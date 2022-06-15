cmake_minimum_required(VERSION 3.19)
project(photo_steganography)

set(CMAKE_CXX_STANDARD 20)

add_executable(photo_steganography src/main.cpp src/cli/commands/help.cpp src/cli/flags.cpp src/cli/commands/encode.cpp src/cli/commands/decode.cpp src/cli/commands/check.cpp src/cli/commands/info.cpp src/includes/image/image.hpp src/image/image.cpp src/includes/image/formats/ppm.hpp src/includes/image/formats/bmp.hpp src/image/formats/bmp.cpp src/image/formats/ppm.cpp src/includes/utils/utils.hpp)
target_include_directories(photo_steganography PUBLIC src/includes)