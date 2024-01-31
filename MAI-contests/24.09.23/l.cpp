#include <bits/stdc++.h>

using namespace std;

int main() {
    int a, b, c, d;
    cin >> a >> b;
    cin >> c >> d;
    if (a + c > b + d) {
        cout << "A" << endl;
    } else if (a + c < b + d) {
        cout << "P" << endl;
    } else {
        cout << "D" << endl;
    }
}