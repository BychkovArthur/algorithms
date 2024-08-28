#include <bits/stdc++.h>

using namespace std;



struct SegTree {
    long long int n;
    vector<long long int> data;


    SegTree(long long int n) : n(n), data(4 * n, 0) {}

    long long int get(long long int pos) {
        return get(pos, 0, n - 1, 0, 0);
    }

    long long int get(long long int pos, long long int l, long long int r, long long int i, long long int buffer) {
        if (l == r) return buffer + data[i];

        long long int m = (l + r) / 2;
        long long int li = i * 2 + 1;
        long long int ri = i * 2 + 2;

        if (pos <= m) {
            return get(pos, l, m, li, buffer + data[i]);
        } 
        return get(pos, m + 1, r, ri, buffer + data[i]);
    }


    void set(long long int ql, long long int qr, long long int val) {
        set(ql, qr, 0, n - 1, 0, val);
    }

    void set(long long int ql, long long int qr ,long long int l, long long int r, long long int i, long long int val) {
        if (ql <= l && r <= qr) {
            data[i] += val;
            return;
        }

        long long int m = (l + r) / 2;
        long long int li = i * 2 + 1;
        long long int ri = i * 2 + 2;

        if (qr <= m) {
            set(ql, qr, l, m, li, val);
            return;
        } else if (ql > m) {
            set(ql, qr, m + 1, r, ri, val);
            return;
        }

        set(ql, qr, l, m, li, val);
        set(ql, qr, m + 1, r, ri, val);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    long long int n, q;
    cin >> n >> q;
    vector<long long int> a(n, 0);

    SegTree st(n);


    for (long long int i = 0; i < q; ++i) {
        long long int t;
        cin >> t;
        if (t == 1) {
            long long int l, r, v;
            cin >> l >> r >> v;
            --r;
            st.set(l, r, v);
        } else {
            long long int pos;
            cin >> pos;
            cout << st.get(pos) << '\n';
        }
    }
}