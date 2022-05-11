#include <string>
#include <vector>
#include <bit>
#include "image/formats/ppm.hpp"
#include "cli/commands/check.hpp"

namespace cli {
    auto
    encode(const std::string &inputFilePath, const std::string &outputFilePath, const std::string &message) -> void {
        // TODO: Switch between formats by counting on file extension
        check(inputFilePath, message);
        auto ppmInputFile = image::formats::Ppm(inputFilePath);
        std::vector<image::Pixel> &pixelVector = ppmInputFile.get_pixel_vector();

        std::vector<std::bitset<8>> message_bytes;
        message_bytes.reserve(message.size());
        std::transform(message.begin(), message.end(), message_bytes.begin(), [](char el) {
            return std::bitset<8>(el);
        });
        // Soundness check in `check()` function
        unsigned int step = (pixelVector.size() * 3) / (message.size() * 8);
        const int bitIndex =
                std::endian::native == std::endian::little ? 0 : std::endian::native == std::endian::big ? 7 : -1;
        if (bitIndex >= 0) {
            for (int i = 0; i < message.size() * 8; i += step) {
                pixelVector[i / 3][i % 3].set(bitIndex, message_bytes[i / 8][i % 8]);
            }
            ppmInputFile.
                    write_to_file(outputFilePath, pixelVector);
        } else {
            std::cerr << "Mixed endian detected - not supported, exiting..." << '\n';
            exit(0);
        }
    }
}