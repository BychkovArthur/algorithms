#include <bits/stdc++.h>

using namespace std;


int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<long long int>> dp(n + 2, vector<long long int>(m + 2, 0ll));

    dp[2][2] = 1;

    for (int i = 2; i < n + 2; ++i) {
        for (int j = 2; j < m + 2; ++j) {
            dp[i][j] += dp[i - 2][j - 1] + dp[i - 1][j - 2];
        }
    }

    cout << dp[n + 1][m + 1];
}