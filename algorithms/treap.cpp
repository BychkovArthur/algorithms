#include <iostream>

class Treap {


    struct Node {
        int value;
        int priority;
        Node* left;
        Node* right;

        Node(const int& value) : value(value), priority(rand() % 10000), left(nullptr), right(nullptr) {}
    };

    friend void print_tree(std::ostream& os, const Node* node, size_t depth);
    friend std::ostream& operator<<(std::ostream& os, const Treap& tree);

    Node* root;

    static std::pair<Node*, Node*> split(Node* tree, const int& value) {
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
            tree->right = pr.first;
            return {tree, pr.second};
        } else {
            auto pr = split(tree->left, value);
            tree->left = pr.second;
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
            t1->right = merge(t1->right, t2);
            return t1;
        } else {
            t2->left = merge(t2->left, t1);
            return t2;
        }
    }

    bool contains(Node* node, const int& value) {
        if (!node) {
            return false;
        }

        if (node->value == value) {
            return true;
        }

        return contains(node->value < value ? node->left : node->right, value);
    }

public:

    Treap() : root(nullptr) {}

    bool containts(const int& value) {
        return contains(root, value);
    }

    void insert(const int& value) {
        auto pr = split(root, value);
        Node* res = merge(pr.first, new Node(value));
        root = merge(res, pr.second);
    }

    void erase(const int& value) {
        auto pr = split(root, value);
        root = merge(pr.first, pr.second);
    }
};

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
    os << node->value << ' ' << node->priority << '\n';

    if (node->left != nullptr) {
        print_tree(os, node->left, depth + 1);
    }
}

std::ostream& operator<<(std::ostream& os, const Treap& tree) {
    print_tree(os, tree.root, 0);
    return os;
}


int main() {
    srand(time(NULL));

    Treap t;

    for (int i = 0; i < 10; ++i) {
        t.insert(i);
    }

    std::cout << t << std::endl;
    std::cout << "________________________________________________________________" << std::endl;
    t.erase(5);

    std::cout << t << std::endl;
}