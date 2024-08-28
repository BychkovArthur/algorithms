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


    void set(int pos) {
        set(pos, 0, n - 1, 0);
    }

    void set(int pos ,int l, int r, int i) {
        if (l == r) {
            data[i] = 1;
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
    SegTree st(2 * n);
    vector<int> arr(n + 1, -1);
    vector<int> ans(n + 1, 0);

    for (int i = 0; i < 2 * n; ++i) {
        int num;
        cin >> num;

        if (arr[num] == -1) arr[num] = i;
        else {
            ans[num] = st.get(arr[num], i);
            st.set(arr[num]);
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << ' ';
    }

}