#include <iostream>
#include <vector>

#include "../include/AVL.hpp"

using namespace avl;

int main() {
    
    AVL tree15;

    std::srand(time(NULL));
    std::vector<int64_t> vct = {
        191, 197, 59, 63, 111, 60, 112, 178, 56, 89, 24, 65, 187, 55
    };

    // for (size_t i = 0; i < 5; ++i) {
    //     tree
    // }

    for (size_t i = 0; i < 15; ++i) {
        std::cout << "Before insert" << std::endl;
        tree15.insert(vct[i]);
        // tree15.insert(std::rand() % 200);
        std::cout << "Before print" << std::endl;
        std::cout << tree15 << std::endl << std::endl << std::endl;
    }
    
    // tree15.insert(800);
    // tree15.small_left_rotation(tree15.root);
    // std::cout << tree15 << std::endl << std::endl << std::endl;
    // tree15.small_right_rotation(tree15.root);
    // std::cout << tree15 << std::endl << std::endl << std::endl;
}