#include <string>
#include <vector>

#include "image/image.hpp"
#include "image/pixel.hpp"
#include "utils/utils.hpp"

using Image = image::Image;
using Pixel = image::Pixel;

namespace cli {
    auto decode(const std::string &inputFilePath) -> void {
        if (utils::check_if_file_readable(inputFilePath)) {
            auto inputFile = Image::get_image_unique_ptr(inputFilePath);

            // Soundness check_size_ascii in `has_message()` function
            if (inputFile->has_message()) {
                auto message = std::string{};
                const std::vector<Pixel> &pixelVector = inputFile->get_pixel_vector();

                auto messageLenBits = inputFile->get_message_size();

                std::cout << "Decoding given file..." << '\n';

                auto buf = std::bitset<8>{};
                unsigned int step = (pixelVector.size() * 3) / (messageLenBits);
                for (unsigned int i = 0; i < messageLenBits; i++) {
                    auto byte = pixelVector[(i * step) / 3][(i * step) % 3];
                    bool bit = byte[0];
                    if ((i + 1) % 8 == 0) {
                        message += static_cast<char>(buf.to_ullong());
                        buf.reset();
                    }
                    buf.set(i % 8, bit);
                }
                std::cout << "Done!"
                          << "\n";
                std::cout << "Decrypted message:\n\n" << message << '\n';

            } else {
                std::cerr << "File not encoded with this program, closing..." << '\n';
                exit(0);
            }
        } else {
            std::cerr << "Don't have enough permissions to read this file! Closing...\n";
        }
    }
}