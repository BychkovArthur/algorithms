#pragma once
#include <iostream>
#include <vector>

/*
    TODO:
        - НА ШАБЛОНЫ!!!
        - переписать на смарт поинтеры
        - На шаблонах придётся переделать вывод дерева, т.к. кастомные данные могут печататься, например, не в одну строку.
        - Мб, вывод дерева можно сделать без передачи текущей ноды. Типо, описать рекурсивный алгоритм вывода внутри node. Но, тогда вывод одной ноды = равен выводу дерева, что странно.

        - Подсчёт баланса при поворотах и вообще подсчёт баланса

*/

/*

    Очевидно, если баланс был 0, а стал +- 1, то мы увеличили глубину дерева.
    Значит, когда мы в родителе увидили, что у одного из сыновей стал баланс +-1, хотя раньше был другой, то изменяей баланс родителя.

    Если в одном из сыновей был баланс отличный от нуля, а стал равным нулю, то баланс родителя не меняется.

    Когда я добавляю новый лист, то у его родителя баланс может быть 0 +-1. => надо прибавить 1, если мы создали ребенка слева, и вычесть один, если создали ребенка справа


    Если у родителя один из детей nullptr, то второй или лист, или тоже nullptr

    Причём, если мы добавляем узел к корню X, то у X баланс может стать 0 +-1.


    Если в какой-то момент стало двойкой, то для родителя ничего не изменится. Т.к. 
    Было: 1, стало 2. После балансировки будет или 0 или 1.
*/

namespace avl {

const int8_t DOESNT_EXISTING_DIFF = 3;

class AVL {
    friend std::ostream& operator<<(std::ostream& os, const AVL& tree);
public:
    struct Node {
        Node* left = nullptr;
        Node* right = nullptr;
        int64_t value;
        int8_t diff = 0;

        Node(int64_t value);
    };

    Node* root = nullptr;

    void get_nodes_from_NLR_traversal(std::vector<Node*>& nodes, Node* node);

    void print_tree(std::ostream& os, const Node* node, size_t depth) const;

    bool find(const Node* node, int64_t value) const;
    void insert(Node* (&node), int64_t value);

    void small_left_rotation(Node* (&node));
    void small_right_rotation(Node* (&node));
    void big_right_left_rotation(Node* (&node));
    void big_left_right_rotation(Node* (&node));

public:
    AVL() = default;
    AVL(int64_t value);

    bool find(int64_t value) const;
    void insert(int64_t value);

    void get_nodes_from_NLR_traversal(std::vector<Node*>& nodes);
};

};