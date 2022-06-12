#pragma once
#include "image/image.hpp"

namespace image {
    struct Ppm : image::Image {
        constexpr static const char Header[2]{'P', '3'};
        /**
         *
         * @param fileInputPath
         */
        explicit Ppm(const std::string &fileInputPath);;
        /**
         *
         * @param linesBuffer
         */
        auto read_to_pixels_ppm(const std::vector<std::string> &linesBuffer) -> void;
        /**
         *
         * @param fileOutputPath
         */
        auto write_to_file(const std::string &fileOutputPath) -> void override;
    };
}
