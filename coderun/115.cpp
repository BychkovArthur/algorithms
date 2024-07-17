#include <bits/stdc++.h>

using namespace std;


int main() {

    int n, k;
    cin >> n >> k;
    vector<int> dp(n, 0);

    dp[0] = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = max(0, i - k); j < i; ++j) {
            dp[i] += dp[j];
        }
    }

    cout << dp[n - 1] << endl;

    return 0;
}