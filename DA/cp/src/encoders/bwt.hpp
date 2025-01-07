#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>

class BWT {

private:
    std::vector<uint8_t> CalculateEncodedText(const std::vector<uint8_t>& text, const std::vector<std::size_t>& suffix_array);

    size_t CalculateEncodedIndex(const std::vector<std::size_t>& suffix_array);

    std::vector<size_t> GetDecodingPermutation(const std::vector<uint16_t>& first, const std::vector<uint16_t>& last);

    std::vector<int32_t> ConvertToVectorWithSentinel(const std::vector<uint8_t>& text);

public:
    struct Encoded {
        std::vector<uint8_t> text;
        size_t index; /*
                       * 0-индексация относительно text
                       * Относительно suffix_array здесь -1 - индексация :) Проще сказать, невалидный он.
                       */
    };

    Encoded Encode(const std::vector<uint8_t>& text);

    std::vector<uint8_t> Decode(const Encoded& encoded);
};