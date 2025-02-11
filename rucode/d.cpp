#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    int bob = n / 2;
    int alice = n - n / 2;
    int i = 0;
    int letter = 0;
    char c = 0;

    set<int> ls;
    for (int j = 0; j < n; ++j)
        ls.insert(65 + j);

    for (; i < (bob - k) * 2; ++i) {
        if (i % 2 == 0) { // alice
            cout << (char)(65 + i) << endl;
            ls.erase(65 + i);
        } else { // bob
            cin >> c;
            ls.erase(65 + i);
        }
    }

    for (; i < n; ++i) {
        if (i % 2 == 0) { // alice
            if (ls.count(65 + i + 1)) {
                cout << (char)(65 + i + 1) << endl;
                ls.erase(65 + i + 1);
            } else {
                cout << (char)(*ls.begin()) << endl;
                ls.erase(ls.begin());
            }
        } else { // bob
            cin >> c;
            ls.erase((int)c);
        }
    }
}