#include "image/formats/ppm.hpp"
#include "image/pixel.hpp"
#include <string>
#include <vector>

namespace cli {
auto decode(const std::string &inputFilePath) -> void {
  // TODO: Switch between formats by counting on file extension
  auto ppmInputFile = image::formats::Ppm(inputFilePath);
  // Soundness check_size_ascii in `has_metadata()` function
  if (ppmInputFile.has_metadata()) {
    auto message = std::string{};

    std::vector<image::Pixel> &pixelVector = ppmInputFile.get_pixel_vector();

    auto messageLenBits = ppmInputFile.get_message_size();

    std::cout << "Decoding given file..." << '\n';

    auto buf = std::bitset<8>{};
    unsigned int step = (pixelVector.size() * 3) / (messageLenBits);
    unsigned int index = 0;
    for (unsigned int i = 0; i < messageLenBits; i++) {
      auto byte = pixelVector[(i*step) / 3][(i*step) % 3];
      bool bit = byte[0];
      if ((i + 1) % 8 == 0) {
        message += static_cast<char>(buf.to_ullong());
        buf.reset();
      }
      buf.set(i % 8, bit);
        unsigned int progress = 100 * i / (messageLenBits);
        if (progress > index) {
          index = progress;
          std::cout << progress << "%"
                    << "\n";
        }
    }
    std::cout << "100%"
              << "\n";
    std::cout << "Decrypted message:\n\n" << message << '\n';

  } else {
    std::cerr << "File not encoded with this program, closing..." << '\n';
    exit(0);
  }
}
} // namespace cli