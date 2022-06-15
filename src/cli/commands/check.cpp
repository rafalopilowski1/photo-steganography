#include <string>
#include <vector>

#include "image/image.hpp"

namespace cli {
    auto check(const std::string &input_src, const std::string &message) -> void {
        auto inputFile = image::Image::get_image_unique_ptr(
                input_src);
        std::vector<image::Pixel> &pixelVector = inputFile->get_pixel_vector();
        image::check_size_ascii(pixelVector, message);
    }

}