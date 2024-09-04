#include <iostream>
#include <cstdint>

using namespace std;

using ll = uint64_t;


ll gcd(ll a, ll b) {
    if (b > a) {
        swap(a, b);
    }
    while(b) {
        ll tmp = a;
        a = b;
        b = tmp % b;
    }
    return a;
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}


int main() {
    ll n, ans;
    cin >> n >> ans;

    for (int i = 0; i < n - 1; ++i) {
        ll val;
        cin >> val;
        ans = lcm(ans, val);
    }
    cout << ans;
}