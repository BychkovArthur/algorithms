#include <fstream>
#include <iostream>

int main() {
    std::ifstream ifs("test/static/encoded_test1.out", std::ios::binary);

    std::cout << "is_open:" << ifs.is_open() << std::endl;
    std::cout << "bad:" << ifs.bad() << " eof: " << ifs.eof() << std::endl;

    int16_t value;
    while (ifs.read(reinterpret_cast<char*>(&value), sizeof(value))) {
        std::cout << "Read value: " << value << std::endl;
    }
    std::cout << "bad:" << ifs.bad() << " eof: " << ifs.eof() << std::endl;
}