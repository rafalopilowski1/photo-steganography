#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cmath>
#include <algorithm>
#include "image/pixel.hpp"

namespace image {

    struct Image {
        uint16_t image_width{};
        uint16_t image_height{};
        double max_color_count{};
        unsigned long message_size = 0;
        std::vector<image::Pixel> pixelsBuffer;

        Image() = default;

        auto get_pixel_vector() -> std::vector<image::Pixel> & {
            return pixelsBuffer;
        };

        auto get_message_size() const -> unsigned long {
            return message_size;
        }

        virtual auto write_to_file(const std::string &fileOutputPath) -> void = 0;

        auto add_metadata(unsigned long messageBitsSize) -> void {
            message_size = messageBitsSize;
        };

        bool has_metadata() const {
            return message_size != 0;
        };
    };

    struct Ppm : Image {
        inline static const std::string Header = "P3";

        explicit Ppm(const std::string &fileInputPath) {
            auto metadata = std::string();
            auto fileInputStream = std::ifstream(fileInputPath, std::ios_base::binary);
            auto file_begin = std::istreambuf_iterator<char>(fileInputStream);
            auto file_end = std::istreambuf_iterator<char>();
            auto buffer_string = std::string(file_begin, file_end);
            fileInputStream.close();
            if (fileInputStream.fail()) {
                std::cerr << "Fail with file: " << to_string(fileInputStream.exceptions()) << '\n';
                exit(0);
            }
            std::stringstream string_stream(buffer_string);
            std::istream_iterator<std::string> begin_string(string_stream);
            std::istream_iterator<std::string> end_string;
            std::vector<std::string> elements(begin_string, end_string);

            if (elements[0] != Header) {
                std::cerr << "It is not an P3 PPM file! Aborting!" << '\n';
                exit(1);
            }
            try {
                image_width = stoi(elements[1]);
                image_height = stoi(elements[2]);
                max_color_count = stoi(elements[3]);
            } catch (const std::invalid_argument &ex) {
                std::cout << "Invalid argument: " << ex.what() << '\n';
                exit(1);
            }
            if (elements[elements.size() - 2] == "#") {
                metadata += elements[elements.size() - 1];
                elements.erase(elements.end() - 2, elements.end());
            }
            try {
                message_size = std::stol(metadata);
            } catch (const std::invalid_argument &ex) {
                std::cout << "Invalid argument: " << ex.what() << '\n';
                exit(1);
            }
            elements.erase(elements.begin(), elements.begin() + 4);
            if (elements.size() != image_width * image_height * 3) {
                std::cerr << "Error reading file!" << '\n';
                exit(2);
            }
            pixelsBuffer = {};
            read_to_pixels_ppm(elements);
        };

        auto read_to_pixels_ppm(const std::vector<std::string> &linesBuffer) -> void {
            try {
                for (int y = 0; y < image_height * 3; y += 3) {
                    for (int x = 0; x < image_width * 3; x += 3) {
                        auto red = stoull(linesBuffer[x + (y * image_width)]),
                                green = stoull(linesBuffer[x + (y * image_width) + 1]),
                                blue = stoull(linesBuffer[x + (y * image_width) + 2]);
                        pixelsBuffer.emplace_back(x / 3 + 1, y / 3 + 1, red, green, blue);
                    }
                }
            } catch (const std::invalid_argument &ex) {
                std::cout << "Invalid argument: " << ex.what() << '\n';
                exit(1);
            }
        }

        auto write_to_file(const std::string &fileOutputPath) -> void override {
            auto fileOutputStream = std::ofstream(fileOutputPath, std::ios_base::binary);
            fileOutputStream << "P3" << '\n';
            fileOutputStream << image_width << ' ' << image_height << '\n';
            fileOutputStream << max_color_count << '\n';

            for (int i = 0; i < pixelsBuffer.size(); ++i) {
                fileOutputStream << pixelsBuffer[i].red.to_ullong() << ' '
                                 << pixelsBuffer[i].green.to_ullong()
                                 << ' ' << pixelsBuffer[i].blue.to_ullong();
                if (i != (pixelsBuffer.size() - 1))
                    fileOutputStream << ' ';
            }
            fileOutputStream << "\n# " << std::to_string(message_size);
            fileOutputStream.close();
        }
    };

    struct Bmp : Image {
        inline static const std::string Header = "BM";
        /// Size of header in `BITMAPINFOHEADER`
        inline static const uint16_t HeaderSize = 40;
        uint32_t file_size;
        uint32_t metadata;
        uint32_t pixel_data_offset;
        uint32_t image_size;
        uint32_t x_pixels_per_meter;
        uint32_t y_pixels_per_meter;

        explicit Bmp(const std::string &fileInputPath) {
            file_size = 0, metadata = 0, pixel_data_offset = 0, image_size = 0, x_pixels_per_meter = 0, y_pixels_per_meter = 0;
            auto fileInputStream = std::ifstream(fileInputPath,
                                                 std::ios_base::binary | std::ios_base::in);
            char headerTest[2];
            fileInputStream.get(headerTest, 3);
            auto headerString = std::string(headerTest);
            if (headerString != Header) {
                std::cerr << "It is not an BMP file! Aborting!" << '\n';
                exit(1);
            }
            fileInputStream.get(reinterpret_cast<char *>(&file_size), 5);
            fileInputStream.get(reinterpret_cast<char *>(&metadata), 5);
            fileInputStream.get(reinterpret_cast<char *>(&pixel_data_offset), 5);
            uint32_t headerSizeTest = 0;
            fileInputStream.get(reinterpret_cast<char *>(&headerSizeTest), 5);
            if (headerSizeTest != HeaderSize) {
                std::cerr << "It is an non-standard BMP file! Aborting!" << '\n';
                exit(1);
            }
            fileInputStream.get(reinterpret_cast<char *>(&image_width), 5);
            fileInputStream.get(reinterpret_cast<char *>(&image_height), 5);
            uint16_t planesTest = 0;
            fileInputStream.get(reinterpret_cast<char *>(&planesTest), 3);
            if (planesTest != 1) {
                std::cerr << "It is an BMP file with more than 1 plane! Aborting!" << '\n';
                exit(1);
            }
            uint16_t bits_per_pixel;
            fileInputStream.get(reinterpret_cast<char *>(&bits_per_pixel), 3);
            max_color_count = std::pow(2, bits_per_pixel);
            uint32_t compression_test;
            fileInputStream.get(reinterpret_cast<char *>(&compression_test), 5);
            if (compression_test != 0) {
                std::cerr << "It is an compressed BMP file, not supported! Aborting!" << '\n';
                exit(1);
            }
            fileInputStream.get(reinterpret_cast<char *>(&image_size), 5);
            fileInputStream.get(reinterpret_cast<char *>(&x_pixels_per_meter), 5);
            fileInputStream.get(reinterpret_cast<char *>(&y_pixels_per_meter), 5);
            uint32_t total_colors_test = -1, important_colors_test = -1;
            fileInputStream.get(reinterpret_cast<char *>(&total_colors_test), 5);
            fileInputStream.get(reinterpret_cast<char *>(&important_colors_test), 5);
            if (total_colors_test != 0 || important_colors_test != 0) {
                std::cerr << "It is an colour-indexed BMP file, not supported! Aborting!" << '\n';
                exit(1);
            }
            pixelsBuffer = {};
            read_to_pixels_bmp(fileInputStream);
            fileInputStream.close();
        }

        auto read_to_pixels_bmp(std::ifstream &fileInputStream) -> void {
            fileInputStream.seekg(pixel_data_offset);
            for (int i = 0; i < (image_size / 3); ++i) {
                unsigned char red = 0;
                unsigned char green = 0;
                unsigned char blue = 0;
                red = fileInputStream.get();
                green = fileInputStream.get();
                blue = fileInputStream.get();
                pixelsBuffer.emplace_back((i % image_width), image_height - (i / image_height), std::bitset<8>(red),
                                          std::bitset<8>(green), std::bitset<8>(blue));
            }
        }

        template<typename T>
        void writeBinaryToFileOutputStream(
                std::basic_ofstream<char> &fileOutputStream, const T& value, uint8_t size) const {
            fileOutputStream.write(reinterpret_cast<const char *>(value), size);
        }

        auto write_to_file(const std::string &fileOutputPath) -> void override {
            auto fileOutputStream = std::ofstream(fileOutputPath, std::ios_base::binary);
            uint16_t plane = 1; /// 1 plane
            uint16_t bits_per_pixel = 24; /// 8 bits * 3 (RGB) = 24 bit/pixel
            uint32_t compression = 0; /// no compression
            /// no colour indexing
            uint32_t total_colors = 0;
            uint32_t important_colors = 0;
            writeBinaryToFileOutputStream(fileOutputStream, Header.data(), 2);
            writeBinaryToFileOutputStream(fileOutputStream, &file_size, 4);
            writeBinaryToFileOutputStream(fileOutputStream, &metadata, 4);
            writeBinaryToFileOutputStream(fileOutputStream, &pixel_data_offset, 4);
            writeBinaryToFileOutputStream(fileOutputStream, &HeaderSize, 2);
            writeBinaryToFileOutputStream(fileOutputStream, &image_width, 4);
            writeBinaryToFileOutputStream(fileOutputStream, &image_height, 4);
            writeBinaryToFileOutputStream(fileOutputStream, &plane, 2);
            writeBinaryToFileOutputStream(fileOutputStream, &bits_per_pixel, 2);
            writeBinaryToFileOutputStream(fileOutputStream, &compression, 4);
            writeBinaryToFileOutputStream(fileOutputStream, &image_size, 4);
            writeBinaryToFileOutputStream(fileOutputStream, &x_pixels_per_meter, 4);
            writeBinaryToFileOutputStream(fileOutputStream, &y_pixels_per_meter, 4);
            writeBinaryToFileOutputStream(fileOutputStream, &total_colors, 4);
            writeBinaryToFileOutputStream(fileOutputStream, &important_colors, 4);
            std::ranges::sort(pixelsBuffer, [](Pixel pixel1, Pixel pixel2) {
                if (pixel1.x == pixel2.x)
                    return pixel1.y > pixel2.y;
                return pixel2.x > pixel1.x;
            });
            for (image::Pixel pixel: pixelsBuffer) {
                writeBinaryToFileOutputStream(fileOutputStream, &pixel.red, 1);
                writeBinaryToFileOutputStream(fileOutputStream, &pixel.green, 1);
                writeBinaryToFileOutputStream(fileOutputStream, &pixel.blue, 1);
            }
            fileOutputStream.close();
        }
    };
}
