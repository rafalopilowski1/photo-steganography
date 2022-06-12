
#include "image/formats/bmp.hpp"

image::Bmp::Bmp(const std::string &fileInputPath) {
    file_size = 0, pixel_data_offset = 0, image_size = 0, x_pixels_per_meter = 0, y_pixels_per_meter = 0;
    image_type = ImageType::BMP;
    auto fileInputStream = std::ifstream(fileInputPath,
                                         std::ios_base::binary | std::ios_base::in);
    auto headerTest = std::vector<char>(2);
    fileInputStream.read(headerTest.data(), sizeof(char) * 2);
    auto headerTestString = std::string(headerTest.begin(), headerTest.end());
    if (headerTestString != Header) {
        std::cerr << "It is not an BMP file! Aborting!" << '\n';
        exit(1);
    }
    fileInputStream.read(reinterpret_cast<char *>(&file_size), sizeof(uint32_t));
    auto metadataTest = std::vector<char>(2);
    fileInputStream.read(reinterpret_cast<char *>(metadataTest.data()), sizeof(uint16_t));
    if (std::string(metadataTest.data()) == "PJ")
        fileInputStream.read(reinterpret_cast<char *>(&message_size), sizeof(uint16_t));
    else {
        auto index = fileInputStream.tellg().operator+(2);
        fileInputStream.seekg(index);
    }
    fileInputStream.read(reinterpret_cast<char *>(&pixel_data_offset), sizeof(uint32_t));
    uint32_t headerSizeTest = 0;
    fileInputStream.read(reinterpret_cast<char *>(&headerSizeTest), sizeof(uint32_t));
    if (headerSizeTest != ImageInformationDataHeaderSize) {
        std::cerr << "WARNING: It is an non-standard BMP file! All additional metadata fields will be omitted!" << '\n';
//        exit(0);
    }
    fileInputStream.read(reinterpret_cast<char *>(&image_width), sizeof(uint32_t));
    fileInputStream.read(reinterpret_cast<char *>(&image_height), sizeof(uint32_t));
    uint16_t planesTest = 0;
    fileInputStream.read(reinterpret_cast<char *>(&planesTest), sizeof(uint16_t));
    if (planesTest != 1) {
        std::cerr << "It is an BMP file with more than 1 plane! Aborting!" << '\n';
        exit(1);
    }
    uint16_t bits_per_pixel;
    fileInputStream.read(reinterpret_cast<char *>(&bits_per_pixel), sizeof(uint16_t));
    max_color_count = std::pow(sizeof(uint16_t), bits_per_pixel);
    uint32_t compression_test;
    fileInputStream.read(reinterpret_cast<char *>(&compression_test), sizeof(uint32_t));
    if (compression_test != 0) {
        std::cerr << "It is an compressed BMP file, not supported! Aborting!" << '\n';
        exit(1);
    }
    fileInputStream.read(reinterpret_cast<char *>(&image_size), sizeof(uint32_t));
    fileInputStream.read(reinterpret_cast<char *>(&x_pixels_per_meter), sizeof(uint32_t));
    fileInputStream.read(reinterpret_cast<char *>(&y_pixels_per_meter), sizeof(uint32_t));
    uint32_t total_colors_test = -1, important_colors_test = -1;
    fileInputStream.read(reinterpret_cast<char *>(&total_colors_test), sizeof(uint32_t));
    fileInputStream.read(reinterpret_cast<char *>(&important_colors_test), sizeof(uint32_t));
    if (total_colors_test != 0 || important_colors_test != 0) {
        std::cerr << "It is an colour-indexed BMP file, not supported! Aborting!" << '\n';
        exit(1);
    }
    pixelsBuffer = {};
    read_to_pixels_bmp(fileInputStream);
    fileInputStream.close();
}

auto image::Bmp::write_to_file(const std::string &fileOutputPath) -> void {
    auto fileOutputStream = std::ofstream(fileOutputPath,
                                          std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);
    uint16_t plane = 1; /// 1 plane
    uint16_t bits_per_pixel = 24; /// 8 bits * sizeof(uint16_t) (RGB) = 24 bit/pixel
    uint32_t compression = 0; /// no compression
    /// no colour indexing
    uint32_t total_colors = 0;
    uint32_t important_colors = 0;
    pixel_data_offset = ImageInformationDataHeaderSize + FileTypeDataHeaderSize;
    file_size = pixel_data_offset + image_size;
    std::cout << "Saving to BMP file..." << '\n';
    writeBinaryToFileOutputStream(fileOutputStream, Header.data(), sizeof(char) * 2);
    writeBinaryToFileOutputStream(fileOutputStream, &file_size, sizeof(uint32_t));
    writeBinaryToFileOutputStream(fileOutputStream, Metadata.data(), sizeof(char) * 2);
    writeBinaryToFileOutputStream(fileOutputStream, &message_size, sizeof(uint16_t));
    writeBinaryToFileOutputStream(fileOutputStream, &pixel_data_offset, sizeof(uint32_t));
    writeBinaryToFileOutputStream(fileOutputStream, &ImageInformationDataHeaderSize, sizeof(uint32_t));
    writeBinaryToFileOutputStream(fileOutputStream, &image_width, sizeof(uint32_t));
    writeBinaryToFileOutputStream(fileOutputStream, &image_height, sizeof(uint32_t));
    writeBinaryToFileOutputStream(fileOutputStream, &plane, sizeof(uint16_t));
    writeBinaryToFileOutputStream(fileOutputStream, &bits_per_pixel, sizeof(uint16_t));
    writeBinaryToFileOutputStream(fileOutputStream, &compression, sizeof(uint32_t));
    writeBinaryToFileOutputStream(fileOutputStream, &image_size, sizeof(uint32_t));
    writeBinaryToFileOutputStream(fileOutputStream, &x_pixels_per_meter, sizeof(uint32_t));
    writeBinaryToFileOutputStream(fileOutputStream, &y_pixels_per_meter, sizeof(uint32_t));
    writeBinaryToFileOutputStream(fileOutputStream, &total_colors, sizeof(uint32_t));
    writeBinaryToFileOutputStream(fileOutputStream, &important_colors, sizeof(uint32_t));
    for (image::Pixel pixel: pixelsBuffer) {
        uint8_t red_ulong = pixel.red.to_ulong();
        uint8_t green_ulong = pixel.green.to_ulong();
        uint8_t blue_ulong = pixel.blue.to_ulong();
        writeBinaryToFileOutputStream(fileOutputStream, &red_ulong, sizeof(red_ulong));
        writeBinaryToFileOutputStream(fileOutputStream, &green_ulong, sizeof(green_ulong));
        writeBinaryToFileOutputStream(fileOutputStream, &blue_ulong, sizeof(blue_ulong));
    }
    fileOutputStream.close();
    std::cout << "Done!" << '\n';
}

auto image::Bmp::read_to_pixels_bmp(std::ifstream &fileInputStream) -> void {
    fileInputStream.seekg(pixel_data_offset);
    for (int i = 0; i < (image_width*image_height); ++i) {
        unsigned char red = fileInputStream.get();
        unsigned char green = fileInputStream.get();
        unsigned char blue = fileInputStream.get();
        pixelsBuffer.emplace_back((i % image_width), image_height - (i / image_height), std::bitset<8>(red),
                                  std::bitset<8>(green), std::bitset<8>(blue));
    }
}

template<typename T>
void image::Bmp::writeBinaryToFileOutputStream(std::basic_ofstream<char> &fileOutputStream, const T &value,
                                               uint8_t size) const {
    fileOutputStream.write(reinterpret_cast<const char *>(value), size);
}