#include "treap.hpp"

std::ostream& operator<<(std::ostream& os, const Treap& tree) {
    print_tree(os, tree.root, 0);
    return os;
}

void print_tree(std::ostream& os, const Treap::Node* node, size_t depth) {
    if (node == nullptr) { // Корень
        return;
    }
    if (node->right != nullptr) {
        print_tree(os, node->right, depth + 1);
    }

    for (size_t i = 0; i < depth; ++i) {
        os << '\t';
    }
    os << node->value << ' ' << node->priority << ' ' << node->node_count << '\n';

    if (node->left != nullptr) {
        print_tree(os, node->left, depth + 1);
    }
}