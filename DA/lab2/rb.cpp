#include <iostream>

/*
    TODO:

    1) Конструкторы для Node
    2) Не хранить is_black, вместо этого использовать биты указателей.
    3) Надо ли сделать size inline???
    4) добавить проверку на null для is_black, вынести это из node.
    5) ??? Сделать константными contains и find

*/


namespace RB {

class RB {
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

    Node*& find(int val); // MB CONST

public:

    RB();


    bool contains(int val); // MB CONST
    void insert(int val);
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
    return is_black; 
}

inline bool RB::Node::is_red() const {
    return !is_black;
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

RB::RB::Node*& RB::find(int val) {

    if (!root || root->val == val) {
        return root;
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

    return left_son ? prev->left : prev->right;
}


bool RB::contains(int val) {
    return find(val);
}

void RB::insert(int val) {
    Node*& node = find(val);
    if (!node) {
        node = new Node(val, )
    }

}

/*
    TREE
    ______________________________________________________________________________________________________________________________________
*/




};



int main() {

}

