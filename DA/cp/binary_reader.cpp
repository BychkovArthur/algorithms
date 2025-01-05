#include <fstream>
#include <iostream>

int main() {
    std::ifstream ifs("build/aboba.bin", std::ios::binary);
//    std::ifstream ifs("test/static/111222333.bin", std::ios::binary);
//
    std::cout << "is_open:" << ifs.is_open() << std::endl;
    std::cout << "bad:" << ifs.bad() << " eof: " << ifs.eof() << std::endl;

    uint8_t value1;
    ifs.read(reinterpret_cast<char*>(&value1), sizeof (value1));
    std::cout << "level: " << (int)value1 << std::endl;

    int16_t value;
    for (int i = 0; i < 11; ++i) {
        ifs.read(reinterpret_cast<char*>(&value), sizeof(value));
        std::cout << "Read value: " << value << std::endl;
    }
//        std::cout << "bad:" << ifs.bad() << " eof: " << ifs.eof() << std::endl;
    while (ifs.read(reinterpret_cast<char*>(&value1), sizeof(value1))) {
        std::cout << (int)value1 << ' ';
    }

//    uint8_t byte;
//    while(ifs.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
//        std::cout << "READ: " << (int)byte << std::endl;
//    }
}