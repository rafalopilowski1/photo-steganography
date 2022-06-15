#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cmath>
#include <algorithm>
#include <filesystem>

#include "image/pixel.hpp"

namespace image {
    using Pixel = image::Pixel;

    /**
     * Funckja sprawdzająca, czy ciąg znaków ASCII zmieści się w ostatnich bitach koloru w `Pixel`-ach
     * @param pixelVector Referencja tylko do odczytu wektora `Pixel`-i
     * @param message Wiadomość do zakodowania
     * @return `true` - da się, `false` - nie da sie
     */
    auto check_size_ascii(const std::vector<Pixel> &pixelVector, const std::string &message) -> bool;

    /**
     * Enumerator po typach obsługiwanych obrazów
     */

    enum class ImageType {
        NotSupported, BMP, PPM
    };

    /**
     * Struktura przechowywująca podstawowe informacje o obrazie
     */
    struct Image {
        uint32_t image_width{};
        uint32_t image_height{};
        double max_color_count{};
        uint16_t message_size{};
        image::ImageType image_type{};
        std::vector<Pixel> pixelsBuffer;

        Image() = default;

        virtual ~Image() = default;

        /**
         * Funkcja generująca unikalny wskaźnik do obrazu niezależnie od jego formatu.
         * @param input_src Ścieżka do obrazu
         * @return unikalny wskaźnik do obrazu
         */
        static auto
        get_image_unique_ptr(const std::string &input_src) -> std::unique_ptr<image::Image>;

        /**
         * Określa typ obrazu
         * @param filePath Ścieżka do obrazu
         * @return Typ obrazu
         */
        static auto find_type(const std::string &filePath) -> ImageType;

        /**
         * Funkcja zwracającą referencję do wektora `Pixel`-i
         * @return Referencja do wektora `Pixel`-i
         */
        auto get_pixel_vector() -> std::vector<image::Pixel> & {
            return pixelsBuffer;
        };

        /**
         * Funkcja zwracająca długość wiadomości (odczytanej lub do zakodowania)
         * @return Długość wiadomości
         */
        auto get_message_size() const -> unsigned long {
            return message_size;
        }

        /**
         * Funkcja określająca, czy obraz zawiera ukrytą wiadomość
         * @return `true` - ma; `false` - nie ma
         */
        auto has_message() const -> bool {
            return message_size != 0;
        };

        /**
         * Funkcja wirtualna powalająca zapisać obraz do pliku.
         * @param fileOutputPath Ścieżka do pliku wyjściowego
         */
        virtual auto write_to_file(const std::string &fileOutputPath) -> void = 0;

    };
}
