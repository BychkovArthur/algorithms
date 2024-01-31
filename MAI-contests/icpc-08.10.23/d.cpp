#include <bits/stdc++.h>

using namespace std;

int main() {
    long long int q, r;
    cin >> q >> r;

    set<long long int> a;
    // cout << 0 % 15 << endl;
    // for (long long int i = 1; i * i <= (q - 1); ++i) {
    //     if ((q - 1) > 0 && (q - 1) % i == 0) {
    //         a.insert(i);
    //         a.insert( (q - 1) / i);
    //     }
    // }
    // for (long long int el : a) {
    //     cout << el << " ";
    // }
    // cout << endl;
    // cout << (q * r - q) << endl;
    for (long long int i = 1; i * i <= (q * r - q); ++i) {
        if ((q * r - q) > 0 && (q * r - q) % i == 0 ) {
            a.insert(i);
            a.insert( (q * r - q) / i );
        }
    }
    cout << a.size() << endl;

}