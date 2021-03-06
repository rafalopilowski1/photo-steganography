#include "cli/commands/check.hpp"
#include "image/image.hpp"
#include "utils/utils.hpp"

#include <string>
#include <vector>

using Image = image::Image;
using Pixel = image::Pixel;

namespace cli {
    auto encode(const std::string &inputFilePath, const std::string &outputFilePath,
                const std::string &message) -> void {
        if (utils::check_if_file_readable(inputFilePath)) {
            auto inputFile = Image::get_image_unique_ptr(
                    inputFilePath);
            std::vector<Pixel> &pixelVector = inputFile->get_pixel_vector();
            if (image::check_size_ascii(pixelVector, message, inputFile->image_type)) {
                std::vector<std::bitset<8>> message_bytes{};
                for (char el: message)
                    message_bytes.emplace_back(el);
                std::cout << "Encoding given message..." << '\n';
                const unsigned long messageLenBits = message_bytes.size() * 8;
                inputFile->message_size = messageLenBits;
                // Soundness check in `check_size_ascii()` function
                unsigned int step = (pixelVector.size() * 3) / messageLenBits;
                for (unsigned int i = 0; i < messageLenBits; i++) {
                    pixelVector[(i * step) / 3][(i * step) % 3].set(0, message_bytes[i / 8][i % 8]);
                }
                if (utils::check_if_file_writable(inputFilePath)) {
                    inputFile->write_to_file(outputFilePath);
                } else {
                    std::cerr << "Don't have enough permissions to write into this file! Closing...\n";
                }

            }
        } else {
            std::cerr << "Don't have enough permissions to read this file! Closing...\n";
        }
    }
}