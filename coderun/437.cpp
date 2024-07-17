#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    int res = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i - 1][j - 1]) {
                dp[i][j] = 1 + min(
                    dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])
                );
            }
            res = max(res, dp[i][j]);
        }
    }

//    for (int i = 1; i <= n; ++i) {
//        for (int j = 1; j <= m; ++j) {
//            cout << dp[i][j] << ' ';
//        }
//        cout << '\n';
//    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (dp[i][j] == res) {
                std::cout << res << std::endl << i - res + 1 << ' ' << j - res + 1;
                return 0;
            }
        }
    }
}