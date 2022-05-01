#include <string>
#include <iostream>
#include "cli/commands/help.hpp"
#include "cli/commands/encode.hpp"
#include "cli/commands/decode.hpp"
#include "cli/commands/info.hpp"
#include "cli/commands/check.hpp"
#include "cli/flags.hpp"

namespace cli {
    auto string_to_enum(std::string str) -> Flag {
        if (str == "-e" || str == "--encode")
            return Flag::ENCODE;
        if (str == "-d" || str == "--decode")
            return Flag::DECODE;
        if (str == "-c" || str == "--check")
            return Flag::CHECK;
        if (str == "-i" || str == "--info")
            return Flag::INFO;
        return Flag::HELP;
    }

    auto run(int args_count, char *args[]) -> void {
        auto flag = string_to_enum(args[1]);
        switch (flag) {
            case Flag::HELP:
                cli::help();
                break;
            case Flag::ENCODE:
                if (args_count == 5) {
                    auto input_src = args[2];
                    auto output_src = args[3];
                    auto message = args[4];
                    cli::encode(input_src, output_src, message);
                } else {
                    std::cerr << "Bad arguments" << "\n\n";
                    cli::help();
                }
                break;
            case Flag::DECODE:
                if (args_count == 3) {
                    auto input_src = args[2];
                    cli::decode(input_src);
                } else {
                    std::cerr << "Bad arguments" << "\n\n";
                    cli::help();
                }
                break;
            case Flag::CHECK:
                if (args_count == 4) {
                    auto input_src = args[2];
                    auto message = args[3];
                    cli::check(input_src, message);
                } else {
                    std::cerr << "Bad arguments" << "\n\n";
                    cli::help();
                }
                break;
            case Flag::INFO:
                if (args_count == 3) {
                    auto input_src = args[2];
                    cli::info(input_src);
                } else {
                    std::cerr << "Bad arguments" << "\n\n";
                    cli::help();
                }
                break;
        }
    }
}