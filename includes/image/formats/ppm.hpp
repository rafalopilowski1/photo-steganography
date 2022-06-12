#pragma once
#include "image/image.hpp"

namespace image {
    struct Ppm : image::Image {
        const std::string Header="P3";
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
