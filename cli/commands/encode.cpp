#include <string>
#include <vector>
#include "image/formats/ppm.hpp"

namespace cli {
    auto encode(std::string inputFilePath, std::string outputFilePath, std::string message) -> void {
        auto ppmInputFile = image::formats::Ppm(inputFilePath);
        ppmInputFile.write_to_file(outputFilePath, message);
    }
}