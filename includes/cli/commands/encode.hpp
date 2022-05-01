#pragma once

#include <string>

namespace cli {
    auto encode(const std::string & inputFilePath, const std::string & outputFilePath, const std::string & message) -> void;
}
