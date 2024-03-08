#include <iostream>


#include "AVL.hpp"

namespace avl {


AVL::Node::Node(int64_t value) : value(value) {}

AVL::AVL(int64_t value) : root(new Node(value)) {}


/*
    OUTPUT
*/

void AVL::print_tree(std::ostream& os, const Node* node, size_t depth) const {

    if (node == nullptr) { // Корень
        return;
    }

    if (node->right != nullptr) {
        print_tree(os, node->right, depth + 1);
    }
    
    for (size_t i = 0; i < depth; ++i) {
        os << '\t';
    }
    os << node->value << ", " << static_cast<int>(node->diff) << '\n';

    if (node->left != nullptr) {
        print_tree(os, node->left, depth + 1);
    }

}

std::ostream& operator<<(std::ostream& os, const AVL& tree) {
    tree.print_tree(os, tree.root, 0);
    return os;
}

/*
    OUTPUT
*/

/*
    ADD/REMOVE/FIND operations
*/

bool AVL::find(int64_t value) const {
    return find(root, value);
}

bool AVL::find(const Node* node, int64_t value) const {
    if (node == nullptr) {
        return false;
    }
    if (node->value == value) {
        return true;
    }
    // Возможно, здесь стоит сделать return  find, а вершину узнать заранее. Т.к. есть вероятность, что более простую
    // Запись компилятор соптимизирует через RVO.
    return node->value > value ? find(node->left, value) : find(node->right, value); 
}

void AVL::insert(int64_t value) {
    insert(root, value);
}

void AVL::insert(Node* (&node), int64_t value) {


    /*
        Дерево пусто.
        Создаём корень.
    */
    if (node == nullptr) {
        node = new Node(value);
        return;
    }

    // std::cout << "Current node: " << node->value << std::endl;

    if (value == node->value) {
        return;
    }

    /*
        Надо будет обновлять diff только в том случае,
        если оба ребенка есть. Иначе, diff будет обновлено
        сразу же при создании ребенка.
    */
    /*
        1) Если одного из детей нет, то очевидно, что даже если там что-то появится 
        на текущем insert, то баланс там никак не сможет стать по модулю равным 2-м.
        Поэтому, трогать что-то нет смысла.
        2) Если одного из детей нет, то появится может только один из этих детей, именно тот,
        которого сейчас нет. Причём, изменение diff при его появлении обрабатывается в момент 
        создания новой вершины.

    */
    int8_t prev_left_diff = DOESNT_EXISTING_DIFF;
    int8_t prev_right_diff = DOESNT_EXISTING_DIFF;
    Node* prev_left_node = nullptr;
    Node* prev_right_node = nullptr;
    if (node->left != nullptr) {
        prev_left_diff = node->left->diff;    
        prev_left_node = node->left;
    }
    if (node->right != nullptr) {
        prev_right_diff = node->right->diff;
        prev_right_node = node->right;
    }


    if (value < node->value) { // Спускаемся/создаём слева

        if (node->left == nullptr) {
            std::cout << "value " << value << "inserted__________________________________________________________________________1" << std::endl;
            node->left = new Node(value);
            std::cout << *this << std::endl;
            ++node->diff;
            return;
        } else {
            insert(node->left, value);
        }

    } else { // Спускаемся/создаём справа

        if (node->right == nullptr) {
            std::cout << "value " << value << "inserted__________________________________________________________________________2" << std::endl;
            node->right = new Node(value);
            std::cout << *this << std::endl;
            --node->diff;
            return;
        } else {
            insert(node->right, value);
        }
    }
    /*
        Здесь мы окажемся только в том случае, 
        если ребенок был создан не для текущей
        node. Нам нужно сделать пересчёт diff.
        |node->left->diff| = 0, 1
    */
    /*
        Предыдущий баланс был 0:
            - Он может стать +-1 или остаться нулем. Если баланс остался нулём,
            то мы попросы не зайдём ни в одно из условий, т.к. баланс не изменился, 
            менять нечего. Если же баланс стал +-1. Тогда, левое поддерево углубилось. 
            Значит, нужно изменить баланс текущего дерево, увеличив на единицу. (в 
            случае с подъёмом справа нужно будет баланс уменьшить на единицу)
        Предыдущий баланс был -1:
            - Тогда он может стать 0. В этом случае ничего делать не надо.
            - Так же, баланс может остаться -1 (без перехода в двоку). В этом случае,
            ничего менять не надо.

            - Сложный случай. Баланс был -1, после стал -2. После балансировки он будет:
                - 1. В этом случае, произошёл левый поворот. А высота поддерева никак не изменилась.
                Ничего менять не нужно.
                - 0. Произошёл левый поворот. Высота поддерева уменьшилась на единицу. У текущей
                вершины надо изменить diff, в зависимости, откуда пришли.
                - 0. Но, произошёл правый-левый поворот. В этом случае, высота ребенка уменьшилась на 


            - Если после добавления баланс станет равным 2, то всё отбалансируется,
            и баланс будет или +-1, или 0. Если баланс снова будет 1, то мы не 
            зайдём в это условие. Если же баланс станет равным 0, то мы просто
            сразу выйдём, т.к. дерево сбалансировано. Если же, баланс стал -1, то мы 
            зайдём в это уловие, но 
            - Если предыдущий баланс не менялся вообще, то мы просто не зайдём сюда.
        Предыдущий баланс был -1:
            - Аналогично с единицей.
        
        Соответственно, надо рассмотреть следующие варианты:
            БЫЛО    СТАЛО   ДЕЙСТВИЕ
              0       1     +-1 в зависимости откуда пришли.
              0      -1     +-1 в зависимости откуда пришли.
              0       0     Ничего.
              1       0     Ничего.
              1      2,0    Была единица, стала двойкой, после 
                            балансировки 0. Ничего не делаем.
              1      2,1    Ничего.
              1       1     Ничего.
             -1       0     Ничего.
             -1     -2,0    Была -1, стала -2. После балансировки
                            0. Ничего не делаем.
             -1     -2,-1   Ничего.
             -1       -1    Ничего.




        
    */

    /*
        Что-то произошло слева.
        1) Был ли поворот? В этом случае указатель будут различны.
        2) Изменилось ли значение diff?
    */

//    std::cout << "Current node value = " << node->value << "\n" << "Prev right node diff = " << static_cast<int>(prev_right_diff) << "\ncurr right node diff = " << static_cast<int>(node->left->diff) << std::endl << std::endl << std::endl;


    std::cout << "Before recalculating diff" << std::endl;
    if (prev_left_node != nullptr && node->left != prev_left_node) { // В левом поддереве была балансировка.
        Node* balance_root = node->left;
        std::cout << "1, node value = " << balance_root->value << std::endl;
        std::cout << "value to insert " << value << std::endl;
        std::cout << *this << std::endl;
        if (prev_left_diff == -1) { // Левые балансировки
            if (balance_root->diff == 0) {
                --node->diff;
            }
        }
        std::cout << "HERE" << std::endl;

        if (prev_left_diff == 1) { // Правые балансировки
            if (balance_root->diff == 0) {
                --node->diff;
            }
        }

    } else if (prev_right_node != nullptr && node->right != prev_right_node) { // В правом поддереве была балансировка.
        std::cout << "2" << std::endl;
        Node* balance_root = node->right;
        
        if (prev_right_diff == -1) { // Левые балансировки
            if (balance_root->diff == 0) {
                ++node->diff;
            }
        }

        if (prev_right_diff == 1) { // Правые балансировки
            if (balance_root->diff == 0) {
                ++node->diff;
            }
        }

    } else if (prev_left_diff != DOESNT_EXISTING_DIFF && node->left->diff != prev_left_diff) { // Что-то произошло слева
        std::cout << "3" << std::endl;
        if (node->left->diff == 0) {
            return;
        }
        ++node->diff;

    } else if (prev_right_diff != DOESNT_EXISTING_DIFF && node->right->diff != prev_right_diff) { // Что-то произошло справа
        std::cout << "4" << std::endl;
        if (node->right->diff == 0) {
            return;
        }
        --node->diff;
    }
    std::cout << *this << std::endl;
    std::cout << "After recalculating diff" << std::endl;

    /*
        Теперь, если значение по модулю равно двум, надо делать балансировку.
    */

    std::cout << "Before balancing" << std::endl;
    if (node->diff == -2) {
        Node* right_node = node->right; // Это узел b у меня в конспекте

        if (right_node->diff == 0) { // Случай 1 в конспекте
            node->diff = -1;
            right_node->diff = 1;
            small_left_rotation(node);
        }
        if (right_node->diff == -1) { // Случай 2 в конспекте
            node->diff = 0;
            right_node->diff = 0;
            small_left_rotation(node);
        }
        if (right_node->diff == 1) { // Случай 3 в конспекте
            std::cout << "IM HERE" << std::endl;
            int8_t right_left_node_diff = right_node->left->diff;

            std::cout << "C diff = " << static_cast<int>(right_left_node_diff) << std::endl;

            right_node->left->diff = 0;
            
            if (right_left_node_diff == 0) {
                node->diff = 0;
                right_node->diff = 0;
            } else if (right_left_node_diff == 1) {
                node->diff = 0;
                right_node->diff = -1;
            } else if (right_left_node_diff == -1) {
                node->diff = 1;
                right_node->diff = 0;
            }
            std::cout << "Before small rotation" << std::endl;
            std::cout << *this << std::endl;
            small_right_rotation(node->right);
            std::cout << "After small rotation" << std::endl;
            std::cout << *this << std::endl;
            small_left_rotation(node);
        }
    }

    if (node->diff == 2) {
        Node* left_node = node->left; // Это узел b у меня в конспекте

        if (left_node->diff == 0) { // Случай 1 в конспекте
            node->diff = 1;
            left_node->diff = -1;
            small_right_rotation(node);
        }

        if (left_node->diff == 1) {
            node->diff = 0;
            left_node->diff = 0;
            small_right_rotation(node);
        }

        if (left_node->diff == -1) {
            int8_t left_right_node_diff = left_node->right->diff;

            left_node->right->diff = 0;

            if (left_right_node_diff == 0) {
                node->diff = 0;
                left_node->diff = 0;
            }

            if (left_right_node_diff == 1) {
                node->diff = -1;
                left_node->diff = 0;
            }

            if (left_right_node_diff == -1) {
                node->diff = 0;
                left_node->diff = 1;
            }

            small_left_rotation(node->left);
            small_right_rotation(node);
        }
    }
    std::cout << *this << std::endl;
    std::cout << "After balancing" << std::endl;
}

void AVL::small_left_rotation(Node* (&node)) {
    Node* right_subtree = node->right; // y
    Node* right_subtree_left_subtree = right_subtree->left; // B

    node->right = right_subtree_left_subtree;
    right_subtree->left = node;
    node = right_subtree;
}

void AVL::small_right_rotation(Node* (&node)) {
    Node* left_subtree = node->left; // x
    Node* left_subtree_right_subtree = left_subtree->right; // B
    std::cout << "INSIDE" << std::endl;
    std::cout << "val = " << node->value;
    std::cout << "left val = " << left_subtree->value << std::endl;
    // std::cout << "left-right val = " << left_subtree_right_subtree->value << std::endl;

    node->left = left_subtree_right_subtree;
    left_subtree->right = node;
    node = left_subtree;
}

void AVL::get_nodes_from_NLR_traversal(std::vector<Node*>& nodes) {
    get_nodes_from_NLR_traversal(nodes, root);
}

void AVL::get_nodes_from_NLR_traversal(std::vector<Node*>& nodes, Node* node) {
    if (node == nullptr) {
        return;
    }
    nodes.push_back(node);
    get_nodes_from_NLR_traversal(nodes, node->left);
    get_nodes_from_NLR_traversal(nodes, node->right);
}

void AVL::big_right_left_rotation(Node* (&node)) {
    small_right_rotation(node->right);
    small_left_rotation(node);
}
void AVL::big_left_right_rotation(Node* (&node)) {
    small_left_rotation(node->left);
    small_right_rotation(node);
}
    

};