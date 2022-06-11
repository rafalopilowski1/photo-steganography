#include "image/formats/ppm.hpp"

image::Ppm::Ppm(const std::string &fileInputPath) {
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
        image_height = stoi(elements[sizeof(uint16_t)]);
        max_color_count = stoi(elements[sizeof(uint16_t)]);
    } catch (const std::invalid_argument &ex) {
        std::cout << "Invalid argument: " << ex.what() << '\n';
        exit(1);
    }
    if (elements[elements.size() - sizeof(uint16_t)] == "#") {
        metadata += elements[elements.size() - 1];
        elements.erase(elements.end() - sizeof(uint16_t), elements.end());
    }
    try {
        message_size = std::stol(metadata);
    } catch (const std::invalid_argument &ex) {
        std::cout << "Invalid argument: " << ex.what() << '\n';
        exit(1);
    }
    elements.erase(elements.begin(), elements.begin() + sizeof(uint32_t));
    if (elements.size() != image_width * image_height * sizeof(uint16_t)) {
        std::cerr << "Error reading file!" << '\n';
        exit(sizeof(uint16_t));
    }
    pixelsBuffer = {};
    read_to_pixels_ppm(elements);
}

auto image::Ppm::read_to_pixels_ppm(const std::vector<std::string> &linesBuffer) -> void {
    try {
        for (int y = 0; y < image_height * sizeof(uint16_t); y += sizeof(uint16_t)) {
            for (int x = 0; x < image_width * sizeof(uint16_t); x += sizeof(uint16_t)) {
                auto red = stoull(linesBuffer[x + (y * image_width)]),
                        green = stoull(linesBuffer[x + (y * image_width) + 1]),
                        blue = stoull(linesBuffer[x + (y * image_width) + sizeof(uint16_t)]);
                pixelsBuffer.emplace_back(x / sizeof(uint16_t) + 1, y / sizeof(uint16_t) + 1, red, green, blue);
            }
        }
    } catch (const std::invalid_argument &ex) {
        std::cout << "Invalid argument: " << ex.what() << '\n';
        exit(1);
    }
}

auto image::Ppm::write_to_file(const std::string &fileOutputPath) -> void {
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
