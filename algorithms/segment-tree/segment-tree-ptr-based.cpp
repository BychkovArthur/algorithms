#include <vector>

/*
 *
 *
 *
 *
 * TODO:
 * 1) Параметризовать класс функцией, для которой строится ДО
 * 2) Если размер массива 0, то гг
 * 3) чекнуть комментарий в  Node()
 * 4) чекнуть комментарий в  push
 * */


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
        } else if (ql > m) {
            set(node->right, ql, qr, m + 1, r, value);
        } else {
            set(node->left, ql, qr, l, m, value);
            set(node->right, ql, qr, m + 1, r, value);
        }

        node->value = std::max(node->left->value, node->right->value);
    }


    
};




int main() {

}