#include "rle.hpp"
#include <cstddef>

std::vector<RLE::Encoded> RLE::Encode(const std::vector<uint8_t>& text) {
    std::vector<Encoded> result;
    size_t i = 0;

    while (i < text.size()) {
        size_t j = i + 1;
        while (j < text.size() && text[i] == text[j]) ++j;
        result.push_back(Encoded{
            .count = j - i,
            .byte = text[i],
        });
        i = j;
    }
    return result;
}

std::vector<uint8_t> RLE::Decode(const std::vector<RLE::Encoded>& encoded) {
    std::vector<uint8_t> result;

    for (const auto& data : encoded) {
        for (size_t i = 0; i < data.count; ++i) {
            result.push_back(data.byte);
        }
    }
    return result;
}
