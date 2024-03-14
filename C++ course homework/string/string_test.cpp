#include <string>
#include <iostream>
#include "include/string.hpp"

int main() {
    // // std::string str1;

    // // std::cout << str1.length() << std::endl;
    // // std::cout << str1.size() << std::endl;
    // // std::cout << str1.capacity() << std::endl;
    // // std::cout << str1 << '|' << std::endl;
    // // std::cout << "____________________________________" << std::endl;


    // // std::string str2("abobabeba");

    // // std::cout << str2.length() << std::endl;
    // // std::cout << str2.size() << std::endl;
    // // std::cout << str2.capacity() << std::endl;
    // // std::cout << str2 << '|' << std::endl;
    // // std::cout << "____________________________________" << std::endl;


    // // std::string str3(10, 'a');
    // // str1.data();

    // // std::cout << str3.length() << std::endl;
    // // std::cout << str3.size() << std::endl;
    // // std::cout << str3.capacity() << std::endl;
    // // std::cout << str3 << '|' << std::endl;
    // // std::cout << "____________________________________" << std::endl;

    // std::string str("aaa");
    // std::string str2("aaaa");

    // std::cout << "str < str2 " << (str < str2) << std::endl;
    // // str.shrink_to_fit(); 
    // // str.find()
    // // str.pop_back();
    // std::cout << "HERE " << static_cast<int>(str.front()) << std::endl;
    // std::cout << "HERE " << static_cast<int>(str.back()) << std::endl;
    // std::cout << str.length() << std::endl;
    // std::cout << str.size() << std::endl;
    // std::cout << str.capacity() << std::endl;
    // std::cout << str << '|' << std::endl;
    // std::cout << "____________________________________" << std::endl;

    String str1;
    String str2("alkjsdfl;kasjdf");
    std::cin >> str1 >> str2;
    std::cout << str1 << ' ' << str2;
}