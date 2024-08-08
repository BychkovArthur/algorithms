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

        data[ind] = max(data[left], data[right]);
    }

    ll get(ll l, ll x) {
        return get(l, x, 0, n - 1, 0);
    }

    ll get(
        ll ql,
        ll x,
        ll l,
        ll r,
        ll ind
    )
    {
        if (r < ql || data[ind] < x) return -1;
        if (l == r) return l;


        ll m = (l + r) / 2;
        ll left = ind * 2 + 1;
        ll right = ind * 2 + 2;
        
        ll val = get(ql, x, l, m, left);
        return val != -1 ? val : get(ql, x, m + 1, r, right);    
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

        data[ind] = max(data[left], data[right]);
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
        int t;
        cin >> t;
        if (t == 1) {
            
            int i, v;
            cin >> i >> v;
            st.set(i, v);

        } else {
            int x;
            cin >> x;
            cout << st.get(0, x) << '\n';
        }
    }
}