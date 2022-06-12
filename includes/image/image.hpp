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
    enum class ImageType {
        NotSupported, BMP, PPM
    };

    struct Image {
        uint32_t image_width{};
        uint32_t image_height{};
        double max_color_count{};
        uint16_t message_size{};
        image::ImageType image_type{};
        std::vector<image::Pixel> pixelsBuffer;

        Image() = default;

        /**
         *
         * @param input_src
         * @return
         */
        static auto
        get_image_unique_ptr(const std::string &input_src) -> std::unique_ptr<image::Image>;

        /**
         *
         * @param filePath
         * @return
         */
        static auto find_type(const std::string &filePath) -> ImageType;

        /**
         *
         * @return
         */
        auto get_pixel_vector() -> std::vector<image::Pixel> & {
            return pixelsBuffer;
        };

        /**
         *
         * @return
         */
        auto get_message_size() const -> unsigned long {
            return message_size;
        }

        /**
         *
         * @return
         */
        bool has_metadata() const {
            return message_size != 0;
        };

        /**
         *
         * @param fileOutputPath
         */
        virtual auto write_to_file(const std::string &fileOutputPath) -> void = 0;

        virtual ~Image();
    };

}
