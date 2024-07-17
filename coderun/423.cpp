//
// Created by mason on 05.07.24.
//
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    for (int iter = 0; iter < k; iter++) {
        int x, l = 0, r = n - 1;
        cin >> x;

        if (a[l] >= x) {
            r = 0;
        } else if (a[r] < x) {
            r = n;
        } else {
            while (l < r - 1) {
                int m = (l + r) / 2;
                if (a[m] < x) l = m;
                else r = m;
            }
        }

        if (r == 0) {
            std::cout << r + 1 << '\n';
        } else if (r == n) {
            std::cout << r << '\n';
        } else if (x == a[r]) {
            std::cout << r + 1 << '\n';
        } else if (x - a[r - 1] == a[r] - x) {
            std::cout << r << '\n';
        } else {
            std::cout << (x - a[r - 1] < a[r] - x ? r : r + 1) << '\n';
        }
    }


    return 0;
}