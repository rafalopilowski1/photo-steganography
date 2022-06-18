#include <iostream>

namespace cli {
    auto help() -> void {
        auto intro = "PST (Photo Steganography Tool)\n";
        auto flag_help = "   - `-h`: Prints out help\n";
        auto flag_encode = "   - `-e <path_to_file> <message>`: Encodes message in image\n";
        auto flag_decode = "   - `-d <path_to_file>`: Decodes message in image\n";
        auto flag_check = "   - `-c <path_to_file> <message>`: Checks if message can be encoded in image\n";
        auto flag_info = "   - `-i <path_to_file>`: Prints out image metadata\n";
        std::cout << intro << flag_help << flag_encode << flag_decode << flag_check << flag_info;
    }
}
