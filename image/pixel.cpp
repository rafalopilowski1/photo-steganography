#include <bit>
#include "image/pixel.hpp"

using Pixel = image::Pixel;

Pixel::Pixel(unsigned int x, unsigned int y, std::size_t red, std::size_t green, std::size_t blue) :
        x(x), y(y), red(red), green(green), blue(blue) {}

/**
 * Funkcja `edit_3_bits` ukrywa w pikselu 3 bity informacji
 * @param first pierwszy bit
 * @param second drugi bit
 * @param third trzeci bit
 */

auto Pixel::edit_3_bits(bool first, bool second, bool third) -> void {
    if (std::endian::native == std::endian::little) {
        /// Little-endian
        red.set(0, first);
        green.set(0, second);
        blue.set(0, third);
    } else if (std::endian::native == std::endian::big) {
        /// Big-endian
        red.set(red.size() - 1, first);
        green.set(green.size() - 1, second);
        blue.set(blue.size() - 1, third);
    }
}