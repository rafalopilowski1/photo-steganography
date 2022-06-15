#include "image/formats/bmp.hpp"
#include "utils/utils.hpp"

using Bmp = image::Bmp;

Bmp::Bmp(const std::string &fileInputPath) {
    file_size = 0, pixel_data_offset = 0, image_size = 0, x_pixels_per_meter = 0, y_pixels_per_meter = 0;
    image_type = ImageType::BMP;

    auto fileInputStream = std::ifstream(fileInputPath,
                                         std::ios_base::binary | std::ios_base::in);

    auto headerTest = utils::read_string_from_file(fileInputStream, 2);
    if (headerTest != Header) {
        std::cerr << "It is not an BMP file! Aborting!" << '\n';
        exit(1);
    }

    utils::read_number_from_file(fileInputStream, &file_size);

    auto metadataTest = utils::read_string_from_file(fileInputStream, 2);
    if (metadataTest == "PJ")
        utils::read_number_from_file(fileInputStream, &message_size);
    else {
        auto index = fileInputStream.tellg();
        index += 2;
        fileInputStream.seekg(index);
    }

    utils::read_number_from_file(fileInputStream, &pixel_data_offset);

    uint32_t headerSizeTest = 0;
    utils::read_number_from_file(fileInputStream, &headerSizeTest);

    if (headerSizeTest != ImageInformationDataHeaderSize) {
        std::cerr << "WARNING: It is an non-standard BMP file! All additional metadata fields will be omitted!" << '\n';
    }
    utils::read_number_from_file(fileInputStream, &image_width);

    utils::read_number_from_file(fileInputStream, &image_height);

    uint16_t planesTest = 0;
    utils::read_number_from_file(fileInputStream, &planesTest);

    if (planesTest != 1) {
        std::cerr << "It is an BMP file with more than 1 plane! Aborting!" << '\n';
        exit(1);
    }
    uint16_t bits_per_pixel;
    utils::read_number_from_file(fileInputStream, &bits_per_pixel);

    max_color_count = std::pow(2, bits_per_pixel);

    uint32_t compression_test;
    utils::read_number_from_file(fileInputStream, &compression_test);

    if (compression_test != 0) {
        std::cerr << "It is an compressed BMP file, not supported! Aborting!" << '\n';
        exit(1);
    }

    utils::read_number_from_file(fileInputStream, &image_size);

    utils::read_number_from_file(fileInputStream, &x_pixels_per_meter);

    utils::read_number_from_file(fileInputStream, &y_pixels_per_meter);

    uint32_t total_colors_test, important_colors_test;
    utils::read_number_from_file(fileInputStream, &total_colors_test);
    utils::read_number_from_file(fileInputStream, &important_colors_test);

    if (total_colors_test != 0 || important_colors_test != 0) {
        std::cerr << "It is an colour-indexed BMP file, not supported! Aborting!" << '\n';
        exit(1);
    }

    pixelsBuffer = {};
    read_to_pixels_bmp(fileInputStream);

    fileInputStream.close();
}

auto Bmp::write_to_file(const std::string &fileOutputPath) -> void {
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
    utils::write_string_to_file_output_stream(fileOutputStream, Header);
    utils::write_number_to_file_output_stream(fileOutputStream, &file_size);
    utils::write_string_to_file_output_stream(fileOutputStream, Metadata);
    utils::write_number_to_file_output_stream(fileOutputStream, &message_size);
    utils::write_number_to_file_output_stream(fileOutputStream, &pixel_data_offset);
    utils::write_number_to_file_output_stream(fileOutputStream, &ImageInformationDataHeaderSize);
    utils::write_number_to_file_output_stream(fileOutputStream, &image_width);
    utils::write_number_to_file_output_stream(fileOutputStream, &image_height);
    utils::write_number_to_file_output_stream(fileOutputStream, &plane);
    utils::write_number_to_file_output_stream(fileOutputStream, &bits_per_pixel);
    utils::write_number_to_file_output_stream(fileOutputStream, &compression);
    utils::write_number_to_file_output_stream(fileOutputStream, &image_size);
    utils::write_number_to_file_output_stream(fileOutputStream, &x_pixels_per_meter);
    utils::write_number_to_file_output_stream(fileOutputStream, &y_pixels_per_meter);
    utils::write_number_to_file_output_stream(fileOutputStream, &total_colors);
    utils::write_number_to_file_output_stream(fileOutputStream, &important_colors);
    for (image::Pixel pixel: pixelsBuffer) {
        uint8_t red_ulong = pixel.red.to_ulong();
        uint8_t green_ulong = pixel.green.to_ulong();
        uint8_t blue_ulong = pixel.blue.to_ulong();
        utils::write_number_to_file_output_stream(fileOutputStream, &red_ulong);
        utils::write_number_to_file_output_stream(fileOutputStream, &green_ulong);
        utils::write_number_to_file_output_stream(fileOutputStream, &blue_ulong);
    }
    fileOutputStream.close();
    std::cout << "Done!" << '\n';
}
auto Bmp::read_to_pixels_bmp(std::ifstream &fileInputStream) -> void {
    fileInputStream.seekg(pixel_data_offset);
    for (int i = 0; i < (image_width * image_height); ++i) {
        unsigned char red = fileInputStream.get();
        unsigned char green = fileInputStream.get();
        unsigned char blue = fileInputStream.get();
        pixelsBuffer.emplace_back((i % image_width), image_height - (i / image_width), std::bitset<8>(red),
                                  std::bitset<8>(green), std::bitset<8>(blue));
    }
}