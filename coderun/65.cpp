#include <bits/stdc++.h>

using namespace std;


int main() {

    vector<long long int> a;
    int b;
    while (cin >> b) {
        a.push_back(b);
    }

    int n = a.size();


    sort(a.begin(), a.end());

    if (a[n - 1] * a[n - 2] * a[n - 3] > a[0] * a[1] * a[n - 1]) {
        cout << a[n - 1] << ' ' << a[n - 2] << ' ' << a[n - 3] << endl;
    } else {
        cout << a[0] << ' ' << a[1] << ' ' << a[n - 1] << endl;
    }


    return 0;
}
