#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;
using ll = int64_t;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin >> n;
    vector<ll> vct(n);
    ll ans = 0;
    ll prev_dist = 0;

    for (ll i = 0; i < n; ++i) {
        cin >> vct[i];
    }
    sort(vct.begin(), vct.end());

    for (ll i = 1; i < n; ++i) {
        ll dist_to_left = vct[i] - vct[i - 1];
        ll curr_dist = dist_to_left * i + prev_dist;
        ans += curr_dist;
        prev_dist = curr_dist;
    }
    cout << ans;
}