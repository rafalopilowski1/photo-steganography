#pragma once

#include <string>

namespace cli {
    auto encode(std::string inputFilePath, std::string outputFilePath, std::string message) -> void;
}
