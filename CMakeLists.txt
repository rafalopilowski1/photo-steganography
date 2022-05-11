cmake_minimum_required(VERSION 3.19)
project(photo_steganography)

set(CMAKE_CXX_STANDARD 20)

add_executable(photo_steganography main.cpp cli/commands/help.cpp includes/cli/commands/help.hpp cli/flags.cpp includes/cli/flags.hpp cli/commands/encode.cpp includes/cli/commands/encode.hpp cli/commands/decode.cpp includes/cli/commands/decode.hpp cli/commands/check.cpp includes/cli/commands/check.hpp cli/commands/info.cpp includes/cli/commands/info.hpp image/flags/image_formats.cpp includes/image/flags/image_formats.hpp image/formats/ppm.cpp includes/image/formats/ppm.hpp image/pixel.cpp includes/image/pixel.hpp image/pixelsLastBits.cpp includes/image/pixelsLastBits.hpp)
target_include_directories(photo_steganography PUBLIC includes)