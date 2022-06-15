#include "image/formats/ppm.hpp"

using Ppm = image::Ppm;

Ppm::Ppm(const std::string &fileInputPath) {
    image_type = ImageType::PPM;
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
        try {
            message_size = std::stol(metadata);
        } catch (const std::invalid_argument &ex) {
            std::cout << "Invalid argument: " << ex.what() << '\n';
            exit(1);
        }
    }
    elements.erase(elements.begin(), elements.begin() + 4);
    if (elements.size() != image_width * image_height * 3) {
        std::cerr << "Error reading file!" << '\n';
        exit(2);
    }
    pixelsBuffer = {};
    read_to_pixels_ppm(elements);
}

auto Ppm::read_to_pixels_ppm(const std::vector<std::string> &linesBuffer) -> void {
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

auto Ppm::write_to_file(const std::string &fileOutputPath) -> void {
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