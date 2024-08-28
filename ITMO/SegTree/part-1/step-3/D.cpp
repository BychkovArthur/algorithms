#include <bits/stdc++.h>

using namespace std;



struct SegTree {
    int n;
    vector<int> data;


    SegTree(int n) : n(n), data(4 * n, 0) {}

    int get(int l, int r) {
        return get(l, r, 0, n - 1, 0);
    }

    int get(int ql, int qr, int l, int r, int i) {
        if (ql > qr) return 0;

        if (ql <= l && r <= qr) return data[i];


        int m = (l + r) / 2;
        int li = i * 2 + 1;
        int ri = i * 2 + 2;

        if (qr <= m) {
            return get(ql, qr, l, m, li);
        } else if (ql > m) {
            return get(ql, qr, m + 1, r, ri);
        }

        return get(ql, qr, l, m, li) + get(ql, qr, m + 1, r, ri);
    }


    void set(int pos, int val) {
        set(pos, 0, n - 1, 0, val);
    }

    void set(int pos ,int l, int r, int i, int val) {
        if (l == r) {
            data[i] = val;
            return;
        } 

        int m = (l + r) /2 ;
        int li = i * 2 + 1;
        int ri = i * 2 + 2;

        if (pos <= m) {
            set(pos, l, m, li, val);
        } else {
            set(pos, m + 1, r, ri, val);
        }

        data[i] = data[li] + data[ri];
    }
};


int main() {
    int n;
    cin >> n;
    vector<int> a(2 * n);
    vector<int> ans(n + 1, 0);
    for (int i = 0; i < 2 * n; ++i) cin >> a[i];

    for (int t = 0; t < 2; ++t) {
        SegTree st(2 * n);
        vector<int> inds(n + 1, -1);

        for (int i = 0; i < 2 * n; ++i) {

            if (inds[a[i]] == -1) {
                inds[a[i]] = i;
                st.set(i, 1);
            } else {
                // cout << "HERE" << " i = " << i << endl;
                // cout << "ADDING " << st.get(inds[a[i]] + 1, i) << endl;

                // cout << "BORDERS = " << inds[a[i]] + 1 << ' ' << i << endl;; 
                ans[a[i]] += st.get(inds[a[i]] + 1, i);

                // cout << "ans[" << a[i] << "] = " << ans[a[i]] << endl << endl;

                st.set(inds[a[i]], 0);
            }
        }

        // cout << "REVERSE" << endl;
        reverse(a.begin(), a.end());
    }

    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << ' ';
    }
}