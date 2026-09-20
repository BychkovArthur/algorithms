#include "a.hpp"

#include <iostream>


namespace {

void foo() {
    std::cout << "foo from a.cpp" << std::endl;
}

} // namespace

void bar() {
    foo();
    std::cout << "bar from a.cpp" << std::endl;
}
