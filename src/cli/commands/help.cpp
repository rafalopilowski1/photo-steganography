#include <iostream>

namespace cli {
    auto help() -> void {
        auto intro = "PST (Photo Steganography Tool)";
        auto flag_help = "   - `-h`: help";
        auto flag_encode = "   - `-e <path_to_file> <message>`: encode";
        auto flag_decode = "   - `-d <path_to_file>`: help";
        auto flag_check = "   - `-c <path_to_file> <message>`: check";
        auto flag_info = "   - `-i <path_to_file>`: info";
        printf("%s\nFlags: \n%s\n%s\n%s\n%s\n%s\n\n", intro, flag_help, flag_encode, flag_decode, flag_check, flag_info);
    }
}
