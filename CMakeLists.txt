cmake_minimum_required(VERSION 3.19)
project(photo_steganography)

set(CMAKE_CXX_STANDARD 20)

add_executable(photo_steganography main.cpp cli/commands/help.cpp  cli/flags.cpp  cli/commands/encode.cpp  cli/commands/decode.cpp  cli/commands/check.cpp  cli/commands/info.cpp  image/flags/image_formats.cpp  image/formats/ppm.cpp includes/image/image.hpp)
target_include_directories(photo_steganography PUBLIC includes)