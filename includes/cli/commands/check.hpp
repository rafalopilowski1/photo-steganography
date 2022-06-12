#pragma once

#include <string>
#include <vector>
#include "image/pixel.hpp"

namespace cli {
    /**
     * Sprawdzanie, czy wiadomość w formacie ASCII zmieśći się w obrazie.
     * @param pixelVector zbiór pikseli obrazu
     * @param message Wiadomość do wysłania
     * @return bool (1 - tak, 0 - nie)
     */
    auto check_size_ascii(const std::vector<image::Pixel> &pixelVector, const std::string & message) -> bool;
}