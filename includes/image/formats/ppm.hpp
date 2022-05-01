#pragma once

#include <string>
#include <deque>
#include "image/pixel.hpp"

namespace image::formats {
    class Ppm {
        inline static const std::string Header = "P3";
        int image_width;
        int image_height;
        int max_color_count;
        std::vector<Pixel> pixelBuffer;

    public:
        explicit Ppm(const std::string & fileInputPath);

        static auto read_to_pixels(const std::vector<std::string> & linesBuffer, Ppm * container) -> void;

        auto write_to_file(const std::string & fileOutputPath, const std::string & message) -> void;

        auto get_pixel_vector() -> std::vector<Pixel> &;
    };
}
