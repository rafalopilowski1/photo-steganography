#include "image/pixel.hpp"


image::Pixel::Pixel(unsigned int x, unsigned int y, std::size_t red, std::size_t green, std::size_t blue) {
    this->x = x;
    this->y = y;
    this->red = red;
    this->green = green;
    this->blue = blue;
}

/**
 * Funkcja `edit_3_bits` ukrywa w pikselu 3 bity informacji
 * @param first pierwszy bit
 * @param second drugi bit
 * @param third trzeci bit
 */

auto image::Pixel::edit_3_bits(bool first, bool second, bool third) -> void {
    /// Little-endian
    red.set(0, first);
    green.set(0, second);
    blue.set(0, third);
}