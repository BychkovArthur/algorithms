#pragma once

#include <cstddef>
#include <cstdint>
#include <fstream>
#include <memory>
#include <vector>
#include <array>

#include <bitio.hpp>
#include <const.hpp>

class BinaryTree {
public:

    struct Node {
        uint8_t byte = 0x00;
        std::unique_ptr<Node> left = nullptr;
        std::unique_ptr<Node> right = nullptr;

        Node() = default;
        Node(uint8_t byte) : byte(byte) {}
    };

    BinaryTree() = default;
    BinaryTree(std::unique_ptr<Node>&& root) : root_(std::move(root)) {}

    BinaryTree(const BinaryTree&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;
    BinaryTree(BinaryTree&&) = default;
    BinaryTree& operator=(BinaryTree&&) = default;

private: 
    std::unique_ptr<Node> root_ = nullptr;

    friend std::vector<int16_t> Serialize(const BinaryTree& bt);
    friend BinaryTree Deserialize(std::ifstream& ifs);
    friend std::array<std::vector<BitIO::Bit>, kAlphabetSize> ExtractCodesFromPrefixTree(const BinaryTree& tree);
};

std::vector<int16_t> Serialize(const BinaryTree& bt);
BinaryTree Deserialize(std::ifstream& ifs);
std::array<std::vector<BitIO::Bit>, kAlphabetSize> ExtractCodesFromPrefixTree(const BinaryTree& tree);