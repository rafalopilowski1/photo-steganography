#include <string>
#include <vector>

#include "image/image.hpp"

namespace cli {
    auto info(const std::string &fileInputPath) -> void {
        auto inputFile = image::Image::get_image_unique_ptr(
                fileInputPath);
        std::vector<image::Pixel> &pixelVector = inputFile->get_pixel_vector();

        auto path = std::filesystem::path(fileInputPath).filename();
        auto file_size = std::filesystem::file_size(fileInputPath);
        auto file_modtime = std::filesystem::last_write_time(fileInputPath);
        auto file_last_time = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(file_modtime));

        auto format_string = std::string();
        if (inputFile->image_type == image::ImageType::BMP)
            format_string = "BMP";
        else if (inputFile->image_type == image::ImageType::PPM)
            format_string = "PPM";

        std::cout << path.string() << ": " << '\n';
        std::cout << "   - Size: " << file_size << " bytes" << '\n';

        std::cout << "   - Last modified: " << std::asctime(std::localtime(&file_last_time));
        std::cout << "   - Type: " << format_string << '\n';
        std::cout << "   - Resolution: " << inputFile->image_width << "px x " << inputFile->image_height << "px\n";
    }
} 