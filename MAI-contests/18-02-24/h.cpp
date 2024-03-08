#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()

using namespace std;

using ll = int64_t;
using ull = uint64_t;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

template <typename _Key, typename _Tp>
using umap = unordered_map<_Key, _Tp>;
template <typename _Value>
using uset = unordered_set<_Value>;

static const ll mod1 = 1'000'000'007;
static const ll mod2 = 2'147'483'647;

ll min3(ll a, ll b, ll c) {
    if (a <= b && a <= c) return a;
    if (b <= a && b <= c) return b;
    return c;
}

ll max3(ll a, ll b, ll c) {
    if (a >= b && a >= c) return a;
    if (b >= a && b >= c) return b;
    return c;
}

ll max(const vll& vct) {
    return max3(vct[0], vct[1], vct[2]);
}

ll min(const vll& vct) {
    return min3(vct[0], vct[1], vct[2]);
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    cin >> n;

    vector<vll> players(n, vll(4));
    vll answers(n);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            cin >> players[i][j];
        }
    }

    // for (size_t i = 0; i < n; ++i) {
    //     for (size_t j = 0; j < 4; ++j) {
    //         cout << players[i][j] << " ";
    //     }
    //     cout << endl;
    // }


    for (size_t i = 0; i < n; ++i) {

        ll mx = max(players[i]);
        ll mn = min(players[i]);

        while (!((2 * mx - 2 * mn) >= 7) && players[i][3]) {
            --players[i][3];

            if (players[i][0] == mn) {
                ++players[i][0];
            } else if (players[i][1] == mn) {
                ++players[i][1];
            } else if (players[i][2] == mn) {
                ++players[i][2];
            }

            mx = max(players[i]);
            mn = min(players[i]);

            cout << "MX: " << mx << endl;
            cout << "MN: " << mn << endl;

            for (ll k : players[i]) {
                cout << k << " ";
            }
            cout << "\n\n" << endl;
        }
        
        if (players[i][0] == mx) {
            players[i][0] += players[i][3];

        } else if (players[i][1] == mx) {
            players[i][1] += players[i][3];

        } else if (players[i][2] == mx) {
            players[i][2] += players[i][3];

        }

    }

    for (size_t i = 0; i < n; ++i) {
        ll res = 0;

        res += players[i][0] * players[i][0];
        res += players[i][1] * players[i][1];
        res += players[i][2] * players[i][2];

        res += min3(players[i][0], players[i][1], players[i][2]) * 7;

        cout << res << endl;
        
    }

    
    return 0;
}