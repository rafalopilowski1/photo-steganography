#include "image/image.hpp"
#include "image/formats/bmp.hpp"
#include "image/formats/ppm.hpp"

using Image = image::Image;

Image::~Image() = default;

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