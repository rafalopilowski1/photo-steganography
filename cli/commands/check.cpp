#include <string>
#include <vector>
#include <iostream>
#include "image/pixel.hpp"

namespace cli {
    auto check_size_ascii(const std::vector<image::Pixel> &pixelVector, const std::string &message) -> bool {
        auto messageLenBits = message.size() * 8;
        auto imageSizePotencial = (pixelVector.size() * 3);
        if (messageLenBits <= imageSizePotencial) {
            std::cout << "Given message (" << messageLenBits << " bits) can be written into this image ("
                      << imageSizePotencial << " bits)" << '\n';
            return true;
        } else {
            std::cout << "Given message (" << messageLenBits << " bits) can't be written into this image ("
                      << imageSizePotencial << " bits)" << '\n';
            return false;
        }
    }
}