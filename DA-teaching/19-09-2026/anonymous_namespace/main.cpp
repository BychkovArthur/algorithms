#include "a.hpp"

#include <iostream>


void foo() {
    std::cout << "foo from main.cpp" << std::endl;
}


int main() {
    foo();
    bar();
}