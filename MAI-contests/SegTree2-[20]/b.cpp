#include <bits/stdc++.h>

using namespace std;
using ll = int64_t;
using ull = size_t;



struct SegTree {
    ull n;
    vector<ll> data;
    vector<ll> delay;

    SegTree(const vector<ll>& other) : n(other.size()), data(4 * n, 0), delay(4 * n, 0) {
        build(0, n - 1, 0, other);
    }

    void build(
        ull l,
        ull r, 
        ull ind,
        const vector<ll>& other
    )
    {
        if (l == r) {
            data[ind] = other[l];
            return;
        }

        ull m = (l + r) / 2;
        ull left = ind * 2 + 1;
        ull right = ind * 2 + 2;


        build(l, m, left, other);
        build(m + 1, r, right, other);

        data[ind] = data[left] + data[right];
    }

    void push(
        ull l,
        ull r,
        ull ind
    )
    {
        if (l != r) {
            delay[ind * 2 + 1] += delay[ind];
            delay[ind * 2 + 2] += delay[ind];
        }
        data[ind] += delay[ind] * (r - l + 1);
        delay[ind] = 0;
    }

    ll get(
        ull l,
        ull r
    )
    {
        return get(l, r, 0, n - 1, 0);
    }

    ll get(
        ull ql,
        ull qr,
        ull l,
        ull r,
        ull ind
    )
    {
        push(l, r, ind);
        if (ql <= l && r <= qr) return data[ind];


        ull m = (l + r) / 2;
        ull left = ind * 2 + 1;
        ull right = ind * 2 + 2;

        if (qr <= m) return get(ql, qr, l, m, left);
        if (ql > m) return get(ql, qr, m + 1, r, right);

        return get(ql, qr, l, m, left) + get(ql, qr, m + 1, r, right);
    }

    void set(ull l, ull r, ll x) {
        set(l, r, 0, n - 1, 0, x);
    }

    void set(
        ull ql,
        ull qr,
        ull l,
        ull r,
        ull ind,
        ll x
    )
    {
        if (ql <= l && r <= qr) {
            delay[ind] += x;
            push(l, r, ind);
            return;
        }

        push(l, r, ind);

        ull m = (l + r) / 2;
        ull left = ind * 2 + 1;
        ull right = ind * 2 + 2;


        if (qr <= m) {
            set(ql, qr, l, m, left, x);
            push(m + 1, r, right);
        } else if (ql > m) {
            set(ql, qr, m + 1, r, right, x);
            push(l, m, left);
        } else {
            set(ql, qr, l, m, left, x);
            set(ql, qr, m + 1, r, right, x);
        }

        data[ind] = data[left] + data[right];
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