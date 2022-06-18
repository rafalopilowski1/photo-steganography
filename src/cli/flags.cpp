#include <string>
#include <iostream>

#include "cli/commands/help.hpp"
#include "cli/commands/encode.hpp"
#include "cli/commands/decode.hpp"
#include "cli/commands/info.hpp"
#include "cli/commands/check.hpp"
#include "cli/flags.hpp"

namespace cli {
    auto string_to_enum(const std::string &str) -> Flag {
        if (str == "-e" || str == "--encode")
            return Flag::ENCODE;
        if (str == "-d" || str == "--decode")
            return Flag::DECODE;
        if (str == "-c" || str == "--check_size_ascii")
            return Flag::CHECK;
        if (str == "-i" || str == "--info")
            return Flag::INFO;
        if (str != "-h" && str != "--help")
            std::cerr << "No such flag!: " << str << "\n\n";
        return Flag::HELP;
    }

    auto run(int args_count, char *args[]) -> void {
        auto flag = string_to_enum(args[1]);
        switch (flag) {
            case Flag::HELP:
                cli::help();
                break;
            case Flag::ENCODE:
                if (args_count == 4) {
                    auto input_src = args[2];
                    auto message = args[3];
                    cli::encode(input_src, input_src, message);
                } else {
                    std::cerr << "Invalid arguments for encode!" << "\n\n";
                    cli::help();
                }
                break;
            case Flag::DECODE:
                if (args_count == 3) {
                    auto input_src = args[2];
                    cli::decode(input_src);
                } else {
                    std::cerr << "Invalid arguments for decode!" << "\n\n";
                    cli::help();
                }
                break;
            case Flag::CHECK:
                if (args_count == 4) {
                    auto input_src = args[2];
                    auto message = args[3];
                    cli::check(input_src, message);
                } else {
                    std::cerr << "Invalid arguments for check!" << "\n\n";
                    cli::help();
                }
                break;
            case Flag::INFO:
                if (args_count == 3) {
                    auto input_src = args[2];
                    cli::info(input_src);
                } else {
                    std::cerr << "Invalid arguments for info!" << "\n\n";
                    cli::help();
                }
                break;
        }
    }
}