#include <bits/stdc++.h>

#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;


template <typename T>
struct SegmentTree
{
public:
    using size_type = std::size_t;

private:
    struct Node
    {
        Node* left;
        Node* right;
        T value;
        T delay;

        Node() = default;                                                   //  так писать вообще стоит delay(T()) ????
        Node(const T& value) : left(nullptr), right(nullptr), value(value), delay(T()) {}
    };

    size_type n;
    Node* root;

public:

    SegmentTree(const std::vector<T>& vct) : n(vct.size()), root(nullptr) {
        build(root, 0, n - 1, vct);
    }

    void build(
        Node*& node,
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

    void push(
        Node* node,
        size_type l,
        size_type r    
    )
    {

        if (l != r) {
            node->left->delay += node->delay;
            node->right->delay += node->delay;
        }
        node->value += node->delay;
        node->delay = T();          //    не кринж??

    }

    const T& get(
        size_type ql,
        size_type qr
    )
    {
        return get(root, ql, qr, 0, n - 1);
    }

    const T& get(
        Node* node,
        size_type ql,
        size_type qr,
        size_type l,
        size_type r
    )
    {
        push(node, l, r);
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
        size_type ql,
        size_type qr,
        const T& value
    )
    {
        set(root, ql, qr, 0, n - 1, value);
    }

    void set(
        Node* node,
        size_type ql,
        size_type qr,
        size_type l,
        size_type r,
        const T& value
    )
    {
        if (ql <= l && r <= qr) {
            node->delay += value;
            push(node, l, r);
            return;
        }

        push(node, l, r);

        size_type m = (l + r) / 2;

        if (qr <= m) {
            set(node->left, ql, qr, l, m, value);
            push(node->right, m + 1, r);
        } else if (ql > m) {
            set(node->right, ql, qr, m + 1, r, value);
            push(node->left, l, m);
        } else {
            set(node->left, ql, qr, l, m, value);
            set(node->right, ql, qr, m + 1, r, value);
        }

        node->value = std::max(node->left->value, node->right->value);
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