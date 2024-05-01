/*
    Без рекурсии, но мы эмулируем стек вызовов сами.
    Это называется Iterative DFS
*/


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:

    int maxDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        stack<pair<TreeNode*, int>> st;
        int res = 0;

        st.push({root, 1});

        while (!st.empty()) {
            TreeNode* node = st.top().first;
            int depth = st.top().second;
            st.pop();
            if (node->right) {
                st.push({node->right, depth + 1});
            }
            if (node->left) {
                st.push({node->left, depth + 1});
            }
            res = max(res, depth);
        }
        return res;
    }
};