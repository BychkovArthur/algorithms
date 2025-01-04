#pragma once

#include <vector>
#include <cstdint>
#include <binary_tree.hpp>

class Huffman {
public:
    struct Encoded {
        BinaryTree model;
        std::vector<uint8_t> text;
        uint8_t alignment;        // Сколько битов я не дописал в последнем байте.
                                  // Я тут делаю дополнение незначащими нулями. 
                                  // Если я дополнил 5-ю нулями, то alignment = 5
    };

    Encoded Encode(const std::vector<uint8_t>& text) const;

    std::vector<uint8_t> Decode(const Encoded& encoded) const;
};