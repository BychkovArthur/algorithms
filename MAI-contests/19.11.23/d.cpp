#include <bits/stdc++.h>

using namespace std;

void z_func(const vector<int>& s, vector<int>& z) {
    int n = s.size();
    z[0] = n;
    
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i < r) {
            z[i]=  min(r - i, z[i - l]);
        }
        while (i + z[i] < n and s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] >= r) {
            r = i + z[i];
            l = i;
        }
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    int n, m;
    cin >> m >> n;
    vector<int> a(n);
    vector<int> b(m);
    

    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    if (m == 1) {
        cout << n << endl;
        return 0;
    }

    vector<int> res(n - 1 + m - 1 + 1);
    int k = 0;
    for (int i = 1; i < m; ++i) {
        res[k++] = b[i] - b[i - 1];
        // res.push_back();
    }
    // res.push_back(-pow(2, 31));
    res[k++] = -pow(2, 31);
    for (int i = 1; i < n; ++i) {
        // res.push_back(a[i] - a[i - 1]);
        res[k++] = a[i] - a[i - 1];
    }

    // for (int i = 0; i < n + m + 1; ++i) {
    //     cout << res[i] << endl;
    // }
    vector<int> z(n - 1 + 1 + m - 1, 0);
    z_func(res, z);
    int cnt = 0;
    for (int i = 0; i < n + m - 1; ++i) {
        if (z[i] == m - 1) {
            ++cnt;
        }
    }

    cout << cnt << endl;
}