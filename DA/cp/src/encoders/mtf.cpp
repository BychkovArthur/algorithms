#include "mtf.hpp"

#include <cstddef>

#include <utils.hpp>


std::array<uint8_t, kAlphabetSize> MTF::GetInitialOrder() {
    std::array<uint8_t, kAlphabetSize> result;
    for (size_t i = 0; i < kAlphabetSize; ++i) {
        result[i] = i;
    }
    return result;
}

std::vector<uint8_t> MTF::Encode(const std::vector<uint8_t>& text) {
    auto arr = GetInitialOrder();
    std::vector<uint8_t> result;
    result.reserve(text.size());

    for (auto byte : text) {
        result.push_back(arr[byte]);
        for (size_t i = 0; i < kAlphabetSize; ++i) {
            if (arr[i] < arr[byte]) {
                ++arr[i];
            }
        }
        arr[byte] = 0;
    }
    return result;
}

std::vector<uint8_t> MTF::Decode(const std::vector<uint8_t>& encoded) {
    auto arr = GetInitialOrder();
    std::vector<uint8_t> result;
    result.reserve(encoded.size());

    for (auto byte : encoded) {
        size_t index_to_skip = -1;

        for (size_t i = 0; i < kAlphabetSize; ++i) {
            if (arr[i] == byte) {
                result.push_back(i);
                arr[i] = 0;
                index_to_skip = i;
                break;
            }
        }
        
        for (size_t i = 0; i < kAlphabetSize; ++i) {
            if (i == index_to_skip) continue;
            if (arr[i] < byte) {
                ++arr[i];
            }
        }
    }

    return result;
}
