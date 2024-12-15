#include <cstdint>
#include <vector>
#include <iostream>
#include <chrono>

std::vector<int64_t> dp;


void solve(int64_t n) {
    if (n == 1) return;

    auto check_memoization = [](int64_t n){
        if (dp[n] == -1) {
            solve(n);
        }
        return dp[n];
    };

    int64_t x1 = check_memoization(n - 1);
    int64_t x2 = n % 2 == 0 ? check_memoization(n / 2) : INT64_MAX;
    int64_t x3 = n % 3 == 0 ? check_memoization(n / 3) : INT64_MAX;

    dp[n] = std::min(std::min(x1, x2), x3) + n;
}

int main() {
    int n;
    std::cin >> n;
    
    std::vector<std::string> operation_types;
    dp.resize(n + 1, -1);
    dp[0] = INT64_MAX;
    dp[1] = 0;

    auto start = std::chrono::steady_clock::now();
    solve(n);
    auto end = std::chrono::steady_clock::now();

    std::cout << dp[n] << std::endl;
    // while (n != 1) {
    //     if (dp[n - 1] + n == dp[n]) operation_types.push_back("-1"), n -= 1;
    //     else if (n % 2 == 0 && dp[n / 2] + n == dp[n]) operation_types.push_back("/2"), n /= 2;
    //     else if (n % 3 == 0 && dp[n / 3] + n == dp[n]) operation_types.push_back("/3"), n /= 3;
    // }

    // for (auto it = operation_types.begin(); it != operation_types.end(); ++it) {
    //     std::cout << *it;
    //     if (it < operation_types.end() - 1) std::cout << ' ';
    // }
    std::cout << "Recursion with memoization: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
}

