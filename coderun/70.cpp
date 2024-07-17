#include <bits/stdc++.h>

using namespace std;

int main() {

    int n, target;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    cin >> target;


    int diff = 1e9;
    int ans = 0;

    for (int i = 0; i < n; ++i) {
        if (abs(a[i] - target) < diff) {
            diff = abs(a[i] - target);
            ans = a[i];
        }

    }

    cout << ans << endl;

    return 0;
}