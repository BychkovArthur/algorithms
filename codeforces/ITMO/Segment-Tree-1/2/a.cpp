#include <bits/stdc++.h>

using namespace std;
using ll = long long int;


struct SegmentTree
{
    
    struct data_ {
        ll sum;
        ll pref;
        ll suf;
        ll seg;
    };
    
    ll n;
    vector<data_> data;
    


    SegmentTree(const vector<ll>& vct) : n(vct.size()), data(4 * n) {
        build(0, n - 1, 0, vct);
    }


    void update(
        ll ind,
        ll left,
        ll right
    )
    {
        data[ind].sum = data[left].sum + data[right].sum;
        data[ind].pref = max(data[left].pref, data[left].sum + data[right].pref);
        data[ind].suf = max(data[right].suf, data[right].sum + data[left].suf);
        data[ind].seg = max(max(data[left].seg, data[right].seg), data[left].suf + data[right].pref);
    }

    void build(
        ll l,
        ll r,
        ll ind,
        const vector<ll>& vct
    )
    {
        if (l == r) {
            data[ind].sum = vct[l];
            data[ind].pref = max(0ll, vct[l]);
            data[ind].suf = max(0ll, vct[l]);
            data[ind].seg = max(0ll, vct[l]);
            return;
        }

        ll m = (l + r) / 2;
        ll left = ind * 2 + 1;
        ll right = ind * 2 + 2;

        build(l, m, left, vct);
        build(m + 1, r, right, vct);

        update(ind, left, right);
    }

    ll get() {
        return data[0].seg;
    }

    // ll get(
    //     ll ql,
    //     ll qr,
    //     ll l,
    //     ll r,
    //     ll ind
    // )
    // {
    //     if (ql <= l && r <= qr) {
    //         return data[ind];
    //     }

    //     ll m = (l + r) / 2;
    //     ll left = ind * 2 + 1;
    //     ll right = ind * 2 + 2;

    //     if (qr <= m) {
    //         return get(ql, qr, l, m, left);
    //     } else if (ql > m) {
    //         return get(ql, qr, m + 1, r, right);
    //     }

    //     return get(ql, qr, l, m, left) + get(ql, qr, m + 1, r, right);
    // }


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
            data[ind].sum = val;
            data[ind].pref = max(0ll, val);
            data[ind].suf = max(0ll, val);
            data[ind].seg = max(0ll, val);
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

        update(ind, left, right);
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
    cout << st.get() << '\n';

    for (int i = 0; i < q; ++i) {
        int pos, v;
        cin >> pos >> v;

        st.set(pos, v);
        cout << st.get() << '\n';
    }
}