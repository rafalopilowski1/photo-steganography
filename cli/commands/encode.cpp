#include <string>
#include <vector>
#include "image/formats/ppm.hpp"

namespace cli {
    auto encode(const std::string & inputFilePath, const std::string & outputFilePath, const std::string & message) -> void {
        auto ppmInputFile = image::formats::Ppm(inputFilePath);
        ppmInputFile.write_to_file(outputFilePath, message);
    }
}