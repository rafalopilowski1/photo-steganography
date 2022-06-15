#include <concepts>
#include <fstream>
#include <bit>
#include <algorithm>
#include <vector>

namespace utils {
    /**
     * Szablon funkcji, która odwraca bajty w liczbie (potrzebne dla *endian-independence*)
     * @tparam I Typ liczbpwy
     * @param integer Liczba
     * @return Liczba z odwróconymi bajtami
     */
    template<typename I>
    requires std::integral<I>
    auto reverse_bytes(I integer) -> I {
        I out = 0;
        /// for each byte in integer
        for (int i = 0; i < sizeof(I); ++i) {
            /// read one byte from the LSB
            I byte = (integer >> 8 * i) & 0xFF;
            /// write it to output beginning at MSB
            out |= byte << (8 * (sizeof(I) - 1 - i));
        }
        return out;
    }

    /**
     * Funkcja pozwalająca zczytać z pliku tekst (*endian-independent*)
     * @param fileInputStream Strumień pliku wejściowego
     * @param number_of_bytes Ilość bajtów do zczytania
     * @return Zczytany tekst
     */
    auto read_string_from_file(std::basic_ifstream<char> &fileInputStream,
                               unsigned int number_of_bytes) -> std::string {
        auto temp_vector = std::vector<char>(number_of_bytes);
        fileInputStream.read(temp_vector.data(), sizeof(char) * number_of_bytes);
        if (std::endian::native == std::endian::big)
            std::ranges::reverse(temp_vector);
        return std::string{temp_vector.begin(), temp_vector.end()};
    }

    /**
     * Szablon funkcji pozwalający zczytać z pliku liczbę (*endian-independent*)
     * @tparam I Typ liczbowy
     * @param fileInputStream Strumień pliku wejściowego
     * @param buffer Referencja do bufora liczby, do którego zapiszemy odczytaną liczbę
     */
    template<typename I>
    requires std::integral<I>
    auto read_number_from_file(std::basic_ifstream<char> &fileInputStream,
                               I *buffer) -> void {
        fileInputStream.read(reinterpret_cast<char *>(buffer), sizeof(I));
        if (std::endian::native == std::endian::big)
            *buffer = reverse_bytes(*buffer);
    }

    /**
     * Funkcja pozwalająca zapisać do pliku tekst
     * @param fileOutputStream Strumień pliku wyjściowego
     * @param value Referencja do tekstu, który ma być zapisany
     */
    auto write_string_to_file_output_stream(std::basic_ofstream<char> &fileOutputStream,
                                            const std::string &value) -> void {
        fileOutputStream.write(reinterpret_cast<const char *>(value.data()), sizeof(char) * value.size());
    }

    /**
     * Szablon funkcji pozwalający zapisać do pliku liczbę
     * @tparam I Typ liczbowy
     * @param fileOutputStream Strumień pliku wyjściowego
     * @param value Wskaźnik do liczby do zapisania
     */
    template<typename I>
    requires std::integral<I>
    auto write_number_to_file_output_stream(std::basic_ofstream<char> &fileOutputStream, const I *value) -> void {
        fileOutputStream.write(reinterpret_cast<const char *>(value), sizeof(I));
    }

}