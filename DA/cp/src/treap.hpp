#pragma once
#include <iostream>
#include <cassert>

class Treap {
    struct Node {
        int64_t value;
        int priority;
        size_t node_count;
        Node* left;
        Node* right;

        Node(const int64_t& value) : value(value), priority(rand() % 10000), node_count(1), left(nullptr), right(nullptr) {}
    };

    friend void print_tree(std::ostream& os, const Node* node, size_t depth);
    friend std::ostream& operator<<(std::ostream& os, const Treap& tree);

    Node* root;

    static int64_t GetNodeCount(const Node* node) {
        if (!node) {
            return 0;
        }
        return node->node_count;
    }

    static std::pair<Node*, Node*> split(Node* tree, const int64_t& value) {
        if (tree == nullptr) {
            return {nullptr, nullptr};
        }

        if (tree->value == value) {
            Node* t1 = tree->left;
            Node* t2 = tree->right;
            delete tree;
            return {t1, t2};

        } else if (tree->value < value) {
            auto pr = split(tree->right, value);
//            tree->node_count -= GetNodeCount(tree->right) - GetNodeCount(pr.first);

            tree->right = pr.first;
            tree->node_count = GetNodeCount(tree->left) + GetNodeCount(tree->right) + 1;
            return {tree, pr.second};
        } else {
            auto pr = split(tree->left, value);
//            tree->node_count -= GetNodeCount(tree->left) - GetNodeCount(pr.second);

            tree->left = pr.second;
            tree->node_count = GetNodeCount(tree->left) + GetNodeCount(tree->right) + 1;
            return {pr.first, tree};
        }
    }
    
    static Node* merge(Node* t1, Node* t2) {
        if (!t1 && !t2) {
            return nullptr;
        } else if (t1 && !t2) {
            return t1;
        } else if (!t1 && t2) {
            return t2;
        }

        if (t1->priority >= t2->priority) {
            auto new_right = merge(t1->right, t2);
//            t1->node_count -= GetNodeCount(t1->right) - GetNodeCount(new_right);
            t1->right = new_right;
            t1->node_count = GetNodeCount(t1->left) + GetNodeCount(t1->right) + 1;
            return t1;
        } else {
            auto new_left = merge(t1, t2->left);
//            t2->node_count -= GetNodeCount(t2->left) - GetNodeCount(new_left);
            t2->left = new_left;
            t2->node_count = GetNodeCount(t2->left) + GetNodeCount(t2->right) + 1;
            return t2;
        }
    }

    bool contains(Node* node, const int64_t& value) {
        if (!node) {
            return false;
        }

        if (node->value == value) {
            return true;
        }

        return contains(node->value < value ? node->left : node->right, value);
    }

    size_t calculate_count_of_lower(Node* node, const int64_t& value) {
        if (!node) {
            return 0;
        }
        if (node->value == value) {
            return GetNodeCount(node->left);
        }
        if (node->value < value) {
            return GetNodeCount(node->left) + 1 + calculate_count_of_lower(node->right, value);
        }
        return calculate_count_of_lower(node->left, value);
    }

    int64_t get_kth_order_statistic(Node* node, ssize_t k) {
        assert(k > 0);
        assert(GetNodeCount(node) >= k);
        assert(node != nullptr);

        if (GetNodeCount(node->left) < k) {
            if ((ssize_t)GetNodeCount(node) - (ssize_t)GetNodeCount(node->right) == k) {
                return node->value;
            }
            return get_kth_order_statistic(node->right, k - ((ssize_t)GetNodeCount(node) - (ssize_t)GetNodeCount(node->right)));
        }
        return get_kth_order_statistic(node->left, k);
    }

public:

    Treap() : root(nullptr) {}

    bool containts(const int64_t& value) {
        return contains(root, value);
    }

    void insert(const int64_t& value) {
        auto pr = split(root, value);
        Node* res = merge(pr.first, new Node(value));
        root = merge(res, pr.second);
    }

    void erase(const int64_t& value) {
        auto pr = split(root, value);
        root = merge(pr.first, pr.second);
    }

    size_t calculate_count_of_lower(const int64_t& value) {
        return calculate_count_of_lower(root, value);
    }

    int64_t get_kth_order_statistic(ssize_t k) {
        return get_kth_order_statistic(root, k);
    }

};

void print_tree(std::ostream& os, const Treap::Node* node, size_t depth);

std::ostream& operator<<(std::ostream& os, const Treap& tree);