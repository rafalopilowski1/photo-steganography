#pragma once

#include <string>

namespace cli {
    /**
     *
     * @param inputFilePath
     * @param outputFilePath
     * @param message
     */
    auto encode(const std::string & inputFilePath, const std::string & outputFilePath, const std::string & message) -> void;
}
