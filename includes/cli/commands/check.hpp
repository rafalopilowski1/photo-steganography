#pragma once

#include <string>

namespace cli {
    auto check_size_ascii(const std::string & filePath, const std::string & message) -> bool;
}