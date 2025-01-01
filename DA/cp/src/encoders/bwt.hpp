#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>

class BWT {

    std::vector<uint8_t> CalculateEncodedText(const std::vector<uint8_t>& text, const std::vector<std::size_t>& suffix_array);

    // size_t CalculateEncodedIndex5(const std::vector<std::size_t>& suffix_array) {
    //     return std::find(suffix_array.begin(), suffix_array.end(), 0) - suffix_array.begin();
    // }

    size_t CalculateEncodedIndex(const std::vector<uint8_t>& encoded);

    std::vector<size_t> GetDecodingPermutation(const std::vector<uint8_t>& first, const std::vector<uint8_t>& last);

    std::vector<int32_t> ConvertToVectorWithSentinel(const std::vector<uint8_t>& text);

public:

    std::vector<uint8_t> Encode(const std::vector<uint8_t>& text);

    std::vector<uint8_t> Decode(const std::vector<uint8_t>& encoded);
};