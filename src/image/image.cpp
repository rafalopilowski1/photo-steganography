#include <iostream>
#include <vector>
#include <string>

#include "image/image.hpp"
#include "image/formats/bmp.hpp"
#include "image/formats/ppm.hpp"

using Image = image::Image;

auto image::check_size_ascii(const std::vector<image::Pixel> &pixelVector, const std::string &message,
                             const ImageType &imageType) -> bool {
    auto messageLenBits = message.size() * 8;
    /// Zapisywanie w formacie BMP ma ograniczenie 64 MB - ograniczenia pola `Metadata`
    auto imageSizePotencial = imageType == ImageType::PPM ? (pixelVector.size() * 3) : (65535);
    if (messageLenBits <= imageSizePotencial) {
        std::cout << "Given message (" << messageLenBits << " bits) can be written into this image ("
                  << imageSizePotencial << " bits)" << '\n';
        return true;
    } else {
        std::cout << "Given message (" << messageLenBits << " bits) can't be written into this image ("
                  << imageSizePotencial << " bits)" << '\n';
        return false;
    }
}

auto Image::get_image_unique_ptr(const std::basic_string<char> &input_src) -> std::unique_ptr<Image> {
    auto inputFile = std::unique_ptr<Image>();
    auto input_source = input_src;
    switch (Image::find_type(input_source)) {
        case ImageType::BMP:
            inputFile = std::make_unique<image::Bmp>(input_source);
            break;
        case ImageType::PPM:
            inputFile = std::make_unique<image::Ppm>(input_source);
            break;
        case ImageType::NotSupported:
            std::cerr << "File not supported!" << '\n';
            exit(1);
    }
    return inputFile;
}

auto Image::find_type(const std::string &filePath) -> ImageType {
    auto path = std::filesystem::path(filePath);
    auto ext = path.extension();
    if (ext.string() == ".bmp")
        return ImageType::BMP;
    else if (ext.string() == ".ppm")
        return ImageType::PPM;
    else
        return ImageType::NotSupported;
}

