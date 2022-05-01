#pragma once

#include <bitset>

namespace image {
    /**
     *
     * Klasa `Pixel` przechowuje dane o kolorach danego piksela obrazu
     * @tparam T typ liczby stałoprzecinkowy definiujący ilość bitów przypadający na każdy z kolorów
     */
    class Pixel {
    public:
        auto edit_3_bits(bool first, bool second, bool third) -> void;


        unsigned int x;
        unsigned int y;
        std::bitset<8> red;
        std::bitset<8> green;
        std::bitset<8> blue;

        Pixel(unsigned int x, unsigned int y, std::size_t red, std::size_t green, std::size_t blue);
    };

}
