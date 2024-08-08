#include <vector>
#include <iostream>

template <typename T>
struct SegmentTree
{
private:
    struct Node
    {
        Node* left;
        Node* right;
        T value;

        Node() : left(nullptr), right(nullptr), value(T()) {}
        Node(const T& value) : left(nullptr), right(nullptr), value(value) {}
    };

    using size_type = std::size_t;
    using ptr = Node*;

    size_type n;
    std::vector<ptr> roots;

public:

    

    SegmentTree(const std::vector<T>& vct) : n(vct.size()) {
        roots.push_back(nullptr);
        build(roots[0], 0, n - 1, vct);
    }

    void build(
        ptr& node,
        size_type l,
        size_type r,
        const std::vector<T>& vct
    )
    {
        if (l == r) {
            node = new Node(vct[l]);
            return;
        } else {
            node = new Node();
        }

        size_type m = (l + r) / 2;

        build(node->left, l, m, vct);
        build(node->right, m + 1, r, vct);

        node->value = std::max(node->left->value, node->right->value);
    }


    const T& get(
        size_type v, 
        size_type ql,
        size_type qr
    )
    {
        return get(roots[v], ql, qr, 0, n - 1);
    }

    const T& get(
        ptr node,
        size_type ql,
        size_type qr,
        size_type l,
        size_type r
    )
    {
        if (ql <= l && r <= qr) {
            return node->value;
        }

        size_type m = (l + r) / 2;

        if (qr <= m) {
            return get(node->left, ql, qr, l, m);
        } else if (ql > m) {
            return get(node->right, ql, qr, m + 1, r);
        }

        return std::max(get(node->left, ql, qr, l, m), get(node->right, ql, qr, m + 1, r));
    }


    void set(
        size_type v,
        size_type pos,
        const T& value
    )
    {
        roots.push_back(nullptr);
        set(roots[v], roots.back(), pos, 0, n - 1, value);
    }

    void set(
        ptr orig,
        ptr& copy,
        size_type pos,
        size_type l,
        size_type r,
        const T& value
    )
    {
        if (l == r) {
            copy = new Node(value);
            return;
        } else {
            copy = new Node();
            copy->left = orig->left;
            copy->right = orig->right;
        }

        size_type m = (l + r) / 2;
        if (pos <= m) {
            set(orig->left, copy->left, pos, l, m, value);
        } else {
            set(orig->right, copy->right, pos, m + 1, r, value);
        }

        copy->value = std::max(copy->left->value, copy->right->value);
    }
};


int main() {
    /*
    * Решение задачи https://mai2022.contest.codeforces.com/group/Ej1bTQMkro/contest/427394/problem/H
    *
    *
    */

    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    SegmentTree<int> st(a);

    for (int i = 0; i < q; ++i) {
        std::string type;
        std::cin >> type;
        if (type == "get") {
            int v, p;
            std::cin >> v >> p;

            --v;
            --p;

            std::cout << st.get(v, p, p) << '\n';
        } else {
            int v, p, x;
            std::cin >> v >> p >> x;
            --v;
            --p;
            st.set(v, p, x);
        }
    } 
}