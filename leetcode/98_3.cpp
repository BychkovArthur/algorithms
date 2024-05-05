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
    bool isValidBST(TreeNode* node, long long mx, long long mn) {
        if (!node) {
            return true;
        }
        return ((int)node->val < mx && (int)node->val > mn) &&
               isValidBST(node->left, node->val, mn) &&
               isValidBST(node->right, mx, node->val);
    }

    bool isValidBST(TreeNode* root) {
        return isValidBST(root, INT64_MAX, INT64_MIN);
    }
};