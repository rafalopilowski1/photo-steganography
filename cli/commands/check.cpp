#include <string>
#include <vector>
#include <iostream>
#include "image/formats/ppm.hpp"
#include "image/pixel.hpp"

namespace cli {
    auto check(const std::string &filePath, const std::string &message) -> void {
        auto ppmInputFile = image::formats::Ppm(filePath);
        std::vector<image::Pixel> & pixelVector = ppmInputFile.get_pixel_vector();
        auto messageLenBits = message.size() * 8;
        auto imageSizePotencial = (pixelVector.size() * 3);
        if (messageLenBits <= imageSizePotencial) {
            std::cout << "Given message (" << messageLenBits << ") bytes can be written into this image (" << imageSizePotencial << ") bytes." << '\n';
        } else {
            std::cout << "Given message (" << messageLenBits << ") bytes can't be written into this image (" << imageSizePotencial << ") bytes." << '\n';
        }
    }
}