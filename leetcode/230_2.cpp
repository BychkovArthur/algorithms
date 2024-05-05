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
    Solution without recursion
*/
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> st;
        st.push(root);

        int curr_k = 0;
        
        while (!(st.size() == 1 && !st.top())) {
            if (st.top()) {
                st.push(st.top()->left);
            } else {
                st.pop();
                TreeNode* node = st.top();
                ++curr_k;
                if (curr_k == k) {
                    return node->val;
                }
                st.pop();
                st.push(node->right);
            }
        }
        return -1;
    }
};  