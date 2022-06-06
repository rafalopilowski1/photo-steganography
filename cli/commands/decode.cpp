#include "image/image.hpp"
#include "image/pixel.hpp"
#include <string>
#include <vector>

namespace cli {
    auto decode(const std::string &inputFilePath) -> void {
        // TODO: Switch between formats by counting on file extension
        auto bmpInputFile = image::Bmp(inputFilePath);
        // Soundness check_size_ascii in `has_metadata()` function
        if (bmpInputFile.has_metadata()) {
            auto message = std::string{};

            std::vector<image::Pixel> &pixelVector = bmpInputFile.get_pixel_vector();

            auto messageLenBits = bmpInputFile.get_message_size();

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
    }
} // namespace cli