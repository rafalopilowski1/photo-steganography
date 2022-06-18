#include <string>
#include <vector>

#include "image/image.hpp"
#include "utils/utils.hpp"

namespace cli {
    auto check(const std::string &input_src, const std::string &message) -> void {
        if (utils::check_if_file_readable(input_src)) {
            auto inputFile = image::Image::get_image_unique_ptr(
                    input_src);
            std::vector<image::Pixel> &pixelVector = inputFile->get_pixel_vector();
            image::check_size_ascii(pixelVector, message, inputFile->image_type);
        } else {
            std::cerr << "Don't have enough permissions to read this file! Closing...\n";
        }
    }

}