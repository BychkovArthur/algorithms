#include "binary_tree.hpp"

#include <cstdint>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <fmt/format.h>

namespace {

constexpr int16_t kNullptrSerializationValue = -1;
constexpr int16_t kInnerNodeByteValue = -2;


void PreOrderTraversalSerialization(const std::unique_ptr<BinaryTree::Node>& node, std::vector<int16_t>& serialized) {
    if (node == nullptr) {
        throw std::logic_error("nullptr as current node in PreOrderTraversal");
    }

    if (node->left && !node->right || node->right && !node->left) {
        throw std::logic_error(fmt::format(
            "Node with value {} has only one child!\n"
            "left_child_value: {}, right_child_value: {}",
            node->byte, 
            node->left == nullptr ? -1 : node->left->byte,
            node->right == nullptr ? -1 : node->left->byte
        ));
    }

    if (node->left && node->right) {
        serialized.push_back(kInnerNodeByteValue);
    } else {
        serialized.push_back(node->byte);
    }
    
    if (node->left) {
        PreOrderTraversalSerialization(node->left, serialized);
    } else {
        serialized.push_back(kNullptrSerializationValue);
    }

    if (node->right) {
        PreOrderTraversalSerialization(node->right, serialized);
    } else {
        serialized.push_back(kNullptrSerializationValue);
    }
}

void PreOrderTraversalDeserialization(std::unique_ptr<BinaryTree::Node>& node, std::istream& ifs) {
    if (ifs.eof()) {
        throw std::logic_error("File ended, but tree is not complete");
    }
    int16_t value;
    ifs.read(reinterpret_cast<char*>(&value), sizeof(int16_t));

    if (value == kNullptrSerializationValue) {
        return;
    }
    if (value == kInnerNodeByteValue) {
        value = 0x00; // Default value for BinaryTree::Node
    }

    node = std::make_unique<BinaryTree::Node>(value);
    PreOrderTraversalDeserialization(node->left, ifs);
    PreOrderTraversalDeserialization(node->right, ifs);
}

} // namespace

std::vector<int16_t> Serialize(const BinaryTree &bt) {
    std::vector<int16_t> serialized;
    PreOrderTraversalSerialization(bt.root_, serialized);
    return serialized;
}

BinaryTree Deserialize(std::istream &ifs) {
    BinaryTree tree;
    PreOrderTraversalDeserialization(tree.root_, ifs);
    return std::move(tree);
}