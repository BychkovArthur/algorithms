#include <iostream>
#include <vector>
#include <queue>
#include <stack>

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int val) : val(val) {};
};

std::ostream& operator<<(std::ostream& os, const std::vector<int>& vct) {
    int n = vct.size();
    for (int i = 0; i < n; ++i) {
        os << vct[i];
        if (i < n - 1) {
            os << ' ';
        }
    }
    return os;
}




void recursive_preorder_dfs(Node* node, std::vector<int>& vct) {
    if (!node) {
        return;
    }
    vct.push_back(node->val);
    recursive_preorder_dfs(node->left, vct);
    recursive_preorder_dfs(node->right, vct);
}

void recursive_inorder_dfs(Node* node, std::vector<int>& vct) {
    if (!node) {
        return;
    }
    recursive_inorder_dfs(node->left, vct);
    vct.push_back(node->val);
    recursive_inorder_dfs(node->right, vct);
}

void recursive_postorder_dfs(Node* node, std::vector<int>& vct) {
    if (!node) {
        return;
    }
    recursive_postorder_dfs(node->left, vct);
    recursive_postorder_dfs(node->right, vct);
    vct.push_back(node->val);
}




void iterative_preorder_dfs(Node* root, std::vector<int>& vct) {
    std::stack<Node*> st;
    st.push(root);

    while (!st.empty()) {
        Node* node = st.top();
        st.pop();
        vct.push_back(node->val);
        if (node->right) {
            st.push(node->right);
        }
        if (node->left) {
            st.push(node->left);
        }
    }
}

void iterative_inorder_dfs(Node* root, std::vector<int>& vct) {
    std::stack<Node*> st;
    st.push(root);
    while (!(st.size() == 1 && !st.top())) {
        Node* node = st.top();
        if (node) {
            st.push(node->left);
        } else {
            st.pop();
            node = st.top();
            st.pop();
            st.push(node->right);
            vct.push_back(node->val);
        }
    }
}

void iterative_postorder_dfs(Node* root, std::vector<int>& vct) {
    std::stack<Node*> st;
    st.push(root);
    while (!(st.size() == 1 && !st.top())) {
        Node* fst = st.top();
        if (fst) {            // Нет null на вершине
            st.push(fst->right);
            st.push(fst->left);
        } else {
            st.pop();
            Node* scnd = st.top();
            st.pop();
            if (scnd) {      // Вершина - null, под ней не null. Надо сделать swap.
                st.push(fst);
                st.push(scnd);
            } else {         // Оба null. Надо обработать то, что лежит под ними.
                Node* thrd = st.top();
                st.pop();
                vct.push_back(thrd->val);
                st.push(nullptr);
            }
        }
    }
    
}


void left_right_bfs(Node* root, std::vector<std::vector<int>>& vct) {
    std::queue<Node*> q;
    q.push(root);

    size_t j = 0;

    while (!q.empty()) {
        size_t sz = q.size();
        vct.emplace_back();
        
        for (size_t i = 0; i < sz; ++i) {
            Node* node = q.front();
            q.pop();
            vct[j].push_back(node->val);
            if (node->left) {
                q.push(node->left);
            }
            if (node->right) {
                q.push(node->right);
            }
        }
        ++j;
    } 
}

void right_left_bfs(Node* root, std::vector<std::vector<int>>& vct) {
    std::queue<Node*> q;
    q.push(root);

    size_t j = 0;

    while (!q.empty()) {
        size_t sz = q.size();
        vct.emplace_back();
        
        for (size_t i = 0; i < sz; ++i) {
            Node* node = q.front();
            q.pop();
            vct[j].push_back(node->val);
            if (node->right) {
                q.push(node->right);
            }
            if (node->left) {
                q.push(node->left);
            }
        }
        ++j;
    } 
}

int main() {

    Node* root = new Node(20);
    root->left = new Node(10);
    root->right = new Node(30);
    root->left->left = new Node(5);
    root->left->right = new Node(15);
    root->right->left = new Node(25);
    root->right->right = new Node(35);

    /*
        Дерево вида:

             __________20__________
             |                    |
        _____10_____         _____30_____
        |          |         |          |
        5          15        25         35
    */

    std::vector<int> recursive_preorder_dfs_vct;
    std::vector<int> recursive_inorder_dfs_vct;
    std::vector<int> recursive_postorder_dfs_vct;

    std::vector<int> iterative_preorder_dfs_vct;
    std::vector<int> iterative_inorder_dfs_vct;
    std::vector<int> iterative_postorder_dfs_vct;

    std::vector<std::vector<int>> left_right_bfs_vct;
    std::vector<std::vector<int>> right_left_bfs_vct;

    recursive_preorder_dfs(root, recursive_preorder_dfs_vct);
    recursive_inorder_dfs(root, recursive_inorder_dfs_vct);
    recursive_postorder_dfs(root, recursive_postorder_dfs_vct);

    iterative_preorder_dfs(root, iterative_preorder_dfs_vct);
    iterative_inorder_dfs(root, iterative_inorder_dfs_vct);
    iterative_postorder_dfs(root, iterative_postorder_dfs_vct);

    left_right_bfs(root, left_right_bfs_vct);
    right_left_bfs(root, right_left_bfs_vct);

    std::cout << "Recursive PreOrder DFS: " << recursive_preorder_dfs_vct << std::endl;
    std::cout << "Recursive InOrder DFS: " << recursive_inorder_dfs_vct << std::endl;
    std::cout << "Recursive PostOrder DFS: " << recursive_postorder_dfs_vct << std::endl;
    std::cout << "\n\n\n" << std::endl;

    std::cout << "Iterative PreOrder DFS: " << iterative_preorder_dfs_vct << std::endl;
    std::cout << "Iterative InOrder DFS: " << iterative_inorder_dfs_vct << std::endl;
    std::cout << "Iterative PostOrder DFS: " << iterative_postorder_dfs_vct << std::endl;
    std::cout << "\n\n\n" << std::endl;

    std::cout << "Left-Right BFS: " << std::endl;
    for (const auto& vct : left_right_bfs_vct) {
        std::cout << vct << std::endl;
    }
    std::cout << "Right-Left BFS: " << std::endl;
    for (const auto& vct : right_left_bfs_vct) {
        std::cout << vct << std::endl;
    }
}