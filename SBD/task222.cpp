#include <bits/stdc++.h>
 
using namespace std;
using ll = long long int;
const ll INF = 1e18;

struct segtree {
    ll n;
    vector<pair<ll, ll>> data;
    segtree(ll _n) : n(_n), data(4 * _n) {}

    segtree(const vector<ll> &a) : segtree(a.size()) {build(1, 1, n, a);}

    void build(ll id, ll l, ll r, const vector<ll> & a) {
        if (l == r) {
            data[id].first = a[l - 1];
            data[id].second = l - 1;
            return;
        }
        ll m = (l + r) / 2;
        build(id * 2, l, m, a);
        build(id * 2 + 1, m + 1, r, a);
        data[id].first = min(data[id * 2].first, data[id * 2 + 1].first);
        data[id].second = (data[id * 2].first <= data[id * 2 + 1].first ? data[id * 2].second : data[id * 2 + 1].second);
    }
    ll get(ll ql, ll qr) {
        return get(1, 1, n, ql, qr).second;
    }
    pair<ll, ll> get(ll id, ll l, ll r, ll ql, ll qr) {
        if (ql <= l and r <= qr) {
            return data[id];
        }
        ll m = (l + r) / 2;
        if (qr <= m) {
            return get(id * 2, l, m, ql, qr);
        }
        if (ql >= m + 1) {
            return get(id * 2 + 1, m + 1, r, ql, qr);
        }
        pair<ll, ll> pr1 = get(id * 2, l, m, ql, qr);
        pair<ll, ll> pr2 = get(id * 2 + 1, m + 1, r, ql, qr);
        if (pr1.first <= pr2.first) {
            return pr1;
        }
        return pr2;
    }
};

int main() {
	ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, k;
    cin >> n >> k;
    vector<ll> prices(n);
    vector<ll> answer(n, 0);

    for (int i = 0; i < n; ++i) {
        cin >> prices[i];
    }
    segtree st(prices);

    for (int i = 0; i < n; ++i) {
        ll ql = (i - k + 1 > 0 ? i - k + 1 : 0) + 1;
        ll qr = i + 1;
        ++answer[st.get(ql, qr)];
    }

	ll sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += prices[i] * answer[i];
    }

    cout << sum << endl;
    for (int i = 0; i < n; ++i) {
        cout << answer[i] << ' ';
    }
}
