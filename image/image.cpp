#include "image/image.hpp"
#include "image/formats/bmp.hpp"
#include "image/formats/ppm.hpp"


image::Image::~Image() = default;

auto image::Image::get_image_unique_ptr(const std::basic_string<char> &input_src) -> std::unique_ptr<image::Image> {
    auto inputFile = std::unique_ptr<image::Image>();
    auto input_source = input_src;
    switch (image::Image::find_type(input_source)) {
        case image::ImageType::BMP:
            inputFile = std::make_unique<image::Bmp>(input_source);
            break;
        case image::ImageType::PPM:
            inputFile = std::make_unique<image::Ppm>(input_source);
            break;
        case image::ImageType::NotSupported:
            std::cerr << "File not supported!" << '\n';
            exit(1);
    }
    return inputFile;
}

auto image::Image::find_type(const std::string &filePath) -> image::ImageType {
    auto path = std::filesystem::path(filePath);
    auto ext = path.extension();
    if (ext.string() == ".bmp")
        return ImageType::BMP;
    else if (ext.string() == ".ppm")
        return ImageType::PPM;
    else
        return ImageType::NotSupported;
}