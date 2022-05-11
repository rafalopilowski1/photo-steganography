#pragma once

#include <string>
#include <deque>
#include "image/pixel.hpp"

namespace image::formats {
    struct Ppm {
        inline static const std::string Header = "P3";
        int image_width;
        int image_height;
        int max_color_count;
        std::string metadata;
        std::vector<Pixel> pixelBuffer;

    public:
        explicit Ppm(const std::string & fileInputPath);

        static auto read_to_pixels(const std::vector<std::string> & linesBuffer, Ppm * container) -> void;

        auto write_to_file(const std::string & fileOutputPath, const std::vector<Pixel> & pixelVector) -> void;

        auto get_pixel_vector() -> std::vector<Pixel> &;

        void add_metadata(unsigned long messageBitsSize);
    };
}
