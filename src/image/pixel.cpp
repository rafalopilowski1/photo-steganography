//
// Created by rafal_opilowski on 18.06.22.
//
#include <image/pixel.hpp>

namespace image {
    Pixel::Pixel(unsigned int x, unsigned int y, uint8_t red, uint8_t green, uint8_t blue) :
            x(x), y(y), red(red), green(green), blue(blue) {}

    Pixel::Pixel(unsigned int x, unsigned int y, std::bitset<8> red, std::bitset<8> green, std::bitset<8> blue) :
            x(x), y(y), red(red), green(green), blue(blue) {}

    std::bitset<8> &Pixel::operator[](int index) {
        switch (index) {
            case 0:
                return red;
            case 1:
                return green;
            case 2:
                return blue;
            default:
                std::cerr << "Wrong index!!!" << '\n';
                exit(0);
        }
    }

    const std::bitset<8>& Pixel::operator[](int index) const {
        switch (index) {
            case 0:
                return red;
            case 1:
                return green;
            case 2:
                return blue;
            default:
                std::cerr << "Wrong index!!!" << '\n';
                exit(0);
        }
    }
}
