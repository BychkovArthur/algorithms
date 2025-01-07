#include "utils.hpp"
#include <cassert>

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

std::vector<uint16_t> CountSort(const std::vector<uint16_t>& text) {
    std::array<size_t, kAlphabetSize + 1> counter{};

    for (auto character : text) {
        assert(0 <= character && character < kAlphabetSize + 1);
        ++counter[character];
    }

    std::vector<uint16_t> result;
    result.reserve(text.size());
    for (size_t i = 0; i < kAlphabetSize + 1; ++i) {
        for (size_t j = 0; j < counter[i]; ++j) {
            result.push_back(static_cast<uint16_t>(i));
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