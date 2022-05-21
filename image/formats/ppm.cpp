#include <string>
#include <vector>
#include <fstream>
#include <ranges>
#include <sstream>
#include <iostream>
#include "image/formats/ppm.hpp"

using Ppm = image::formats::Ppm;

/**
 * Konstruktor klasy `Ppm` dekoduje obraz do wektora pikseli
 * @param fileInputPath ścieżka do zczytywanego pliku
 */
Ppm::Ppm(const std::string &fileInputPath) {
    metadata = "";
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
    elements.erase(elements.begin(), elements.begin() + 4);
    if (elements.size() != image_width * image_height * 3) {
        std::cerr << "Error reading file!" << '\n';
        exit(2);
    }
    pixelBuffer = {};
    read_to_pixels(elements, this);

}

/**
 * Zczytywanie linii pliku PPM to wektora pikseli
 * @param linesBuffer bufor zczytanych linii
 * @param container inicjalizowana klasa `Ppm`
 */
auto Ppm::read_to_pixels(const std::vector<std::string> &linesBuffer, Ppm *container) -> void {
    try {
        for (int y = 0; y < container->image_height * 3; y += 3) {
            for (int x = 0; x < container->image_width * 3; x += 3) {
                auto red = stoull(linesBuffer[x + (y * container->image_width)]),
                        green = stoull(linesBuffer[x + (y * container->image_width) + 1]),
                        blue = stoull(linesBuffer[x + (y * container->image_width) + 2]);
                // std::cout << "Pixel " << x / 3 + 1 << ":" << y / 3 + 1 << '\n';
                container->pixelBuffer.emplace_back(x / 3 + 1, y / 3 + 1, red, green, blue);
            }
        }
    } catch (const std::invalid_argument &ex) {
        std::cout << "Invalid argument: " << ex.what() << '\n';
        exit(1);
    }

}

/**
 * Zapisanie pliku w formacie PPM
 * @param fileOutputPath ścieżka do pliku docelowego
 * @param message wiadomość do zapisania
 */
auto Ppm::write_to_file(const std::string &fileOutputPath, const std::vector<Pixel> &pixelsBuffer) -> void {
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
    fileOutputStream << "\n# " << metadata;
    fileOutputStream.close();
}

auto Ppm::get_pixel_vector() -> std::vector<Pixel> & {
    return pixelBuffer;
}

void image::formats::Ppm::add_metadata(unsigned long messageBitsSize) {
    metadata += std::to_string(messageBitsSize);
}

bool image::formats::Ppm::has_metadata() {
    return !metadata.empty();
}

int image::formats::Ppm::get_message_size() {
    return std::stoi(metadata);
}
