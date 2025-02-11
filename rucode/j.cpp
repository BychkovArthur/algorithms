#include <bits/stdc++.h>
#include <cstdint>
#include <vector>

using namespace std;

using ll = uint64_t;

ll getk(ll num) {
    if (num == 0) return 0;
    ll power = 1;
    ll i = 0;

    while (power <= num) {
        power *= 2;
        ++i;
    }
    return i;
}

ll inverse(ll num, ll k) {

    // cout << "num = " << num << endl;

    ll left = (num >> k) << k;

    // cout << "left = " << left << endl;

    ll right = (num << (64 - k));

    // cout << "right = " << right << endl;

    right = UINT64_MAX ^ right;
    right >>= (64 - k);

    // cout << "righti = " << right << endl << endl << endl;

    return left + right;
}

int main() {

    // cout << getk(0) << endl;
    // cout << getk(1) << endl;
    // cout << getk(2) << endl;
    // cout << getk(3) << endl;
    // cout << getk(4) << endl;
    // cout << getk(5) << endl;
    // cout << getk(6) << endl;
    // cout << getk(7) << endl;
    // cout << getk(8) << endl;
    // cout << getk(9) << endl;

    ll n;
    cin >> n;
    vector<ll> a(n);

    bool zero = false;

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] == 0) {
            zero = true;
        }
    }

    if (zero) {
        cout << 0 << endl;
        return 0;
    }
    

    vector<ll> k(n);

    for (int i = 0; i < n; ++i) {
        k[i] = getk(a[i]);
        // cout << "k " << i << " = " << k[i] << endl;
    }

    // ll mink = *min(k.begin(), k.end());
    ll mink = k[0];
    for (int i = 1; i < n; ++i) {
        mink = min(mink, k[i]);
    }


    // cout << mink << endl;


    // cout << inverse(1, 1) << endl;
    // cout << inverse(2, 2) << endl;
    // cout << inverse(3, 2) << endl;
    // cout << inverse(4, 2) << endl;
    // cout << inverse(5, 2) << endl;
    // cout << inverse(6, 2) << endl;
    // cout << inverse(7, 2) << endl;

    for (int i = 0; i < n; ++i) {
        if (a[i] & (1 << (mink - 1))) {
            
        } else {
            a[i] = inverse(a[i], mink);
        }
    }

    ll res = a[0];

    for (int i = 1; i < n; ++i) {
        res &= a[i];
    }

    cout << res << endl;

}