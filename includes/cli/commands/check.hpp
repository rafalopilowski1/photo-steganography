#pragma once

#include <string>
#include <vector>
#include "image/pixel.hpp"

namespace cli {
    auto check_size_ascii(const std::vector<image::Pixel> &pixelVector, const std::string & message) -> bool;
}