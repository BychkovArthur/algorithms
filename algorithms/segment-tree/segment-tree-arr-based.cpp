#include <iostream>
#include <vector>
#include <cstdint>

/*
 *
 *
 *
 *
 * TODO:
 * 1) Параметризовать класс функцией, для которой строится ДО
 * 2) Если размер массива 0, то гг
 *
 * */

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
        if (ql <= l &&  r <= qr) {
            delay[curr_tree_ind] += value;
            push(l, r, curr_tree_ind);
            return;
        }

        push(l, r, curr_tree_ind);

        auto m = (l + r) / 2;
        auto left_son_ind = 2 * curr_tree_ind + 1;
        auto right_son_ind = 2 * curr_tree_ind + 2;

        if (qr <= m) {
            set(ql, qr, l, m, left_son_ind, value);
        } else if (ql > m) {
            set(ql, qr, m + 1, r, right_son_ind, value);
        } else {
            set(ql, qr, l, m, left_son_ind, value);
            set(ql, qr, m + 1, r, right_son_ind, value);
        }

        tree[curr_tree_ind] = std::max(tree[left_son_ind], tree[right_son_ind]);
    }


};


int main() {
    /*
     *
     * Решение задачи
     * https://mai2022.contest.codeforces.com/group/Ej1bTQMkro/contest/427393/problem/A
     */
//    std::cin.tie(NULL);
//    std::ios::sync_with_stdio(false);
//    long long int n, k;
//    std::cin >> n;
//    std::vector<long long int> a(n);
//    for (int i = 0; i < n; ++i) std::cin >> a[i];
//    std::cin >> k;
//
//    SegmentTree<long long int> st(a);
//    for (int i = 0; i < k; ++i) {
//        long long int a, b, c;
//
//        std::cin >> a >> b >> c;
//        if (a) {
//            st.set(b - 1, c);
//        } else {
//            std::cout << st.get(b - 1, c - 1) << '\n';
//        }
//    }

    /*
     *
     * Решение задачи
     * https://mai2022.contest.codeforces.com/group/Ej1bTQMkro/contest/427394/problem/A
     *
     */

    int n, k;
    std::cin >> n;
    std::vector<int64_t> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    std::cin >> k;

    SegmentTree<int64_t> st(a);

    for (int i = 0; i < k; ++i) {
        int64_t l, r, x;
        std::cin >> l >> r >> x;
        --l;
        --r;
        st.set(l, r, x);
        std::cout << st.get(l, r) << '\n';
    }
}
