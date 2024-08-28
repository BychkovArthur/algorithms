#include <bits/stdc++.h>

using namespace std;



struct SegTree {
    int n;
    vector<int> data;


    SegTree(int n) : n(n), data(4 * n, 0) {
        build(0, n - 1, 0);
    }

    void build(int l, int r, int i) {
        // cout << l << ' ' << r << endl;
        if (l == r) {
            data[i] = 1;
            return;
        }

        int m = (l + r) / 2;
        int li = i * 2 + 1;
        int ri = i * 2 + 2;

        build(l, m, li);
        build(m + 1, r, ri);

        data[i] = data[li] + data[ri];
    }

    int get(int number) {
        int l = 0, r = n - 1, i = 0;

        while (l != r) {
            int m = (l + r) / 2;
            int li = i * 2 + 1;
            int ri = i * 2 + 2;

            if (data[ri] >= number) {
                l = m + 1;
                i = ri;
            } else {
                r = m;
                i = li;
                number -= data[ri];
            }
        }
        return l;
    }


    void set(int pos) {
        set(pos, 0, n - 1, 0);
    }

    void set(int pos ,int l, int r, int i) {
        if (l == r) {
            data[i] = 0;
            return;
        } 

        int m = (l + r) /2 ;
        int li = i * 2 + 1;
        int ri = i * 2 + 2;

        if (pos <= m) {
            set(pos, l, m, li);
        } else {
            set(pos, m + 1, r, ri);
        }

        data[i] = data[li] + data[ri];
    }
};


int main() {
    int n;
    cin >> n;
    SegTree st(n);
    vector<int> a(n);
    vector<int> ans(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    

    for (int i = n - 1; i >= 0; --i) {
        ans[n - 1 - i] = st.get(a[i] + 1) + 1;
        st.set(ans[n - 1 - i] - 1);
    }

    reverse(ans.begin(), ans.end());
    for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
    
}