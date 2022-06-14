cmake_minimum_required(VERSION 3.19)
project(photo_steganography)

set(CMAKE_CXX_STANDARD 20)

add_executable(photo_steganography main.cpp cli/commands/help.cpp  cli/flags.cpp  cli/commands/encode.cpp  cli/commands/decode.cpp  cli/commands/check.cpp  cli/commands/info.cpp includes/image/image.hpp image/image.cpp includes/image/formats/ppm.hpp includes/image/formats/bmp.hpp image/formats/bmp.cpp image/formats/ppm.cpp includes/utils/utils.hpp)
target_include_directories(photo_steganography PUBLIC includes)