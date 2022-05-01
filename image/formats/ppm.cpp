#include <string>
#include <vector>
#include <fstream>
#include <ranges>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "image/formats/ppm.hpp"

using Ppm = image::formats::Ppm;

/**
 * Konstruktor klasy `Ppm` dekoduje obraz do wektora pikseli
 * @param fileInputStream strumień wejściowy zczytywanego pliku
 */
Ppm::Ppm(std::string fileInputPath) {
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

    image_width = stoi(elements[1]);
    image_height = stoi(elements[2]);
    max_color_count = stoi(elements[3]);
    elements.erase(elements.begin(), elements.begin() + 4);
    if (elements.size() != image_width * image_height * 3) {
        std::cerr << "Error reading file!" << '\n';
        exit(3);
    }
    pixelBuffer = {};
    read_to_pixels(elements, this);
    std::ranges::sort(pixelBuffer, [](Pixel pixel1, Pixel pixel2) {
        return pixel2.red.to_ulong() + pixel2.green.to_ulong() + pixel2.blue.to_ulong() >
               pixel1.red.to_ulong() + pixel1.green.to_ulong() + pixel1.blue.to_ulong();
    });
}

/**
 * Zczytywanie linii pliku PPM to wektora pikseli
 * @param linesBuffer bufor zczytanych linii
 * @param container inicjalizowana klasa `Ppm`
 */
auto Ppm::read_to_pixels(std::vector<std::string> linesBuffer, Ppm *container) -> void {
    for (int y = 0; y < container->image_height * 3; y += 3) {
        for (int x = 0; x < container->image_width * 3; x += 3) {
            auto red = stoi(linesBuffer[x + (y * container->image_width)]),
                    green = stoi(linesBuffer[x + (y * container->image_width) + 1]),
                    blue = stoi(linesBuffer[x + (y * container->image_width) + 2]);

            std::cout << "Pixel " << x / 3 + 1 << ":" << y / 3 + 1 << '\n';
            container->pixelBuffer.emplace_back(x / 3 + 1, y / 3 + 1, red, green, blue);
        }
    }

}

/**
 * Zapisanie pliku w formacie PPM
 * @param fileOutputStream strumień wyjściowy pliku docelowego
 */
auto Ppm::write_to_file(std::string fileOutputPath, std::string message) -> void {
    std::ranges::sort(pixelBuffer, [this](Pixel pixel1, Pixel pixel2) {
        auto pixel1_length = pixel1.x + pixel1.y * image_width;
        auto pixel2_length = pixel2.x + pixel2.y * image_width;
        return pixel2_length > pixel1_length;
    });

    auto fileOutputStream = std::ofstream(fileOutputPath, std::ios_base::binary);
    fileOutputStream << "P3" << '\n';
    fileOutputStream << image_width << ' ' << image_height << '\n';
    fileOutputStream << max_color_count << '\n';

    for (int i = 0; i < pixelBuffer.size(); ++i) {
        fileOutputStream << pixelBuffer[i].red.to_ulong() << ' '
                         << pixelBuffer[i].green.to_ulong()
                         << ' ' << pixelBuffer[i].blue.to_ulong();
        if (i != (pixelBuffer.size() - 1))
            fileOutputStream << ' ';
    }
    fileOutputStream.close();
}
