#include <iostream>
#include <vector>

#include "rb.hpp"

/*
    TODO:

    1) Конструкторы для Node
    2) Не хранить is_black, вместо этого использовать биты указателей.
    3) Надо ли сделать size inline???
    5) ??? Сделать константными contains и find
    6) Красиво задокументировать методы

    7) Надо что то сделать с методами для тестирования. В классе их оставлять как то глупо.

    4) добавить проверку на null для is_black, вынести это из node. +
    8) Проверять значение родителей. ++++
    9) Заменить присваивание цвета на метод +++
*/



namespace RB {



/*
    NODE
    ______________________________________________________________________________________________________________________________________
*/

RB::Node::Node() : val(0), left(nullptr), right(nullptr), parent(nullptr), _is_black(false) {}
RB::Node::Node(int val) : val(val), left(nullptr), right(nullptr), parent(nullptr), _is_black(false) {}
RB::Node::Node(int val, Node* parent) : val(val), left(nullptr), right(nullptr), parent(parent), _is_black(false) {}
RB::Node::Node(int val, Node* parent, bool is_black) : val(val), left(nullptr), right(nullptr), parent(parent), _is_black(is_black) {}

/*
    NODE
    ______________________________________________________________________________________________________________________________________
*/



/*
    TREE
    ______________________________________________________________________________________________________________________________________
*/


RB::RB() : root(nullptr), sz(0) {}


size_t RB::size() const {
    return sz;
}

bool RB::empty() const {
    return sz == 0;
}

std::pair<RB::RB::Node*&, RB::RB::Node*> RB::find(int val) {

    if (!root || root->val == val) {
        return {root, nullptr};
    }

    Node* curr = root;
    Node* prev = nullptr;
    bool left_son = false;
    while (curr) {
        if (val < curr->val) {
            prev = curr;
            curr = curr->left;
            left_son = true;
        } else if (val > curr->val) {
            prev = curr;
            curr = curr->right;
            left_son = false;
        } else {
            break;
        }
    }    

    if (left_son) {
        return {prev->left, prev};
    } else {
        return {prev->right, prev};
    }
}


bool RB::contains(int val) {
    return find(val).first;
}

void RB::insert(int val) {
    std::pair<Node*&, Node*> place = find(val);
    if (!place.first) {
        place.first = new Node(val, place.second);
        ++sz;
        insert_fixup(place.first);
    }
}

void RB::insert_fixup(Node* node) {

    while (is_red(node->parent)) {

        Node* dad = node->parent;
        Node* granddad = dad->parent;

        if (granddad->left == dad) {
            Node* uncle = granddad->right;
            if (is_red(uncle)) {
                make_black(uncle);
                make_black(dad);
                make_red(granddad);
                node = granddad;
            } else {
                if (dad->right == node) {
                    std::swap(dad, node);
                    left_rotation(granddad->left);
                }
                make_red(granddad);
                make_black(dad);
                if (granddad->parent) {
                    right_rotation(granddad->parent->left == granddad ? granddad->parent->left : granddad->parent->right);
                } else {
                    right_rotation(root);
                }
            }

        } else {
            Node* uncle = granddad->left;
            if (is_red(uncle)) {
                make_black(uncle);
                make_black(dad);
                make_red(granddad);
                node = granddad;
            } else {
                if (dad->left == node) {
                    std::swap(dad, node);
                    right_rotation(granddad->right);
                }
                make_red(granddad);
                make_black(dad);
                if (granddad->parent) {
                    left_rotation(granddad->parent->left == granddad ? granddad->parent->left : granddad->parent->right);
                } else {
                    left_rotation(root);
                }
            }
        }
    }
    root->_is_black = true;
}

std::pair<RB::Node*&, RB::Node*> RB::find_left_max(Node* root) const { // Здесь надо сделать так же по красоте, как с обычным find. Надо сделать через ссылку.
    if (!root->left->right) {
        return {root->left, root};
    }
    Node* curr = root->left;
    Node* prev = nullptr;

    while (curr->right) {
        prev = curr;
        curr = curr->right;
    }

    return {prev->right, prev};
}

void RB::erase(int val) {
    std::pair<Node*&, Node*> place = find(val);
    Node*& to_delete = place.first;
    Node* new_parent = place.second;

    if (!to_delete) {
        return;
    }

    if (!to_delete->left && !to_delete->right) {
        delete to_delete;
        to_delete = nullptr;

    } else if (!to_delete->left && to_delete->right) {
        Node* deleted_node = to_delete;
        to_delete = to_delete->right;
        to_delete->parent = new_parent;
        delete deleted_node;

    } else if (to_delete->left && !to_delete->right) {
        // std::cout << "HERE" << std::endl;
        // std::cout << "TO DELETE VAL = " << to_delete->val << " TO DELETE LEFT VAL = " << to_delete->left->val << std::endl; 
        Node* deleted_node = to_delete;
        to_delete = to_delete->left;
        to_delete->parent = new_parent;
        delete deleted_node;

    } else {
        std::pair<Node*&, Node*> place = find_left_max(to_delete);
        Node* to_delete_new = place.first;
        std::swap(to_delete_new->val, to_delete->val);
        place.first = to_delete_new->left;
        if (place.first) {
            place.first->parent = place.second;
            delete to_delete_new;
        }
    }

    --sz;
}


void RB::print_tree(std::ostream& os, Node* node, size_t tabs) {
    if (!node) {
        return;
    }
    print_tree(os, node->right, tabs + 1);
    for (size_t i = 0; i < tabs; ++i) {
        os << '\t';
    }
    if (node->parent) {
        os << "\e[1;31m" << node->parent->val << "\e[0m" << ';';
    }
    os << "\e[1;32m" << node->val << "\e[0m" << '\n';
    print_tree(os, node->left, tabs + 1);
}


std::ostream& operator<<(std::ostream& os, const RB& tree) {
    RB::print_tree(os, tree.root, 0);
    return os;
}

void RB::get_nodes_in_NLR_traversal_order(std::vector<RB::Node*>& vct) {
    get_nodes_in_NLR_traversal_order(vct, root);
}

void RB::get_nodes_in_NLR_traversal_order(std::vector<RB::Node*>& vct, Node* node) {
    if (!node) {
        return;
    }
    vct.push_back(node);
    get_nodes_in_NLR_traversal_order(vct, node->left);
    get_nodes_in_NLR_traversal_order(vct, node->right);
}

void RB::left_rotation(Node*& node) {
    Node* a = node;                     // Это как в конспекте. Эти вершины обязательно должны быть.
    Node* b = node->right;              // Это как в конспекте. Эти вершины обязательно должны быть.
    Node* parent = node->parent;

    // Node* alpha = a->left;           // Это как в конспекте. Эти вершины могут не быть.
    Node* betta = b->left;              // Это как в конспекте. Эти вершины могут не быть.
    // Node* gamma = b->right;          // Это как в конспекте. Эти вершины могут не быть.

    node = b;
    b->parent = parent;
    b->left = a;
    a->parent = b;
    a->right = betta;

    if (betta) {
        betta->parent = a;
    }
}

void RB::right_rotation(Node*& node) {
    Node* a = node;                     // Это как в конспекте. Эти вершины обязательно должны быть.
    Node* b = node->left;               // Это как в конспекте. Эти вершины обязательно должны быть.
    Node* parent = node->parent;

    // Node* alpha = b->left;           // Это как в конспекте. Эти вершины могут не быть.            
    Node* betta = b->right;             // Это как в конспекте. Эти вершины могут не быть.
    // Node* gamma = a->right;          // Это как в конспекте. Эти вершины могут не быть.

    node = b;
    b->parent = parent;
    b->right = a;
    a->parent = b;
    a->left = betta;

    if (betta) {
        betta->parent = a;
    }
}

inline bool RB::is_black(Node* node) {
    return !node || node->_is_black; 
}

inline bool RB::is_red(Node* node) {
    return node && !node->_is_black;
}

inline void RB::make_red(Node* node) {
    node->_is_black = false;
}
inline void RB::make_black(Node* node) {
    node->_is_black = true;
}

/*
    TREE
    ______________________________________________________________________________________________________________________________________
*/
};
