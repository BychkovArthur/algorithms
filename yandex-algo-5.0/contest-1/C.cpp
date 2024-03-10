#include <iostream>

using namespace std;


int main() {
    long long int n, res = 0, x;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        res += x / 4;
        if (x % 4) {
            res += (x % 4 == 1 ? 1 : 2);
        } 
    }
    cout << res << endl;
}