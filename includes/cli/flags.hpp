#pragma once

#include <string>

namespace cli {
    /**
     *
     */
    enum class Flag {
        HELP,
        ENCODE,
        DECODE,
        CHECK,
        INFO
    };
    /**
     *
     * @param str
     * @return
     */
    auto string_to_enum(const std::string & str) -> Flag;
    /**
     *
     * @param args_count
     * @param args
     */
    auto run(int args_count,char* args[]) -> void;
}