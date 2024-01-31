#include <bits/stdc++.h>

using namespace std;

bool isValid(int x, int y, int n) {
    return 0 <= x && x < n && 0 <= y && y < n;
}


bool isGoodSquare(int x, int y, vector<vector<int>>& a, int k, int n) {
    if (isValid(x + k - 1, y + k - 1, n)) {
        if (a[x + k - 1][y + k - 1] == a[x][y] && a[x][y] == a[x + k - 1][y] && a[x][y] == a[x][y + k - 1]) {
            return true;
        }
    }
    return false;
}

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    // cout << "HERE" << endl;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }

    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cnt += isGoodSquare(i, j, a, k, n);
        }
    }

    cout << cnt << endl;
}