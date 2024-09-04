#include <iostream>

using namespace std;


int main() {
    long long int n;
    cin >> n;
    long long int res = 0;
    for (long long int i = 1; i * i <= n; ++i) {
        if (n % i == 0) res += 2;
        if (i * i == n) res -= 1;
    }
    cout << res;
}