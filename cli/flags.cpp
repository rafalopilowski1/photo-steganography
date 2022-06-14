#include <string>
#include <iostream>
#include "cli/commands/help.hpp"
#include "cli/commands/encode.hpp"
#include "cli/commands/decode.hpp"
#include "cli/commands/info.hpp"
#include "cli/commands/check.hpp"
#include "cli/flags.hpp"
#include "image/image.hpp"

using Image = image::Image;
using Pixel = image::Pixel;

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
            std::cerr << "No such flag!: " << str << '\n';
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
                    auto input_src = std::string(args[2]);
                    auto message = std::string(args[3]);
                    auto inputFile = Image::get_image_unique_ptr(
                            input_src);
                    std::vector<Pixel> &pixelVector = inputFile->get_pixel_vector();
                    cli::check_size_ascii(pixelVector, message);
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