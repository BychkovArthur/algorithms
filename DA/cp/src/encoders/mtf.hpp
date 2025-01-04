#pragma once

#include <vector>
#include <array>
#include <cstdint>

#include <const.hpp>

class MTF {
    std::array<uint8_t, kAlphabetSize> GetInitialOrder();

public:

    std::vector<uint8_t> Encode(const std::vector<uint8_t>& text);
    std::vector<uint8_t> Decode(const std::vector<uint8_t>& encoded);
};