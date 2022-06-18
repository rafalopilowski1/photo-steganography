#pragma once

#include <bitset>
#include <iostream>

namespace image {
    /**
     * Klasa `Pixel` przechowuje dane o kolorach danego piksela obrazu oraz jego współrzędnych
     */
    struct Pixel {
    public:

        unsigned int x;
        unsigned int y;
        std::bitset<8> red;
        std::bitset<8> green;
        std::bitset<8> blue;

        /**
         * Konstruktor `Pixel` przyjmujący za wartości kolorów liczby
         * @param x
         * @param y
         * @param red
         * @param green
         * @param blue
         */
        Pixel(unsigned int x, unsigned int y, uint8_t red, uint8_t green, uint8_t blue);

        /**
         * Konstruktor `Pixel` przyjmujący za wartości kolorów zestaw 8 bitów
         * @param x
         * @param y
         * @param red
         * @param green
         * @param blue
         */
        Pixel(unsigned int x, unsigned int y, std::bitset<8> red, std::bitset<8> green, std::bitset<8> blue);

        /**
         * Nadpisanie operatora indeksowania, który pozwala za pomocą indeksu zwrócić referencję do `bitset`-u odpowiedniego koloru
         * @param index Indeks
         * @return Referencja do `bitset`-u wybranego koloru
         */
        std::bitset<8> &operator[](int index);
    };
}
