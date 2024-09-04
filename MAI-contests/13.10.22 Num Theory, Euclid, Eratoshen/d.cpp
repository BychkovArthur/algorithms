#include <iostream>
#include <cstdint>
#include <tuple>

using namespace std;

using ll = int64_t;

struct ExtendedEuclid {
    ll x;
    ll y;
    ll gcd;
};


ExtendedEuclid extended_euclid(ll a, ll b) {
    bool swapped = false;
    if (b > a) swap(a, b), swapped = true;

    // r0 = a, r1 = b
    ll x, xp, xpp, y, yp, ypp, r, rp, rpp;
    xpp = 1, xp = 0;
    ypp = 0, yp = 1;
    rpp = a, rp = b;

    while(true) {
        ll q = rpp / rp;
        x = xpp - q * xp;
        y = ypp - q * yp;
        r = x * a + y * b;
        
        if (!r) {
            return swapped ? ExtendedEuclid{yp, xp, rp} : ExtendedEuclid{xp, yp, rp};
        }
        xpp = xp;
        xp = x;
        ypp = yp;
        yp = y;
        rpp = rp;
        rp = r;
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    for (;t;--t) {
        ll a, b, c;
        cin >> a >> b >> c;
        auto res = extended_euclid(a, b);
        if (c % res.gcd == 0) {
            cout << res.gcd << ' ' << res.x * c / res.gcd << ' ' << res.y * c / res.gcd << '\n';
        } else {
            cout << -1 << '\n';
        }
    }
}