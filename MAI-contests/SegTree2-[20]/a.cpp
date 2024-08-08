#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;

struct SegTree {
    ll n;
    vector<ll> data;
    vector<ll> delay;

    SegTree(const vector<ll>& vct) : n(vct.size()), data(4 * n, 0), delay(4 * n, 0) {
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
        data[ind] = max(data[left_ind], data[right_ind]);
    }

    void push(
        size_t l,
        size_t r,
        size_t ind
    )
    {
        if (l != r) {
            delay[ind * 2 + 1] += delay[ind];
            delay[ind * 2 + 2] += delay[ind];
        }
        data[ind] += delay[ind];
        delay[ind] = 0;
    }

    ll get(
        size_t l,
        size_t r
    )
    {
        return get(l, r, 0, n - 1, 0);
    }

    ll get(
        size_t ql,
        size_t qr, 
        size_t l,
        size_t r,
        size_t ind
    )
    {
        push(l, r, ind);
        if (ql <= l && r <= qr) {
            return data[ind];
        }

        auto m = (l + r) / 2;
        auto left_ind = ind * 2 + 1;
        auto right_ind = ind * 2 + 2;

        if (qr <= m) {
            return get(ql, qr, l, m, left_ind);
        }
        if (ql > m) {
            return get(ql, qr, m + 1, r, right_ind);
        }

        return max(get(ql, qr, l, m, left_ind), get(ql, qr, m + 1, r, right_ind));
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
        push(l, r, ind);
        if (ql <= l && r <= qr) {
            delay[ind] += val;
            push(l, r, ind);
            return;
        }

        

        auto m = (l + r) / 2;
        auto left_ind = ind * 2 + 1;
        auto right_ind = ind * 2 + 2;

        if (qr <= m) {
            set(ql, qr, l, m, left_ind, val);
            push(m + 1, r, right_ind);
        } else if (ql > m) {
            set(ql, qr, m + 1, r, right_ind, val);
            push(l, m, left_ind);
        } else {
            set(ql, qr, l, m, left_ind, val);
            set(ql, qr, m + 1, r, right_ind, val);
        }

        data[ind] = max(data[left_ind], data[right_ind]);
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
        int l, r, x;
        cin >> l >> r >> x;
        --l;
        --r;
        st.set(l, r, x);
        cout << st.get(l, r) << '\n';
    }

}