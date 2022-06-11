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
        BMP, PPM, NotSupported
    };

    struct Image {
        uint32_t image_width{};
        uint32_t image_height{};
        double max_color_count{};
        uint16_t message_size{};
        std::vector<image::Pixel> pixelsBuffer;

        Image() = default;

        static auto
        get_image_unique_ptr(const std::basic_string<char> &input_src) -> std::unique_ptr<image::Image>;

        static auto find_type(const std::string &filePath) -> ImageType;

        auto get_pixel_vector() -> std::vector<image::Pixel> & {
            return pixelsBuffer;
        };

        auto get_message_size() const -> unsigned long {
            return message_size;
        }

        bool has_metadata() const {
            return message_size != 0;
        };

        virtual auto write_to_file(const std::string &fileOutputPath) -> void = 0;
        virtual ~Image();
    };

}
