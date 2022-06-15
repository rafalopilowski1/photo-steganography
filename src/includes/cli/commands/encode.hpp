#pragma once

#include <string>

namespace cli {
    /**
     * Funkcja kodująca wiadomość do obrazu.
     * @param inputFilePath Ścieżka do obrazu wejściowego
     * @param outputFilePath Ścieżka do pliku wyjściowego
     * @param message Wiadomość do zakodowania
     */
    auto
    encode(const std::string &inputFilePath, const std::string &outputFilePath, const std::string &message) -> void;
}
