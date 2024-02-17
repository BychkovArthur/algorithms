#include <iostream>
#include <bitset>

constexpr size_t maxN = 121;

void sieve(std::bitset<maxN + 1>& bs, size_t n) {
    bs[0] = false;
    bs[1] = false;

    for (size_t prime = 2; prime * prime <= n; ++prime) {
        if (!bs[prime]) {
            continue;
        }

        for (size_t composite = prime * prime; composite <= n; composite += prime) {
            bs[composite] = false;
        }
    }
}

int main() {
    size_t n;
    std::cin >> n;

    std::bitset<maxN + 1> bs;
    bs.set();

    sieve(bs, n);

    for (size_t i = 0; i <= maxN; ++i) {
        std::cout << i << ": " << bs[i] << std::endl;
    }
}