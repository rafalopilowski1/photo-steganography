#pragma once

#include "image/image.hpp"

namespace image {
    /**
     * Struktura obrazu PPM P3
     */
    struct Ppm : image::Image {
        const std::string Header = "P3";

        /**
         * Konstruktor klasy obrazu PPM, który odczytuje podstawowe informacje o obrazie
         * @param fileInputPath Ścieżka do pliku wejściowego
         */
        explicit Ppm(const std::string &fileInputPath);

        /**
         * Funkcja zczytująca z pliku PPM `Pixel`-e
         * @param linesBuffer Bufor linii plików zapianych w `string`-ach
         */
        auto read_to_pixels_ppm(const std::vector<std::string> &linesBuffer) -> void;

        /**
         * Funkcja zapisująca obraz do pliku w formacie PPM P3
         * @param fileOutputPath Ścieżka do pliku wyjściowego
         */
        auto write_to_file(const std::string &fileOutputPath) -> void override;
    };
}
