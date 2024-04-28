#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>

namespace RB {

/*
    COMPARISON OPERATORS
    ______________________________________________________________________________________________________________________________________
*/

bool operator<(const std::pair<std::string, uint64_t>& a, const std::pair<std::string, uint64_t>& b) {
    return a.first < b.first;
}

bool operator>(const std::pair<std::string, uint64_t>& a, const std::pair<std::string, uint64_t>& b) {
    return b < a;
}

bool operator==(const std::pair<std::string, uint64_t>& a, const std::pair<std::string, uint64_t>& b) {
    return a.first == b.first;
}

/*
    COMPARISON OPERATORS
    ______________________________________________________________________________________________________________________________________
*/

class RB {
private:
    struct Node {
    public:
        std::pair<std::string, uint64_t> val;
        Node* left;
        Node* right;
        Node* parent;
        
        Node();
        Node(const std::pair<std::string, uint64_t>& val);
        Node(const std::pair<std::string, uint64_t>& val, bool is_black);
        Node(const std::pair<std::string, uint64_t> &val, Node* parent);
        Node(const std::pair<std::string, uint64_t>& val, Node* parent, bool is_black);

        ~Node() = default;
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
    std::pair<Node*&, Node*> find(const std::pair<std::string, uint64_t>& val); // MB CONST

    std::pair<Node*&, Node*> find_left_max(Node* root) const;

    static void left_rotation(Node*& node);
    static void right_rotation(Node*& node);

    static bool is_black(Node* node);
    static bool is_red(Node* node);
    static void make_red(Node* node);
    static void make_black(Node* node);
    static Node* make_normal_ptr(Node* ptr);
    static void set_parent(Node* child, Node* parent);

    Node*& get_ref_to_node(Node* node);

    void insert_fixup(Node* node);
    void erase_fixup(Node* parent, bool left_bh_decreased);
    void delete_tree(Node* node);

    void serialize(std::fstream& file, Node* node);
    Node* deserialize(std::fstream& file);

    enum class SERIALIZE_TYPE : int8_t {
        NULLPTR,
        BLACK,
        RED
    };


public:

    RB();
    ~RB();

    bool contains(const std::pair<std::string, uint64_t>& val); // MB CONST
    bool insert(const std::pair<std::string, uint64_t>& val);
    bool erase(const std::pair<std::string, uint64_t>& val);
    uint64_t operator[](const std::string& str);
    size_t size() const;
    bool empty() const;

    bool serialize(const std::string& filename);
    bool deserialize(const std::string& filename);
};

/*
    NODE
    ______________________________________________________________________________________________________________________________________
*/

RB::Node::Node() : left(nullptr), right(nullptr), parent(nullptr) {}
RB::Node::Node(const std::pair<std::string, uint64_t>& val) : val(val), left(nullptr), right(nullptr), parent(nullptr) {}
RB::Node::Node(const std::pair<std::string, uint64_t>& val, Node* parent) : val(val), left(nullptr), right(nullptr), parent(parent) {}
RB::Node::Node(const std::pair<std::string, uint64_t>& val, Node* parent, bool is_black) : val(val), left(nullptr), right(nullptr), parent(parent) {
    if (is_black) {
        make_black(this);
    }
}
RB::Node::Node(const std::pair<std::string, uint64_t>& val, bool is_black) : val(val), left(nullptr), right(nullptr), parent(nullptr) {
    if (is_black) {
        make_black(this);
    }
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

std::pair<RB::RB::Node*&, RB::RB::Node*> RB::find(const std::pair<std::string, uint64_t>& val) {

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

bool RB::contains(const std::pair<std::string, uint64_t>& val) {
    return find(val).first;
}

bool RB::insert(const std::pair<std::string, uint64_t>& val) {
    std::pair<Node*&, Node*> place = find(val);
    if (!place.first) {
        place.first = new Node(val, place.second);
        ++sz;
        insert_fixup(place.first);
        return true;
    }
    return false;
}

void RB::insert_fixup(Node* node) {

    while (is_red(make_normal_ptr(node->parent))) {

        Node* dad = make_normal_ptr(node->parent);
        Node* granddad = make_normal_ptr(dad->parent);

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
                if (make_normal_ptr(granddad->parent)) {
                    right_rotation(make_normal_ptr(granddad->parent)->left == granddad ? make_normal_ptr(granddad->parent)->left : make_normal_ptr(granddad->parent)->right);
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
                    left_rotation(make_normal_ptr(granddad->parent)->left == granddad ? make_normal_ptr(granddad->parent)->left : make_normal_ptr(granddad->parent)->right);
                } else {
                    left_rotation(root);
                }
            }
        }
    }
    make_black(root);
}

std::pair<RB::Node*&, RB::Node*> RB::find_left_max(Node* root) const {
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

bool RB::erase(const std::pair<std::string, uint64_t>& val) {
    std::pair<Node*&, Node*> place = find(val);
    Node*& to_delete = place.first;
    Node* new_parent = place.second;

    if (!to_delete) {
        return false;
    }

    if (!to_delete->left && !to_delete->right) {
        bool need_fixup = false;
        bool left_bh_decreased = false;
        // В случае если parent = NULL, то мы удаляем корень, никакие балансировки не нужны.
        if (is_black(to_delete) && new_parent) { // Случай 4 балансировки. Определяем с какой стороны у нашего отца необходима балансировка.
            need_fixup = true;
            left_bh_decreased = new_parent->left == to_delete;
        }

        delete to_delete;
        to_delete = nullptr;

        if (need_fixup) {
            erase_fixup(new_parent, left_bh_decreased);
        }

    } else if (!to_delete->left && to_delete->right) {
        Node* deleted_node = to_delete;
        to_delete = to_delete->right;
        set_parent(to_delete, new_parent);
        delete deleted_node;

        make_black(to_delete); // Балансировка, случай 3.

    } else if (to_delete->left && !to_delete->right) { 
        Node* deleted_node = to_delete;
        to_delete = to_delete->left;
        set_parent(to_delete, new_parent);
        delete deleted_node;

        make_black(to_delete); // Балансировка, случай 3.

    } else {
        bool need_fixup = false;
        bool left_bh_decreased = false;

        std::pair<Node*&, Node*> place = find_left_max(to_delete);
        Node* to_delete_new = place.first;


        // У удаляемой вершины нет детей. Значит возможны случаи 1 и 4.
        // Здесь в отличие от самого первого ифа (когда мы проверяем, что нет детей вообще) всегда будет родитель.
        if (is_black(to_delete_new) && !to_delete_new->left) {
            need_fixup = true;
            left_bh_decreased = place.second->left == to_delete_new;
        }

        std::swap(place.first->val, to_delete->val);

        place.first = place.first->left;
        if (place.first) {
            set_parent(place.first, place.second);
            
            make_black(place.first); // Балансировка, случай 3.
        }

        delete to_delete_new;

        if (need_fixup) {
            erase_fixup(place.second, left_bh_decreased);
        }
    }

    --sz;
    return true;
}

void RB::erase_fixup(Node* parent, bool left_bh_decreased) {
    // Изначально parent 100% не корень
    while (true) {
        Node* brother = left_bh_decreased ? parent->right : parent->left;

        if (is_red(brother)) { // Случай 4, подслучай 2. Брат - красный.
            make_red(parent);
            make_black(brother);
            
            Node*& parent_ref = get_ref_to_node(parent);
            if (left_bh_decreased) {
                left_rotation(parent_ref);
            } else {
                right_rotation(parent_ref);
            }
        
        } else { // Случай 4, подслучай 3. Брат - черный.
            if (is_black(brother->left) && is_black(brother->right)) { // Подслучай 3.1
                bool parent_was_red = is_red(parent);
                
                make_red(brother);
                make_black(parent);

                if (parent_was_red) { // Подслучай 3.1.1
                    return;
                } else {              // Подслучай 3.1.2
                    Node* new_parent = make_normal_ptr(parent->parent);

                    if (!new_parent) { // Нет родителя -> parent - корень. Значит, во всем дереве уменишьлась черная высота.
                        return;
                    }
                    left_bh_decreased = new_parent->left == parent;
                    parent = new_parent;
                }
            
            // brothers_red_son это вершина s2 в конспекте
            } else if (Node* brothers_red_son = left_bh_decreased ? brother->right : brother->left; is_red(brothers_red_son)) { // Подслучай 3.3.

                // Перекраска всех
                bool parent_was_black = is_black(parent);

                if (parent_was_black) {
                    make_black(brother);
                } else {
                    make_red(brother);
                }
                make_black(parent);
                make_black(brothers_red_son);

                // Поворотики
                Node*& parent_ref = get_ref_to_node(parent);
                if (left_bh_decreased) {
                    left_rotation(parent_ref);
                } else {
                    right_rotation(parent_ref);
                }

                return;

            } else { // Подслучай 3.2
                // Это s1 в конспекте.
                // Это сын, который находится с той же стороны относительно brother,
                // как и поддерево, в котором уменьшилась bh, относительно parent.
                Node* brother_red_son = left_bh_decreased ? brother->left : brother->right;

                make_black(brother_red_son);
                make_red(brother);

                Node*& brother_ref = get_ref_to_node(brother);
                if (left_bh_decreased) {
                    right_rotation(brother_ref);
                } else {
                    left_rotation(brother_ref);
                }
            }
        }

    }
}

RB::Node*& RB::get_ref_to_node(Node* node) {
    Node* parent = make_normal_ptr(node->parent);

    if (!parent) {
        return root;
    }
    return parent->left == node ? parent->left : parent->right;
}

void RB::left_rotation(Node*& node) {
    Node* a = node;                     // Это как в конспекте. Эти вершины обязательно должны быть.
    Node* b = node->right;              // Это как в конспекте. Эти вершины обязательно должны быть.
    Node* parent = make_normal_ptr(node->parent);

    // Node* alpha = a->left;           // Это как в конспекте. Эти вершины могут не быть.
    Node* betta = b->left;              // Это как в конспекте. Эти вершины могут не быть.
    // Node* gamma = b->right;          // Это как в конспекте. Эти вершины могут не быть.

    node = b;
    set_parent(b, parent);
    b->left = a;
    set_parent(a, b);
    a->right = betta;

    if (betta) {
        set_parent(betta, a);
    }
}

void RB::right_rotation(Node*& node) {
    Node* a = node;                     // Это как в конспекте. Эти вершины обязательно должны быть.
    Node* b = node->left;               // Это как в конспекте. Эти вершины обязательно должны быть.
    Node* parent = make_normal_ptr(node->parent);

    // Node* alpha = b->left;           // Это как в конспекте. Эти вершины могут не быть.            
    Node* betta = b->right;             // Это как в конспекте. Эти вершины могут не быть.
    // Node* gamma = a->right;          // Это как в конспекте. Эти вершины могут не быть.

    node = b;
    set_parent(b, parent);
    b->right = a;
    set_parent(a, b);
    a->left = betta;

    if (betta) {
        set_parent(betta, a);
    }
}

inline bool RB::is_black(Node* node) {
    return !node || (reinterpret_cast<size_t>(node->parent) & 1ULL); 
}

inline bool RB::is_red(Node* node) {
    return node && !(reinterpret_cast<size_t>(node->parent) & 1ULL);
}

inline void RB::make_red(Node* node) {
    node->parent = reinterpret_cast<Node*>(reinterpret_cast<size_t>(node->parent) & (UINT64_MAX - 1));
}

inline void RB::make_black(Node* node) {
    node->parent = reinterpret_cast<Node*>(reinterpret_cast<size_t>(node->parent) | 1ULL);
}

inline RB::Node* RB::make_normal_ptr(Node* ptr) {
    return reinterpret_cast<Node*>(reinterpret_cast<size_t>(ptr) & (UINT64_MAX - 1));
}

inline void RB::set_parent(Node* child, Node* parent) {
    if (is_black(child)) {
        child->parent = parent;
        make_black(child);
    } else {
        child->parent = parent;
        make_red(child);
    }
}

RB::~RB() {
    delete_tree(root);
}

void RB::delete_tree(Node* node) {

    if (!node) {
        return;
    }

    if (node->left) {
        delete_tree(node->left);
    }

    if (node->right) {
        delete_tree(node->right);
    }

    Node* parent = make_normal_ptr(node->parent);
    if (parent) {
        if (parent->left == node) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
    }
    delete node;

}

uint64_t RB::operator[](const std::string& str) {
    std::pair<Node*&, Node*> place = find({str, 0ULL});

    if (!place.first) {
        throw std::invalid_argument("Key not found");
    }

    return place.first->val.second;
}

bool RB::serialize(const std::string& filename) {
    std::fstream file;

    file.open(filename, std::ios::binary | std::ios::out | std::ios::trunc);
    // if (file.fail()) {
    //     return false;
    // }

    serialize(file, root);

    file.close();
    return true;
}

void RB::serialize(std::fstream& file, Node* node) {

    SERIALIZE_TYPE type = SERIALIZE_TYPE::NULLPTR;

    if (!node) {
        file.write(reinterpret_cast<char*>(&type), sizeof(type));
        return;
    }

    type = is_black(node) ? SERIALIZE_TYPE::BLACK : SERIALIZE_TYPE::RED;
    size_t string_size = node->val.first.size();

    file.write(reinterpret_cast<char*>(&type), sizeof(type));
    file.write(reinterpret_cast<char*>(&string_size), sizeof(string_size));
    file.write(node->val.first.c_str(), string_size);
    file.write(reinterpret_cast<char*>(&node->val.second), sizeof(node->val.second));

    if (node->left) {
        serialize(file, node->left);
    } else {
        type = SERIALIZE_TYPE::NULLPTR;
        file.write(reinterpret_cast<char*>(&type), sizeof(type));
    }

    if (node->right) {
        serialize(file, node->right);
    } else {
        type = SERIALIZE_TYPE::NULLPTR;
        file.write(reinterpret_cast<char*>(&type), sizeof(type));
    }
}

bool RB::deserialize(const std::string& filename) {
    std::fstream file;
    file.open(filename, std::ios::binary | std::ios::in);

    
    // if (file.fail()) {
    //     return false;
    // }

    delete_tree(root);
    root = deserialize(file);

    file.close();
    return true;
}

RB::Node* RB::deserialize(std::fstream& file) {
    SERIALIZE_TYPE type;
    
    file.read(reinterpret_cast<char*>(&type), sizeof(SERIALIZE_TYPE));

    if (type == SERIALIZE_TYPE::NULLPTR) {
        return nullptr;
    }

    ++sz;

    size_t string_size;
    std::string key;
    uint64_t val;

    file.read(reinterpret_cast<char*>(&string_size), sizeof(string_size));
    key.resize(string_size);
    file.read(key.data(), string_size);
    file.read(reinterpret_cast<char*>(&val), sizeof(val));

    Node* node = new Node({key, val}, type == SERIALIZE_TYPE::BLACK);
    node->left = deserialize(file);
    node->right = deserialize(file);

    if (node->left) {
        set_parent(node->left, node);
    }

    if (node->right) {
        set_parent(node->right, node);
    }

    return node;
}

/*
    TREE
    ______________________________________________________________________________________________________________________________________
*/

};


using namespace std;

void lower(string& s) {
    for (char& c : s) {
        c = tolower(c);
    }
}

int main() {
    RB::RB tree;

    string input1, input2, input3;

    while (cin >> input1) {

        if (input1.size() == 1 && input1[0] == '+') {
            cin >> input2 >> input3;
            uint64_t val = stoull(input3);

            lower(input2);

            if (tree.insert({input2, val})) {
                cout << "OK" << '\n';
            } else {
                cout << "Exist" << '\n';
            }

        } else if (input1.size() == 1 && input1[0] == '-') {
            cin >> input2;
            lower(input2);

            if (tree.erase({input2, 0ULL})) {
                cout << "OK" << '\n';

            } else {
                cout << "NoSuchWord" << '\n';
            }

        } else if (input1.size() == 1 && input1[0] == '!') {
            cin >> input2 >> input3;

            
            if (input2 == "Save") {
                tree.serialize(input3);
            } else {
                tree.deserialize(input3);
            }

            cout << "OK" << '\n';

        } else {

            lower(input1);
            try {
                uint64_t res = tree[input1];
                cout << "OK: " << res << '\n';
            
            } catch(const std::exception& e) {
                cout << "NoSuchWord" << '\n';
            }
        }
    }
}