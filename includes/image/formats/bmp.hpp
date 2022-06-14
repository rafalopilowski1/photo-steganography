#pragma once
#include "image/image.hpp"
namespace image {
    struct Bmp : image::Image {
        const std::string Header="BM";
        /// Size of header in `BITMAPINFOHEADER`
        inline static const uint32_t ImageInformationDataHeaderSize = 40;
        inline static const uint32_t FileTypeDataHeaderSize = 14;
        const std::string Metadata="PJ";
        uint32_t file_size{};
        uint32_t pixel_data_offset{};
        uint32_t image_size{};
        uint32_t x_pixels_per_meter{};
        uint32_t y_pixels_per_meter{};

        /**
         *
         * @param fileInputPath
         */
        explicit Bmp(const std::string &fileInputPath);

        /**
         *
         * @param fileInputStream
         */
        auto read_to_pixels_bmp(std::ifstream &fileInputStream) -> void;

        /**
         *
         * @param fileOutputPath
         */
        auto write_to_file(const std::string &fileOutputPath) -> void override;
    };
}