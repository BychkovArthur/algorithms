#include <bits/stdc++.h>

using namespace std;


int main() {

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    for (int i = 0; i <= n; ++i) {


        vector<int> b = a;
        for (int j = i - 1; j >= 0; --j) {
            b.push_back(a[j]);
        }


        bool is_poly = true;
        for (int j = 0; j < b.size() / 2; ++j) {
            if (b[j] != b[b.size() - 1 - j]) {
                is_poly = false;
                break;
            }
        }


        if (is_poly) {
            cout << i << endl;

            for (int j = i - 1; j >= 0; --j) {
                cout << a[j] << ' ';
            }
            return 0;
        }

    }

    return 0;
}