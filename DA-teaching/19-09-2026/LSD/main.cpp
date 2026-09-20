#include "lsd_sort.h"

#include <iostream>


int main() {
    size_t n;
    std::cin >> n;

    std::vector<size_t> a(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    LSD(a);

    for (size_t i = 0; i < n; ++i) {
        std::cout << a[i] << '\n';
    }
    std::cout << std::endl;

    return 0;
}