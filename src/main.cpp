#include <iostream>
#include "cli/commands/help.hpp"
#include "cli/flags.hpp"

auto main(int char_count, char *argument_vector[]) -> int {
    switch (char_count) {
        case 2:
        case 3:
        case 4:
        case 5:
            cli::run(char_count, argument_vector);
            break;
        default:
            std::cerr << "Invalid number of arguments" << "\n\n";
            cli::help();
            break;
    }
}
