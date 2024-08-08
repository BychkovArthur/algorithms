#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;

struct SegTree {
    ll n;
    vector<vector<ll>> data;

    SegTree(const vector<ll>& vct) : n(vct.size()), data(4 * n) {
        build(0, n - 1, 0, vct);
    }

    void merge(vector<ll>& dest, const vector<ll>& src1, const vector<ll>& src2) {

        size_t ptr1 = 0;
        size_t ptr2 = 0;

        while (ptr1 < src1.size() && ptr2 < src2.size()) {
            if (src1[ptr1] < src2[ptr2]) {
                dest.push_back(src1[ptr1++]);
            } else {
                dest.push_back(src2[ptr2++]);
            }
        }

        while (ptr1 < src1.size()) dest.push_back(src1[ptr1++]);
        while (ptr2 < src2.size()) dest.push_back(src2[ptr2++]);

    }

    void build(
        size_t l,
        size_t r,
        size_t ind,
        const vector<ll>& vct
    )
    {
        if (l == r) {
            data[ind].push_back(vct[l]);
            return;
        }

        auto m = (l + r) / 2;
        auto left_ind = ind * 2 + 1;
        auto right_ind = ind * 2 + 2;

        build(l, m, left_ind, vct);
        build(m + 1, r, right_ind, vct);

        merge(data[ind], data[left_ind], data[right_ind]);
    }

    ll get(
        size_t l,
        size_t r,
        ll x
    )
    {
        return get(l, r, 0, n - 1, 0, x);
    }

    ll get(
        size_t ql,
        size_t qr, 
        size_t l,
        size_t r,
        size_t ind,
        ll x
    )
    {
        if (ql <= l && r <= qr) {
            auto lb = lower_bound(data[ind].begin(), data[ind].end(), x);
            if (lb == data[ind].end()) return INT64_MAX;
            return *lb;
        }

        auto m = (l + r) / 2;
        auto left_ind = ind * 2 + 1;
        auto right_ind = ind * 2 + 2;

        if (qr <= m) {
            return get(ql, qr, l, m, left_ind, x);
        }
        if (ql > m) {
            return get(ql, qr, m + 1, r, right_ind, x);
        }

        return min(get(ql, qr, l, m, left_ind, x), get(ql, qr, m + 1, r, right_ind, x));
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
        ll res = st.get(l, r, x);
        if (res == INT64_MAX) {
            cout << "None" << '\n';
        } else {
            cout << res << '\n';
        }
    }

}