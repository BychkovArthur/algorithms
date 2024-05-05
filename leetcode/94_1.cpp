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
    DFS Recursive
*/
class Solution {
public:
    void dfs(TreeNode* node, vector<int>& vct) {
        if (!node) {
            return;
        }
        dfs(node->left, vct);
        vct.push_back(node->val);
        dfs(node->right, vct);
    }

    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        dfs(root, ans);
        return ans;
    }
};