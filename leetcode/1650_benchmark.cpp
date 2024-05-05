#include <bits/stdc++.h>

using namespace std;

struct Node {
    int val;

    Node* left;
    Node* right;
    Node* parent;

    Node(int val) : val(val), left(nullptr), right(nullptr), parent(nullptr) {}
    Node(int val, Node* parent) : val(val), left(nullptr), right(nullptr), parent(parent) {}
};

Node* LCA_my_solution1(Node* p, Node* q) {
    /*
        TIME: O(H)
        SPACE: O(H)
    */
    unordered_set<Node*> st;

    while (p) {
        st.insert(p);
        p = p->parent;
    }

    while (!st.contains(q)) { q = q->parent; }
    return q;
}

int depth(Node* node, Node* target) {
    if (!node) {
        return -1;
    }

    if (node == target) {
        return 1;
    }

    int left = depth(node->left, target);
    int right = depth(node->right, target);

    if (left == -1 && right == -1) {
        return -1;
    }
    return max(left, right) + 1;
}

Node* LCA_my_solution2(Node* p, Node* q) {
    /*
        TIME: O(N) из-за depth, он в худшем случае пройдёт все вершины
        SPACE: O(H), если считать рекурсия за память. Иначе - O(1).
    */

    Node* root = q;

    while (root->parent) { root = root->parent; }

    int p_depth = depth(root, p);
    int q_depth = depth(root, q);

    while (p != q)
    {
        if (q_depth > p_depth) {
            --q_depth;
            q = q->parent;
        } else if (p_depth > q_depth) {
            --p_depth;
            p = p->parent;
        } else {
            --q_depth;
            --p_depth;
            q = q->parent;
            p = p->parent;
        }
    }
    return p;
}


Node* LCA_my_solution3(Node* p, Node* q) {
    /*
        TIME: O(H)
        SPACE: O(1)
    */

    int p_depth = 1;
    int q_depth = 1;
    Node* p_copy = p;
    Node* q_copy = q;

    while (p_copy->parent) {
        p_copy = p_copy->parent;
        ++p_depth;
    }

    while (q_copy->parent) {
        q_copy = q_copy->parent;
        ++q_depth;
    }

    while (p != q)
    {
        if (q_depth > p_depth) {
            --q_depth;
            q = q->parent;
        } else if (p_depth > q_depth) {
            --p_depth;
            p = p->parent;
        } else {
            --q_depth;
            --p_depth;
            q = q->parent;
            p = p->parent;
        }
    }
    return p;
}

int CORRECT_getLength(Node *p) {
    int ans = 0;
    for (; p->parent; p = p->parent, ++ans);
    return ans;
}
Node* CORRECT_lowestCommonAncestor(Node* p, Node * q) {
    int a = CORRECT_getLength(p), b = CORRECT_getLength(q);
    if (a < b) swap(a, b), swap(p, q);
    a -= b;
    while (a-- > 0) p = p->parent;
    while (p != q) p = p->parent, q = q->parent;
    return p;
}

Node* add_node(Node* root, int val) {
    Node* node = root;
    while (true) {
        if (int r = rand() % 2; r) {
            if (node->left) {
                node = node->left;
            } else {
                node->left = new Node(val, node);
                return node->left;
            }
        } else {
            if (node->right) {
                node = node->right;
            } else {
                node->right = new Node(val, node);
                return node->right;
            }
        }
    }

}

void print(Node* node, int tabs) {
    if (node->right) {
        print(node->right, tabs + 1);
    }
    for (int i = 0; i < tabs; ++i) {
        cout << '\t';
    }
    cout << node->val << '\n';
    if (node->left) {
        print(node->left, tabs + 1);
    }
}


int main() {

    /*
        Референс верного решения взят отсюда
        https://leetcode.ca/2020-06-06-1650-Lowest-Common-Ancestor-of-a-Binary-Tree-III/
    */

    std::srand(time(NULL));

    for (int i = 0; i < 1'000'000; ++i) {
        
        Node* root = new Node(rand() % 500);
        
        int n = rand() % 100;
        vector<Node*> nodes(n + 1);
        
        nodes[0] = root;

        for (int j = 1; j <= n; ++j) {
            nodes[j] = add_node(root, rand() % 500);
        }
        Node* p = nodes[rand() % (n + 1)];
        Node* q = nodes[rand() % (n + 1)];

        Node* res1 = LCA_my_solution1(p, q);
        Node* res2 = LCA_my_solution2(p, q);
        Node* res3 = LCA_my_solution3(p, q);
        Node* res4 = CORRECT_lowestCommonAncestor(p, q);
        if (res1 == res2 && res1 == res3 && res1 == res4) {
            cout << "Test " << i + 1 << " SUCCESS" << endl;
            // print(root, 0);
            // cout << "P->val = " << p->val << endl;
            // cout << "Q->val = " << q->val << endl;
            // cout << "RES = " << res1->val << endl;
            // cout << "\n\n\n\n" << endl;
        } else {
            cout << "Test " << i + 1 << " ERROR" << endl;
            print(root, 0);
            cout << "P->val = " << p->val << endl;
            cout << "Q->val = " << q->val << endl;
            cout << "RES1->val = " << res1->val << endl;
            cout << "RES2->val = " << res2->val << endl;
            cout << "RES3->val = " << res3->val << endl;
            cout << "RES3->val = " << res4->val << endl;
            break;
        }
    }
}