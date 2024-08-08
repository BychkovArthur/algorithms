#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;

struct SegTree {
    ll n;
    vector<ll> data;

    SegTree(const vector<ll>& vct) : n(vct.size()), data(4 * n, -1) {
        build(0, n - 1, 0, vct);
    }

    void build(
        size_t l,
        size_t r,
        size_t ind,
        const vector<ll>& vct
    )
    {
        if (l == r) {
            data[ind] = vct[l];
            return;
        }

        auto m = (l + r) / 2;
        auto left_ind = ind * 2 + 1;
        auto right_ind = ind * 2 + 2;

        build(l, m, left_ind, vct);
        build(m + 1, r, right_ind, vct);        
    }

    void push(
        size_t l,
        size_t r,
        size_t ind
    )
    {
        if (data[ind] == -1 || l == r) return;

        data[ind * 2 + 1] = data[ind];
        data[ind * 2 + 2] = data[ind];
        data[ind] = -1;
    }

    ll get(
        size_t pos
    )
    {
        return get(pos, 0, n - 1, 0);
    }

    ll get(
        size_t pos,
        size_t l,
        size_t r,
        size_t ind
    )
    {
        if (data[ind] != -1) {
            return data[ind];
        }

        auto m = (l + r) / 2;
        auto left_ind = ind * 2 + 1;
        auto right_ind = ind * 2 + 2;

        if (pos <= m) {
            return get(pos, l, m, left_ind);
        } else {
            return get(pos, m + 1, r, right_ind);
        }
    }

    void set(
        size_t l,
        size_t r,
        ll val
    )
    {
        set(l, r, 0, n - 1, 0, val);
    }

    void set(
        size_t ql,
        size_t qr,
        size_t l,
        size_t r,
        size_t ind,
        ll val
    )
    {
        if (ql <= l && r <= qr) {
            data[ind] = val;
            return;
        }

        push(l, r, ind);
        
        auto m = (l + r) / 2;
        auto left_ind = ind * 2 + 1;
        auto right_ind = ind * 2 + 2;

        if (qr <= m) {
            set(ql, qr, l, m, left_ind, val);
        } else if (ql > m) {
            set(ql, qr, m + 1, r, right_ind, val);
        } else {
            set(ql, qr, l, m, left_ind, val);
            set(ql, qr, m + 1, r, right_ind, val);
        }
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    cin >> k;

    SegTree st(a);
    
    for (int i = 0; i < k; ++i) {
        int q;
        cin >> q;
        if (q) {
            int pos;
            cin >> pos;
            --pos;
            cout << st.get(pos) << '\n';
        } else {
            int l, r, c;
            cin >> l >> r >> c;
            --l;
            --r;
            st.set(l, r, c);
            
        }
        
    }

}