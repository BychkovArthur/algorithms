#include <bits/stdc++.h>


#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;


template <typename T>
struct SegmentTree {
    std::size_t n;
    std::vector<T> tree;
    std::vector<T> delay;

    SegmentTree(const std::vector<T>& vct) : n(vct.size()), tree(4 * n, T()), delay(4 * n, T()) {
        buildTree(0, n - 1, 0, vct);
    }

    void buildTree(
        std::size_t l,
        std::size_t r,
        std::size_t curr_tree_ind,
        const std::vector<T>& vct
    )
    {
        // Лист
        if (l == r) {
            tree[curr_tree_ind] = vct[l];
            return;
        }

        // Рекурсивный запуск
        auto m = (l + r) / 2;
        auto left_son_ind = 2 * curr_tree_ind + 1;
        auto right_son_ind = 2 * curr_tree_ind + 2;

        buildTree(l, m, left_son_ind, vct);
        buildTree(m + 1, r, right_son_ind, vct);

        // Получение значения во внутренней вершине
        tree[curr_tree_ind] = std::max(tree[left_son_ind], tree[right_son_ind]);
    }

    void push(
            std::size_t l,
            std::size_t r,
            std::size_t curr_tree_ind
    )
    {
        if (l != r) {
            delay[curr_tree_ind * 2 + 1] += delay[curr_tree_ind];
            delay[curr_tree_ind * 2 + 2] += delay[curr_tree_ind];
        }
        tree[curr_tree_ind] += delay[curr_tree_ind];
        delay[curr_tree_ind] = T();
    }


    T get(
        std::size_t ql,
        std::size_t qr
    )
    {
        return get(ql, qr, 0, n - 1, 0);
    }

    T get(
        std::size_t ql,
        std::size_t qr,
        std::size_t l,
        std::size_t r,
        std::size_t curr_tree_ind
    )
    {
        push(l, r, curr_tree_ind);
        if (ql <= l && r <= qr) return tree[curr_tree_ind];

        auto m = (l + r) / 2;
        auto left_son_ind = 2 * curr_tree_ind + 1;
        auto right_son_ind = 2 * curr_tree_ind + 2;

        // Только налево
        if (qr <= m) {
            return get(ql, qr, l, m, left_son_ind);
        }

        // Только направо
        if (ql > m) {
            return get(ql, qr, m + 1, r, right_son_ind);
        }

        // В обе стороны
        return std::max(get(ql, qr, l, m, left_son_ind), get(ql, qr, m + 1, r, right_son_ind));
    }

    void set(std::size_t pos, const T& value) {
        set(pos, value, 0, n - 1, 0);
    }

    void set(
        std::size_t pos,
        const T& value,
        std::size_t l,
        std::size_t r,
        std::size_t curr_tree_ind
    )
    {
        push(l, r, curr_tree_ind);
        if (l == r) {
            tree[curr_tree_ind] += value;
            return;
        }

        auto m = (l + r) / 2;
        auto left_son_ind = 2 * curr_tree_ind + 1;
        auto right_son_ind = 2 * curr_tree_ind + 2;

        if (pos <= m) {
            set(pos, value, l, m, left_son_ind);
        } else {
            set(pos, value, m + 1, r, right_son_ind);
        }

        tree[curr_tree_ind] = std::max(tree[left_son_ind], tree[right_son_ind]);
    }

    void set(
        std::size_t ql,
        std::size_t qr,
        const T& value
    )
    {
        set(ql, qr, 0, n - 1, 0, value);
    }

    void set(
        std::size_t ql,
        std::size_t qr,
        std::size_t l,
        std::size_t r,
        std::size_t curr_tree_ind,
        const T& value
    )
    {
        // if (qr == 5) cout << "ql = " << ql << " qr = " << qr << " l = " << l << " r = " << r << endl;    

        if (ql <= l &&  r <= qr) {
            // if (qr == 5) cout << "here1" << endl;
            delay[curr_tree_ind] += value;
            push(l, r, curr_tree_ind);
            return;
        }

        push(l, r, curr_tree_ind);

        auto m = (l + r) / 2;
        auto left_son_ind = 2 * curr_tree_ind + 1;
        auto right_son_ind = 2 * curr_tree_ind + 2;

        if (qr <= m) {
            // if (qr == 5) cout << "here2" << endl;
            set(ql, qr, l, m, left_son_ind, value);
        } else if (ql > m) {
            // if (qr == 5)cout << "here3" << endl;
            set(ql, qr, m + 1, r, right_son_ind, value);
        } else {
            // if (qr == 5)cout << "here4" << endl;
            set(ql, qr, l, m, left_son_ind, value);
            set(ql, qr, m + 1, r, right_son_ind, value);
        }
        tree[curr_tree_ind] = std::max(tree[left_son_ind], tree[right_son_ind]);
    }
};


struct Naive {

    size_t n;
    vector<int> vct;
    
    Naive(const vector<int>& vct) : n(vct.size()), vct(vct) {}


    void set(int l, int r, int value) {
        for (int i = l; i <= r; ++i) {
            vct[i] += value;
        }
    }

    int get(int l, int r) {
        int mx = INT32_MIN;
        for (int i = l; i <= r; ++i) {
            mx = max(mx, vct[i]);
        }
        return mx;
    }
    
};








int main() {
    // int n = 7;
    // vector<int> a = {1, 4, 2, 5, 1, 3, 3};
    // SegmentTree<int> st(a);
    // Naive nv(a);

    // st.set(0, 2, 1);
    // nv.set(0, 2, 1);
    // st.set(0, 4, 2);
    // nv.set(0, 4, 2);

    // // 4 7 5 7 3 3 3

    // st.set(0, 5, 2);
    // nv.set(0, 5, 2);

    // // 6 9 7 9 5 5 3 - должно быт


    // for (int i = 0; i < n; ++i) {
    //     for (int j = i + 1; j < n; ++j) {
    //         int val1 = st.get(i, j);
    //         int val2 = nv.get(i, j);

    //         if (val1 != val2) {
    //             cout << "error on  l = " << i << " r = " << j << endl;
    //             cout << "val1 = " << val1 << " val2 = " << val2 << endl;
    //             return 0;
    //         }
    //     }
    // }

    // st.set(3, 4, 2);

    // cout << st.get(3, 5) << endl;

    int n = 1000;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) a[i] = rand() % n;

    SegmentTree<int> st(a);
    Naive nv(a);

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {

            if (rand() % 2) {
                int val = rand() % n / 3;
                // cout << "called set l = " << i << " r " << j << " val = " << val << endl;
                nv.set(i, j, val);
                st.set(i, j, val);
            } else {
                // cout << "called get l = " << i << " r " << j << endl;

                int val1 = st.get(i, j);
                int val2 = nv.get(i, j);

                if (val1 != val2) {

                    cout << "Input arr = ";
                    for (int i = 0; i < n; ++i) cout << a[i] << ' ';
                    cout << endl;

                    cout << "correct arr = ";
                    for (int i = 0; i < n; ++i) cout << nv.vct[i] << ' ';
                    cout << endl;

                    cout << "ERROR ON i = " << i << " j = " << j << endl;
                    cout << "val1 = " << val1 << '\n' << "val2 = " << val2 << endl; 
                    return 0;
                }

            }
        }
    }
}


/*
    1 4 2 5 1 3 3
    set     0 2 1
    
    2 5 3 5 1 3 3
    set 0 4 2
    4 7 5 7 3 3 3
    set 0 5 2
    6 9 7 9 5 5 3
    set 3 5 1
    6 9 7 10 6 6 3

*/ 

