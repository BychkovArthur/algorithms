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

/*
    DFS Iterative
*/
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode*> st;
        st.push(root);

        while (!(st.size() == 1 && !st.top())) {
            if (st.top()) {
                st.push(st.top()->left);
            } else {
                st.pop();
                TreeNode* node = st.top();
                st.pop();
                st.push(node->right);
                ans.push_back(node->val);
            }
        }
        return ans;
    }
};