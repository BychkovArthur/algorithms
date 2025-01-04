#include "utils.hpp"

#include <const.hpp>

template <>
std::ostream& operator<<(std::ostream& os, const std::vector<uint8_t> vct) {
    for (std::size_t i = 0; i < vct.size(); ++i) {
        os << (int)vct[i];
        if (i != vct.size() - 1) {
            os << ", ";
        }
    }
    return os;
}

std::vector<uint8_t> CountSort(const std::vector<uint8_t>& text) {
    std::array<size_t, kAlphabetSize> counter{};

    for (auto character : text) {
        ++counter[character];
    }

    std::vector<uint8_t> result;
    result.reserve(text.size());
    for (size_t i = 0; i < kAlphabetSize; ++i) {
        for (size_t j = 0; j < counter[i]; ++j) {
            result.push_back(static_cast<uint8_t>(i));
        }
    }
    return result;
}

std::array<size_t, kAlphabetSize> CountBytes(const std::vector<uint8_t>& bytes) {
    std::array<size_t, kAlphabetSize> count{};
    for (auto byte : bytes) {
        ++count[byte];
    }
    return count;
}