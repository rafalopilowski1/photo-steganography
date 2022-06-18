#include "utils/utils.hpp"

namespace utils {
    auto check_if_file_readable(const std::string &file_path) -> bool {
        const auto file_permissions = std::filesystem::status(file_path).permissions();
        return (file_permissions & std::filesystem::perms::owner_read) != std::filesystem::perms::none;
    }

    auto check_if_file_writable(const std::string &file_path) -> bool {
        const auto file_permissions = std::filesystem::status(file_path).permissions();
        return (file_permissions & std::filesystem::perms::owner_write) != std::filesystem::perms::none;
    }

    auto
    read_string_from_file(std::basic_ifstream<char> &fileInputStream,
                          unsigned int number_of_bytes) -> std::string {
        auto temp_vector = std::vector<char>(number_of_bytes);
        fileInputStream.read(temp_vector.data(), sizeof(char) * number_of_bytes);
        if (std::endian::native == std::endian::big)
            std::ranges::reverse(temp_vector);
        return std::string{temp_vector.begin(), temp_vector.end()};
    }

    auto
    write_string_to_file_output_stream(std::basic_ofstream<char> &fileOutputStream,
                                       const std::string &value) -> void {
        fileOutputStream.write(reinterpret_cast<const char *>(value.data()), sizeof(char) * value.size());
    }
}