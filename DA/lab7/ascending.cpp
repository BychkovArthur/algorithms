#include <cstdint>
#include <vector>
#include <iostream>

std::vector<int64_t> dp;


void solve(int64_t n) {
    for (int i = 2; i <= n; ++i) {
        int64_t x1 = dp[i - 1];
        int64_t x2 = i % 2 == 0 ? dp[i / 2] : INT64_MAX;
        int64_t x3 = i % 3 == 0 ? dp[i / 3] : INT64_MAX;
        dp[i] = std::min(x1, std::min(x2, x3)) + i;
    }
}

int main() {
    int n;
    std::cin >> n;
    
    std::vector<std::string> operation_types;
    dp.resize(n + 1, -1);
    dp[0] = INT64_MAX;
    dp[1] = 0;

    solve(n);

    std::cout << dp[n] << std::endl;
    while (n != 1) {
        if (dp[n - 1] + n == dp[n]) operation_types.push_back("-1"), n -= 1;
        else if (n % 2 == 0 && dp[n / 2] + n == dp[n]) operation_types.push_back("/2"), n /= 2;
        else if (n % 3 == 0 && dp[n / 3] + n == dp[n]) operation_types.push_back("/3"), n /= 3;
    }

    for (auto it = operation_types.begin(); it != operation_types.end(); ++it) {
        std::cout << *it;
        if (it < operation_types.end() - 1) std::cout << ' ';
    }
}

