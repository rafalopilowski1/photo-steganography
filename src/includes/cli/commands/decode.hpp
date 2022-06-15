#pragma once

namespace cli {
    /**
     * Funkcja odkodywująca wiadomość z obrazu
     * @param inputFilePath Ścieżka do obrazu
     */
    auto decode(const std::string &inputFilePath) -> void;
}