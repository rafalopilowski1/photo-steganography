#pragma once

#include <string>
#include <vector>

#include "image/pixel.hpp"

namespace cli {
    /**
     * Funkcja sprawdzająca, czy dana wiadomość ASCII zmieści się w obrazie.
     * @param input_src Ścieżka do obrazu
     * @param message Wiadomość do zakodowania
     */
    auto check(const std::string &input_src, const std::string &message) -> void;
}