#include <cstdint>
#include <vector>
#include <iostream>
#include <chrono>

int64_t solve(int64_t n) {
    if (n == 1) return 0;

    int64_t x1 = solve(n - 1);
    int64_t x2 = n % 2 == 0 ? solve(n / 2) : INT64_MAX;
    int64_t x3 = n % 3 == 0 ? solve(n / 3) : INT64_MAX;

    return std::min(std::min(x1, x2), x3) + n;
}

int main() {
    int n;
    std::cin >> n;
    
    auto start = std::chrono::steady_clock::now();
    auto res = solve(n);
    auto end = std::chrono::steady_clock::now();

    std::cout << res << std::endl;
    std::cout << "Recursion without memoization: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
}

