#include <iostream>
#include <string>
#include <cstdint>

class Treap {


    struct Node {
        std::string key;
        uint64_t value;
        int priority;
        Node* left;
        Node* right;

        Node(const std::string& key, uint64_t value) : key(key), value(value), priority(rand() % 10000), left(nullptr), right(nullptr) {}
    };

    friend void print_tree(std::ostream& os, const Node* node, size_t depth);
    friend std::ostream& operator<<(std::ostream& os, const Treap& tree);

    Node* root;

    static std::pair<Node*, Node*> split(Node* tree, const std::string& key) {
        if (tree == nullptr) {
            return {nullptr, nullptr};
        }

        if (tree->key == key) {
            Node* t1 = tree->left;
            Node* t2 = tree->right;
            delete tree;
            return {t1, t2};

        } else if (tree->key < key) {
            auto pr = split(tree->right, key);
            tree->right = pr.first;
            return {tree, pr.second};
        } else {
            auto pr = split(tree->left, key);
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

    bool contains(Node* node, const std::string& key) {
        if (!node) {
            return false;
        }

        if (node->key == key) {
            return true;
        }

        return contains(key < node->key ? node->left : node->right, key);
    }

    Node* find(Node* node, const std::string& key) {
        if (!node) {
            return nullptr;
        }

        if (node->key == key) {
            return node;
        }

        return find(key < node->key ? node->left : node->right, key);
    }

public:

    Treap() : root(nullptr) {}

    bool containts(const std::string& key) {
        return contains(root, key);
    }

    Node* find(const std::string& key) {
        return find(root, key);
    }

    void insert(const std::string& key, uint64_t value) {
        auto pr = split(root, key);
        Node* res = merge(pr.first, new Node(key, value));
        root = merge(res, pr.second);
    }

    void erase(const std::string& key) {
        auto pr = split(root, key);
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
    os << node->key << ' ' << node->priority << '\n';

    if (node->left != nullptr) {
        print_tree(os, node->left, depth + 1);
    }
}

std::ostream& operator<<(std::ostream& os, const Treap& tree) {
    print_tree(os, tree.root, 0);
    return os;
}

using namespace std;

void lower(string& s) {
    for (char& c : s) {
        c = tolower(c);
    }
}

int main() {
    srand(time(NULL));

    Treap tree;

    string input1, input2, input3;

    while (cin >> input1) {
        if (input1.size() == 1 && input1[0] == '+') {
            cin >> input2 >> input3;
            uint64_t val = stoull(input3);

            lower(input2);

            if (!tree.containts(input2)) {
                tree.insert(input2, val);
                cout << "OK" << '\n';
            } else {
                cout << "Exist" << '\n';
            }

        } else if (input1.size() == 1 && input1[0] == '-') {
            cin >> input2;
            lower(input2);

            if (tree.containts(input2)) {
                tree.erase(input2);
                cout << "OK" << '\n';

            } else {
                cout << "NoSuchWord" << '\n';
            }

        } else {

            lower(input1);

            if (auto node = tree.find(input1); node) {
                cout << "OK: " << node->value << '\n';
            } else {
                cout << "NoSuchWord" << '\n';
            }
        }
    }
}