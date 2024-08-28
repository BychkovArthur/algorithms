#include <iostream>

using namespace std;

template<typename T>
T bpow(T base, long long int power) {
    T res = 1;
    while (power) {
        if (power & 1) res *= base;
        base *= base;
        power >>= 1;
    }
    return res;
}



int main() {

    std::cout << bpow(2, 10) << std::endl;
    std::cout << bpow(2, 14) << std::endl;
    std::cout << bpow(5, 5) << std::endl;
    std::cout << bpow(1.1, 10) << std::endl;

}