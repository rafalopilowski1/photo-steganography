#pragma once

#include <string>

namespace cli {
    /**
     * Enumerator po rodzajach funkcjonalności programu
     */
    enum class Flag {
        HELP,
        ENCODE,
        DECODE,
        CHECK,
        INFO
    };

    /**
     * Funkcja zczytująca `string` to enumeratora `Flag`
     * @param str
     * @return
     */
    auto string_to_enum(const std::string & str) -> Flag;

    /**
     * Główna funkcja uruchamiająca program
     * @param args_count Ilość argumentów
     * @param args Wskaźnik do tablicy `char`-ów, przechowywująca argumenty
     */
    auto run(int args_count,char* args[]) -> void;
}