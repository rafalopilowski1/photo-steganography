# PST (Photo Steganography Toolkit)

## Usage

- `-h`: Prints out help
- `-e <path_to_file> <message>`: Encodes message in image
- `-d <path_to_file>`: Decodes message in image
- `-c <path_to_file> <message>`: Checks if message can be encoded in image
- `-i <path_to_file>`: Prints out image metadata

## Compatibility table

|      Tested with:       | Footnotes |
|:-----------------------:|:---------:|
| MSVC ver. 142 (VS 2019) |           |
| MSVC `clang-cl` 12.0.0  |    1.     |
|       MinGW 11.0        |           |
|       GCC 12.1.1        |           |
|       Clang 14.0        |           |

### Footnotes

1: Requires enabling exceptions support in compiler options: `/EHa`