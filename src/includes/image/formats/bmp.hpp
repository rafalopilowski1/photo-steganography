#pragma once

#include "image/image.hpp"

namespace image {
    struct Bmp : image::Image {
        const std::string Header="BM";
        /// Rozmiar nagłówka `BITMAPINFOHEADER`
        inline static const uint32_t ImageInformationDataHeaderSize = 40;
        /// Rozmiar części nagłówka o typie pliku BMP
        inline static const uint32_t FileTypeDataHeaderSize = 14;
        const std::string Metadata="PJ";
        uint32_t file_size{};
        uint32_t pixel_data_offset{};
        uint32_t image_size{};
        uint32_t x_pixels_per_meter{};
        uint32_t y_pixels_per_meter{};

        /**
         * Konstructor klasy obrazu BMP, który odczytuje podstawowe informacje o obrazie
         * @param fileInputPath Ścieżka do pliku wejściowego
         */
        explicit Bmp(const std::string &fileInputPath);

        /**
         * Funkcja zczytująca z pliku BMP `Pixel`-e
         * @param fileInputStream Strumień pliku wejściowego
         */
        auto read_to_pixels_bmp(std::ifstream &fileInputStream) -> void;

        /**
         * Funkcja zapisująca obraz do pliku w formacie BMP
         * @param fileOutputPath Ścieżka do pliku wyjściowego
         */
        auto write_to_file(const std::string &fileOutputPath) -> void override;
    };
}