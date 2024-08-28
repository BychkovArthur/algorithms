#include <iostream>

using ll = int64_t;



ll gcd1(ll a, ll b) {
    while (b) {
        if (b >= a) b -= a;
        else std::swap(a, b);
    }
    return a;
}

ll gcd2(ll a, ll b) {
    if (a > b) std::swap(a, b);
    while (a) {
        b = b % a;
        std::swap(a, b);
    }
    return b;
}


int main() {
    // int a, b;
    // std::cin >> a >> b;
    // std::cout << gcd1(a ,b) << std::endl;
    // std::cout << gcd2(a, b) << std::endl;

    int n = 1000;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (gcd1(i, j) != gcd2(i, j)) {
                std::cout << "Error on: (i, j) = (" << i << ", " << j << ")" << std::endl;
                std::cout << "GCD1 = " << gcd1(i, j) << std::endl;
                std::cout << "GCD2 = " << gcd2(i, j) << std::endl;
                return 0;
            }
        }
    }
}