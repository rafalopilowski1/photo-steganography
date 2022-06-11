#pragma once
#include "image/image.hpp"
namespace image {
    struct Bmp : image::Image {
        constexpr static const char Header[2]{'B','M'};
        /// Size of header in `BITMAPINFOHEADER`
        inline static const uint32_t HeaderSize = 40;
        constexpr static const char Metadata[2]{'P','J'};
        uint32_t file_size{};
        uint32_t pixel_data_offset{};
        uint32_t image_size{};
        uint32_t x_pixels_per_meter{};
        uint32_t y_pixels_per_meter{};

        explicit Bmp(const std::string &fileInputPath);

        auto read_to_pixels_bmp(std::ifstream &fileInputStream) -> void;

        template<typename T>
        void writeBinaryToFileOutputStream(
                std::basic_ofstream<char> &fileOutputStream, const T &value, uint8_t size) const;

        auto write_to_file(const std::string &fileOutputPath) -> void override;
    };
}