#include <iostream>

namespace cli {
    auto help() -> void {
        auto intro = "PST (Photo Steganography Tool)\n";
        auto flag_help = "   - `-h`: Prints out help\n";
        auto flag_encode = "   - `-e <path_to_file> <message>`: Encodes message in image\n";
        auto flag_decode = "   - `-d <path_to_file>`: Decodes message in image\n";
        auto flag_check = "   - `-c <path_to_file> <message>`: Checks if message can be encoded in image\n";
        auto flag_info = "   - `-i <path_to_file>`: Prints out image metadata\n";
        auto extended_flag_help = "   - `-h` = `--help`\n";
        auto extended_flag_encode = "   - `-e` = `--encode`\n";
        auto extended_flag_decode = "   - `-d` = `--decode`\n";
        auto extended_flag_check = "   - `-c` = `--check`\n";
        auto extended_flag_info = "   - `-i` = `--info`\n";
        std::cout << intro << flag_help << flag_encode << flag_decode << flag_check << flag_info << '\n'
                  << "You can also use extended flags: \n" << extended_flag_help << extended_flag_encode
                  << extended_flag_decode << extended_flag_check << extended_flag_info;
    }
}
