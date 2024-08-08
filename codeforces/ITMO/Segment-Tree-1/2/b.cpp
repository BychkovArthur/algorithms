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

    ll get(ll k) {
        ++k;

        int i = 0;
        int l = 0, r = n - 1;

        while (l < r) {
            ll m = (l + r) / 2;
            ll left = i * 2 + 1;
            ll right = i * 2 + 2;

            if (data[left] >= k) {
                i = left;
                r = m;
            } else {
                k -= data[left];
                i = right;
                l = m + 1;
            }
        }
        return l;
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
            data[ind] = data[ind] ? 0 : 1;
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
        int t, v;
        cin >> t >> v;
        if (t == 1) {
            st.set(v, v);
        } else {
            cout << st.get(v) << '\n';
        }
    }
}