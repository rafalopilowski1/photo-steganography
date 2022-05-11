#include <iostream>
namespace cli {
    auto help() -> void {
        auto intro = "PST (Photo Steganography Tool)";
        auto flag_help = "   - `-h`: help";
        auto flag_encode = "   - `-e`: encode";
        auto flag_decode = "   - `-d`: help";
        auto flag_check = "   - `-c`: check";
        auto flag_info = "   - `-i`: info";
        printf("%s\nFlags: \n%s\n%s\n%s\n%s\n%s\n\n", intro, flag_help, flag_encode, flag_decode, flag_check, flag_info);
    }
}
