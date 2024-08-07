#include <iostream>
#include <vector>
#include <cstdint>


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

    using ptr = Node*;
    using size_type = std::size_t;
    
    size_type n;
    ptr root;
public:

    SegmentTree(size_type n) : n(n), root(nullptr) {}

    T get(size_type ql, size_type qr) {
        return get(ql, qr, 0, n - 1, root);
    }

    T get(
        size_type ql,
        size_type qr, 
        size_type l,
        size_type r,
        ptr node
    )
    {
        if (!node) return 0;

        if (ql <= l && r <= qr) {
            return node->value;
        }

        size_type m = (l + r) / 2;

        if (qr <= m) {
            return get(ql, qr, l, m, node->left);
        } 
        if (ql > m) {
            return get(ql, qr, m + 1, r, node->right);
        }

        return  get(ql, qr, l, m, node->left) + get(ql, qr, m + 1, r, node->right);
    }

    void set(size_type pos, const T& val) {
        set(pos, 0, n - 1, val, root);
    }

    void set(
        size_type pos,
        size_type l,
        size_type r,
        const T& val,
        ptr& node
    )
    {
        if (!node) {
            node = new Node();
        }

        if (l == r) {
            node->value += val;
            return;
        }

        size_type m = (l + r) / 2;

        if (pos <= m) {
            set(pos, l, m, val, node->left);
        } else {
            set(pos, m + 1, r, val, node->right);
        }

        if (node->left && node->right) {
            node->value = node->left->value + node->right->value;
            return;
        }
        node->value = node->left ? node->left->value : node->right->value;
    }  
};


int main() {

    /*
    * Решение задачи https://mai2022.contest.codeforces.com/group/Ej1bTQMkro/contest/427394/problem/C
    *
    */

    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);


    int k;
    SegmentTree<int64_t> st(1e9);
    
    std::cin >> k;

    for (int i = 0; i < k; ++i) {
        int q, x, y;
        std::cin >> q >> x >> y;
        if (q) {
            --x;
            st.set(x, y);
        } else {
            --x;
            --y;
            std::cout << st.get(x, y) << '\n';
        }
    }
}
