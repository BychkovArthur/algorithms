#include "huffman.hpp"

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <fmt/format.h>

#include <utils.hpp>
#include <const.hpp>

#include <bitio.hpp>

namespace {

struct NodesByCount {
    std::unique_ptr<BinaryTree::Node> node;
    std::size_t count;
};

NodesByCount BuildParentNode(NodesByCount&& left, NodesByCount&& right) {
    auto parent = std::make_unique<BinaryTree::Node>();
    parent->left = std::move(left.node);
    parent->right = std::move(right.node);

    return {
        .node = std::move(parent),
        .count = left.count + right.count
    };
}

bool NotProcessedAtLeast(const size_t not_processed_count, const size_t vector_size, const size_t processed_count) {
    return vector_size - processed_count >= not_processed_count;
}

BinaryTree BuildPrefixTree(const std::vector<uint8_t>& text) {
    std::vector<NodesByCount> vct1;
    std::vector<NodesByCount> vct2;
    vct1.reserve(kAlphabetSize);
    vct2.reserve(kAlphabetSize);

    const auto frequency = CountBytes(text);

    for (size_t byte = 0; byte < kAlphabetSize; ++byte) {
        if (frequency[byte]) {
            vct1.emplace_back(std::make_unique<BinaryTree::Node>(byte), frequency[byte]);
        }
    }
    std::sort(
        vct1.begin(),
        vct1.end(),
        [](const NodesByCount& lhs, const NodesByCount& rhs) { 
            return lhs.count < rhs.count;
        }
    );

    if (vct1.size() == 1) {
        throw std::logic_error("Invalid input text. It's contains only 1 different byte");
    }

    size_t processed1 = 0;
    size_t processed2 = 0;
    while (NotProcessedAtLeast(2, vct1.size() + vct2.size(), processed1 + processed2)) {
        size_t count1 = UINT64_MAX; // Оба из vct1 
        size_t count2 = UINT64_MAX; // Оба из vct2
        size_t count3 = UINT64_MAX; // Берез из обоих

        if (NotProcessedAtLeast(2, vct1.size(), processed1)) {
            count1 = vct1[processed1].count + vct1[processed1 + 1].count;
        }
        if (NotProcessedAtLeast(2, vct2.size(), processed2)) {
            count2 = vct2[processed2].count + vct2[processed2 + 1].count;
        }
        if (
            NotProcessedAtLeast(1, vct1.size(), processed1) &&
            NotProcessedAtLeast(1, vct2.size(), processed2)
        ) {
            count3 = vct1[processed1].count + vct2[processed2].count;
        }

        size_t mn = std::min({count1, count2, count3});
        if (mn == UINT64_MAX) {
            throw std::logic_error("Not a single pair get out");
        }

        if (mn == count1) {
            vct2.push_back(
                BuildParentNode(
                    std::move(vct1[processed1]),
                    std::move(vct1[processed1 + 1])));
            processed1 += 2;

        } else if (mn == count2) {
            vct2.push_back(
                BuildParentNode(
                    std::move(vct2[processed2]),
                    std::move(vct2[processed2 + 1])));
            processed2 += 2;

        } else {
            vct2.push_back(
                BuildParentNode(
                    std::move(vct1[processed1]),
                    std::move(vct2[processed2])));
            ++processed1;
            ++processed2;
        }
    }

    return BinaryTree(std::move(vct2[processed2].node));
}

void CodesExtracter(const std::unique_ptr<BinaryTree::Node>& node, std::vector<BitIO::Bit>& bits, std::array<std::vector<BitIO::Bit>, kAlphabetSize>& codes) {
    if (!node->left && !node->right) {
        codes[node->byte] = bits;
        return;
    }

    assert(node->left && node->right); // Дерево полное. Должны быть оба ребенка
    
    bits.push_back(BitIO::Bit::kZero);
    CodesExtracter(node->left, bits, codes);
    bits.pop_back();

    bits.push_back(BitIO::Bit::kOne);
    CodesExtracter(node->right, bits, codes);
    bits.pop_back();
}

} // namespace

std::array<std::vector<BitIO::Bit>, kAlphabetSize> ExtractCodesFromPrefixTree(const BinaryTree& tree) {
    std::array<std::vector<BitIO::Bit>, kAlphabetSize> codes;
    std::vector<BitIO::Bit> bits;

    CodesExtracter(tree.root_, bits, codes);
    assert(bits.empty());

    return codes;
}

Huffman::Encoded Huffman::Encode(const std::vector<uint8_t>& text) const {
    if (text.empty()) {
        throw std::logic_error("Input text is empty");
    }

    auto tree = BuildPrefixTree(text);
    const auto codes = ExtractCodesFromPrefixTree(tree);
    
    std::vector<uint8_t> encoded;
    uint8_t bits_writed = 0;
    BitIO stream(encoded);

    for (const auto& byte : text) {
        for (const auto& bit : codes[byte]) {
            stream.Write(bit);
            ++bits_writed;
            bits_writed %= 8;
        }
    }
    stream.FlushOutput();

    return {
        .model = std::move(tree),
        .text = std::move(encoded),
        .alignment = (uint8_t)(8 - (int)bits_writed) % 8
    };
}

std::vector<uint8_t> Huffman::Decode(Huffman::Encoded& encoded) const {
    std::vector<uint8_t> decoded;
    auto& tree = encoded.model;
    auto& encoded_text = encoded.text;
    BitIO stream(encoded_text);

    /*
    * Делаю полную хрень(((
    */
    auto& root = tree.GetRoot();
    auto root_raw = root.get();
    auto current_node = root_raw;

    if (encoded.alignment == 0) {
        while (!stream.Eof()) {
            const auto bit = stream.Read();
            if (bit == BitIO::Bit::kZero) {
                if (!current_node->left) {
                    throw std::logic_error("Invalid tree (left not found)");
                }
                current_node = current_node->left.get();
            } else {
                if (!current_node->right) {
                    throw std::logic_error("Invalid tree (right not found)");
                }
                current_node = current_node->right.get();
            }

            if (!current_node->left && !current_node->right) {
                decoded.push_back(current_node->byte);
                current_node = root_raw;
            }
        }
    } else {
        for (size_t i = 0; i < 8 * (encoded_text.size() - 1) + (8 - encoded.alignment); ++i) {
            const auto bit = stream.Read();
            if (bit == BitIO::Bit::kZero) {
                if (!current_node->left) {
                    throw std::logic_error("Invalid tree (left not found)");
                }
                current_node = current_node->left.get();
            } else {
                if (!current_node->right) {
                    throw std::logic_error("Invalid tree (right not found)");
                }
                current_node = current_node->right.get();
            }

            if (!current_node->left && !current_node->right) {
                decoded.push_back(current_node->byte);
                current_node = root_raw;
            }
        }
    }
    
    assert(current_node == root_raw);

    return decoded;
}