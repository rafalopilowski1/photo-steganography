#include <iostream>

namespace cli {
    auto help() -> void {
        auto intro = "PST (Photo Steganography Tool)";
        auto flag_help = "   - `-h`: Prints out help";
        auto flag_encode = "   - `-e <path_to_file> <message>`: Encodes message in image";
        auto flag_decode = "   - `-d <path_to_file>`: Decodes message in image";
        auto flag_check = "   - `-c <path_to_file> <message>`: Checks if message can be encoded in image";
        auto flag_info = "   - `-i <path_to_file>`: Prints out image metadata";
        printf("%s\nFlags: \n%s\n%s\n%s\n%s\n%s\n\n", intro, flag_help, flag_encode, flag_decode, flag_check, flag_info);
    }
}
