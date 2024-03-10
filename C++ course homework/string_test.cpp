#include <string>
#include <iostream>


int main() {
    std::string str1;

    std::cout << str1.length() << std::endl;
    std::cout << str1.size() << std::endl;
    std::cout << str1.capacity() << std::endl;
    std::cout << str1 << '|' << std::endl;
    std::cout << "____________________________________" << std::endl;


    std::string str2("abobabeba");

    std::cout << str2.length() << std::endl;
    std::cout << str2.size() << std::endl;
    std::cout << str2.capacity() << std::endl;
    std::cout << str2 << '|' << std::endl;
    std::cout << "____________________________________" << std::endl;


    std::string str3(10, 'a');
    str1.data();

    std::cout << str3.length() << std::endl;
    std::cout << str3.size() << std::endl;
    std::cout << str3.capacity() << std::endl;
    std::cout << str3 << '|' << std::endl;
    std::cout << "____________________________________" << std::endl;
}