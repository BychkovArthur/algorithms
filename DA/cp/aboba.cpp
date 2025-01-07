#include <bits/stdc++.h>
#include <cstdint>

using namespace std;

int main() {


    uint8_t b1 = 0b11111111;
    int8_t b2 = 0b11111111;

    uint32_t b3;


    b3 = 123123123;
    b3 ^= b1;
    std::cout << b3 << std::endl;


    b3 = 123123123;
    b3 ^= b2;
    std::cout << b3 << std::endl;
}