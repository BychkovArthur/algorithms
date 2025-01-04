#pragma once

#include <cstdint>
#include <cstddef>
#include <vector>

class RLE {

public:
    struct Encoded {
        size_t count;
        uint8_t byte;

        bool operator==(const Encoded&) const = default;
    };

    std::vector<Encoded> Encode(const std::vector<uint8_t>& text);

    std::vector<uint8_t> Decode(const std::vector<Encoded>& encoded);
};