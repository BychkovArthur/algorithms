#include <bits/stdc++.h>

using namespace std;
using ll = long long int;


struct SegmentTree
{
    ll n;
    vector<ll> data;

    SegmentTree(const vector<ll>& vct) : n(vct.size()), data(4 * n) {
        build(0, n - 1, 0, vct);
    }


    void build(
        ll l,
        ll r,
        ll ind,
        const vector<ll>& vct
    )
    {
        if (l == r) {
            data[ind] = vct[l];
            return;
        }

        ll m = (l + r) / 2;
        ll left = ind * 2 + 1;
        ll right = ind * 2 + 2;

        build(l, m, left, vct);
        build(m + 1, r, right, vct);

        data[ind] = data[left] + data[right];
    }

    ll get(ll l, ll r) {
        return get(l, r, 0, n - 1, 0);
    }

    ll get(
        ll ql,
        ll qr,
        ll l,
        ll r,
        ll ind
    )
    {
        if (ql <= l && r <= qr) {
            return data[ind];
        }

        ll m = (l + r) / 2;
        ll left = ind * 2 + 1;
        ll right = ind * 2 + 2;

        if (qr <= m) {
            return get(ql, qr, l, m, left);
        } else if (ql > m) {
            return get(ql, qr, m + 1, r, right);
        }

        return get(ql, qr, l, m, left) + get(ql, qr, m + 1, r, right);
    }


    void set(ll pos, ll val) {
        set(pos, 0, n - 1, 0, val);
    }

    void set(
        ll pos,
        ll l,
        ll r, 
        ll ind,
        ll val
    )
    {
        if (l == r) {
            data[ind] = val;
            return;
        }

        ll m = (l + r) / 2;
        ll left = ind * 2 + 1;
        ll right = ind * 2 + 2;



        if (pos <= m) {
            set(pos, l, m, left, val);
        } else {
            set(pos, m + 1, r, right, val);
        }

        data[ind] = data[left] + data[right];
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    SegmentTree st(a);

    for (int i = 0; i < q; ++i) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 2) {
            --r;
            cout << st.get(l, r) << '\n';
        } else {
            st.set(l, r);
        }
    }
}