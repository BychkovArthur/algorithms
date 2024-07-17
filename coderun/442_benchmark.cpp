#include <iostream>
#include <vector>

/*
 * Параметризовать класс функцией,
 * для которой строится ДО
 *
 *
 * TODO:
 * 1) Можно завести мапу, чтобы в ней пару
 * */


const long long mod = 1e9 + 7;

template <typename T>
struct SegmentTree {
    std::size_t n;
    std::vector<T> tree;

    SegmentTree(const std::vector<T>& vct) : n(vct.size()), tree(4 * n, T()) {
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
        tree[curr_tree_ind] = (tree[left_son_ind] * tree[right_son_ind]) % mod;
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
        return (get(ql, qr, l, m, left_son_ind) * get(ql, qr, m + 1, r, right_son_ind)) % mod;
    }

    void set(
            std::size_t ql,
            std::size_t qr
    )
    {
        set(ql, qr, 0, n - 1, 0);
    }

    void set(
            std::size_t ql,
            std::size_t qr,
            std::size_t l,
            std::size_t r,
            std::size_t curr_tree_ind
    )
    {
        if (l == r) {
            ++tree[curr_tree_ind];
            return;
        }

        auto m = (l + r) / 2;
        auto left_son_ind = 2 * curr_tree_ind + 1;
        auto right_son_ind = 2 * curr_tree_ind + 2;

        // Только налево
        if (qr <= m) {
            set(ql, qr, l, m, left_son_ind);
        } else if (ql > m) {
            set(ql, qr, m + 1, r, right_son_ind);
        } else {
            set(ql, qr, l, m, left_son_ind);
            set(ql, qr, m + 1, r, right_son_ind);
        }
        tree[curr_tree_ind] = (tree[left_son_ind] * tree[right_son_ind]) % mod;
    }
};

using namespace std;


int main() {

    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);
    std::srand(time(NULL));


    long long int n, k;
    std::cin >> n;
    std::vector<long long int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    std::cin >> k;


    SegmentTree<long long int> st(a);

    for (int i = 0; i < k; ++i) {
        long long int a, b, c;

        std::cin >> a >> b >> c;
        if (a == 0) {
            st.set(b, c);
        } else {
            std::cout << st.get(b, c) << '\n';
        }

    }

//    for (int ii = 0; ii < 1'000'000; ++ii) {
//        int n = 5;
//        int k = rand() % 20 + 5;
//        vector<long long int> a(n);
//
//        for (int i = 0; i < n; ++i) a[i] = rand() % 3 + 5;
//        vector<long long int> b(a);
//
//        SegmentTree<long long int> st(a);
//
//        cout << "Test " << ii << '\n' << endl;
//        cout << "ARR = " << endl;
//        for (int i = 0; i < n; ++i)
//            cout << a[i] << ' ';
//        cout << endl;
//
//        for (int i = 0; i < k; ++i) {
//            int q = rand() % 2;
//            int l = rand() % n, r = rand() % n;
//
//
//
//            while (l > r) {
//                l = rand() % n, r = rand() % n;
//            }
//
//            cout << "Q = " << q << " l = " << l << " r = " << r << endl;
//
//            if (q == 0) {
//                for (int i = l; i <= r; ++i) ++b[i];
//                st.set(l , r);
//            } else {
//                long long int res = 1;
//                for (int i = l; i <= r; ++i) {
//                    res *= b[i];
//                    res %= mod;
//                }
//                if (auto getres = st.get(l, r); res != getres) {
//                    cout << "ERROR" << endl;
//                    cout << "RES = " << res << " GET = " << getres << endl;
//                    return 1;
//                }
//            }
//        }
//    }

    // 7 6 6 7 5

}
