#pragma once

#include <string>

namespace cli {
    enum class Flag {
        HELP,
        ENCODE,
        DECODE,
        CHECK,
        INFO
    };
    auto string_to_enum(const std::string & str) -> Flag;
    auto run(int args_count,char* args[]) -> void;
}