# PST (Photo Steganography Toolkit)

## Usage

- `-h`: Prints out help
- `-e <path_to_file> <message>`: Encodes message in image
- `-d <path_to_file>`: Decodes message in image
- `-c <path_to_file> <message>`: Checks if message can be encoded in image
- `-i <path_to_file>`: Prints out image metadata

## Supported formats

- P3 PPM
- BMP

## Compatibility table

- `Doxygen` documentation works best with `clang` installed (more accurate code parsing)

|      Tested with:       | Footnotes |
|:-----------------------:|:---------:|
| MSVC ver. 142 (VS 2019) |     -     |
| MSVC `clang-cl` 12.0.0  |    1.     |
|        MinGW 9.0        |     -     |
|       GCC 12.1.1        |     -     |
|       Clang 14.0        |     -     |

### Footnotes

1: Requires enabling exceptions support in compiler options: `/EHa`

## Disclosure

Image samples provided by © [filesamples.com](https://filesamples.com)

Sources:
 - [https://filesamples.com/formats/bmp](https://filesamples.com/formats/bmp)
 - [https://filesamples.com/formats/ppm](https://filesamples.com/formats/ppm) (converted from P6 to P3)