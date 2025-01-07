#pragma once

#include <vector>
#include <array>
#include <cstdint>

#include <const.hpp>

class MTF {
    template<typename T>
    std::array<T, kAlphabetSize> GetInitialOrder() {
        std::array<T, kAlphabetSize> result;
        for (size_t i = 0; i < kAlphabetSize; ++i) {
            result[i] = i;
        }
        return result;
    }

public:

    std::vector<uint8_t> Encode(const std::vector<uint8_t>& text);
    std::vector<uint8_t> Decode(const std::vector<uint8_t>& encoded);
};