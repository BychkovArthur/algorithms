#include <bits/stdc++.h>

using namespace std;


int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    vector<int> dp(n, 0);
    vector<int> prev(n, -1);
    dp[0] = 1;

    for (int i = 1; i < n; ++i) {
        int mx = 0;

        for (int j = 0; j < i; ++j) {
            if (a[i] > a[j] && dp[j] + 1 > mx) {
                mx = dp[j] + 1;
                prev[i] = j;
            }
        }
        dp[i] = max(mx, 1);
    }

    int mx = 0;
    for (int i = 0; i < n; ++i) {
        mx = max(mx, dp[i]);
    }

    int index = 0;
    for (int i = 0; i < n; ++i) {
        if (dp[i] == mx) {
            index = i;
            break;
        }
    }

    vector<int> ans;
    while (prev[index] != -1) {
        ans.push_back(a[index]);
        index = prev[index];
    }

    ans.push_back(a[index]);
    reverse(ans.begin(), ans.end());
    for (auto i : ans) {
        cout << i << ' ';
    }
    cout << endl;
}