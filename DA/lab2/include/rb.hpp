#pragma once

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace RB {

class RB {
    friend std::ostream& operator<<(std::ostream&, const RB&);
    friend bool is_correct_NLR_sequence(std::vector<int>& correct_sequence, RB& tree);
    friend bool is_correct_parents(std::unordered_map<int, int>& parents, RB& tree);
    friend void make_left_rotation(int rotation_root, RB& tree);
    friend bool is_correct_colors(std::unordered_map<int, bool>& is_black_node, RB& tree);
private:
    struct Node {
    public:
        int val;
        Node* left;
        Node* right;
        Node* parent;
        
        Node();
        Node(int val);
        Node(int val, Node* parent);
        Node(int val, Node* parent, bool is_black);

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
    std::pair<Node*&, Node*> find(int val); // MB CONST

    static void print_tree(std::ostream& os, Node* node, size_t tabs);
    std::pair<Node*&, Node*> find_left_max(Node* root) const;

    /*
        Это нужно для тестов.
    */
    void get_nodes_in_NLR_traversal_order(std::vector<Node*>& vct);
    void get_nodes_in_NLR_traversal_order(std::vector<Node*>& vct, Node* node);

    static void left_rotation(Node*& node);
    static void right_rotation(Node*& node);

    static bool is_black(Node* node);
    static bool is_red(Node* node);
    static void make_red(Node* node);
    static void make_black(Node* node);
    static Node* make_normal_ptr(Node* ptr);
    static void set_parent(Node* child, Node* parent);

    void insert_fixup(Node* node);
    bool is_correct_tree(Node* node, std::unordered_set<int>& st, int cnt);
public:

    RB();

    bool contains(int val); // MB CONST
    void insert(int val);
    void erase(int val);
    size_t size() const;
    bool empty() const;
    
    bool is_correct_tree(); // private
};

};
