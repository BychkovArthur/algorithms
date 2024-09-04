#include <bits/stdc++.h>

using namespace std;


int gcd(int a, int b) {
    if (b > a) swap(a, b);

    while (b) {
        int tmp = a;
        a = b;
        b = tmp % b;
    }
    return a;
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;

    for (;n;--n) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int a = abs(x1 - x2);
        int b = abs(y1 - y2);
        if (!a || !b) {
            cout << max(a, b) + 1 << '\n';
        } else {
            cout << gcd(a, b) + 1 << '\n';
        }
    }
}