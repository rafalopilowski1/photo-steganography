#include "cli/commands/check.hpp"
#include "image/image.hpp"
#include <bit>
#include <chrono>
#include <string>
#include <vector>

namespace cli {
    auto encode(const std::string &inputFilePath, const std::string &outputFilePath,
                const std::string &message) -> void {
        // TODO: Switch between formats by counting on file extension
        auto message_copy = message;
        auto bmpInputFile = image::Bmp(inputFilePath);
        std::vector<image::Pixel> &pixelVector = bmpInputFile.get_pixel_vector();
        if (check_size_ascii(pixelVector, message)) {
            std::vector<std::bitset<8>> message_bytes{};
            for (char el: message)
                message_bytes.emplace_back(el);
            std::cout << "Encoding given message..." << '\n';
            const unsigned long messageLenBits = message_bytes.size() * 8;
            bmpInputFile.add_metadata(messageLenBits);
            // Soundness check in `check_size_ascii()` function
            unsigned int step = (pixelVector.size() * 3) / messageLenBits;
            unsigned int index = 0;
            std::cout << "0%"
                      << "\n";
            for (unsigned int i = 0; i < messageLenBits; i++) {
                pixelVector[(i * step) / 3][(i * step) % 3].set(0, message_bytes[i / 8][i % 8]);
                unsigned int progress = 100 * i / messageLenBits;
                if (progress > index) {
                    index = progress;
                    std::cout << progress << "%"
                              << "\n";
                }
            }
            std::cout << "100%"
                      << "\n";
            bmpInputFile.write_to_file(outputFilePath);
        };
    }
} // namespace cli