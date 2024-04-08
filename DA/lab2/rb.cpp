#include <iostream>
#include <vector>

/*
    TODO:

    1) Конструкторы для Node
    2) Не хранить is_black, вместо этого использовать биты указателей.
    3) Надо ли сделать size inline???
    4) добавить проверку на null для is_black, вынести это из node.
    5) ??? Сделать константными contains и find
    6) Красиво задокументировать методы

*/


namespace RB {

class RB {
    friend std::ostream& operator<<(std::ostream&, const RB&);
private:
    struct Node {
    public:
        int val;
        Node* left;
        Node* right;
        Node* parent;
        bool _is_black;
        
        Node();
        Node(int val);
        Node(int val, Node* parent);
        Node(int val, Node* parent, bool is_black);

        ~Node() = default;

        bool is_black() const;
        bool is_red() const;
    };
    Node* root;
    size_t sz;

    /**
     * Нахождение вершины, где должно быть указанное значение.
     *
     * @param val Значение, которое необходимо найти.
     * @return `pair<Node*& place, Node* parent>` where `parent` - parent for place where `val` must be,
     * `place` - `root` or `parent->left` if `perent->left->val == val` else `parent->right`
     */
    std::pair<Node*&, Node*> find(int val, Node* start); // MB CONST

    static void print_tree(std::ostream& os, Node* node, size_t tabs);
    Node* find_max(Node* root) const;
public:

    RB();

    bool contains(int val); // MB CONST
    void insert(int val);
    void erase(int val);
    size_t size() const;
    bool empty() const;
    
};

/*
    NODE
    ______________________________________________________________________________________________________________________________________
*/

RB::Node::Node() : val(0), left(nullptr), right(nullptr), parent(nullptr), _is_black(false) {}
RB::Node::Node(int val) : val(val), left(nullptr), right(nullptr), parent(nullptr), _is_black(false) {}
RB::Node::Node(int val, Node* parent) : val(val), left(nullptr), right(nullptr), parent(parent), _is_black(false) {}
RB::Node::Node(int val, Node* parent, bool is_black) : val(val), left(nullptr), right(nullptr), parent(parent), _is_black(is_black) {}

inline bool RB::Node::is_black() const {
    return _is_black; 
}

inline bool RB::Node::is_red() const {
    return !_is_black;
}

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

std::pair<RB::RB::Node*&, RB::RB::Node*> RB::find(int val, Node* start) {

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
    }
}

RB::Node* RB::find_max(Node* root) const {
    Node* curr = root;
    while (curr->right) {
        curr = curr->right;
    }
    return curr;
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
        Node* new_right = to_delete->right;
        delete to_delete;
        to_delete->right = new_right;
        to_delete->right->parent = new_parent;

    } else if (to_delete->left && !to_delete->right) {
        Node* new_left = to_delete->left;
        delete to_delete;
        to_delete->left = new_left;
        to_delete->left->parent = new_parent;

    } else {
        Node* max = find_max(to_delete->left);
        std::swap(max->val, to_delete->val);
    }
}


void RB::print_tree(std::ostream& os, Node* node, size_t tabs) {
    if (!node) {
        return;
    }
    print_tree(os, node->right, tabs + 1);
    for (size_t i = 0; i < tabs; ++i) {
        os << '\t';
    }
    os << node->val << '\n';
    print_tree(os, node->left, tabs + 1);
}


std::ostream& operator<<(std::ostream& os, const RB& tree) {
    RB::print_tree(os, tree.root, 0);
    return os;
}

/*
    TREE
    ______________________________________________________________________________________________________________________________________
*/




};



int main() {


    // int a = 5;

    // int& b = a;

    // int& c = b;

    RB::RB tree;

    std::vector<int> vct = {26, 17, 41, 30, 47, 28, 38, 35, 39, 14, 21, 10, 16, 19, 23, 7, 12, 15, 20, 3};


    for (int el : vct) {
        tree.insert(el);
    }



    std::cout << tree;
    tree.insert(3);
    std::cout << tree;
    tree.insert(-5);
    std::cout << tree;
}

