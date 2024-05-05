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
    int goodNodes(TreeNode* node, int mx) {
        if (!node) {
            return 0;
        }
        int res = goodNodes(node->left, max(mx, node->val)) + goodNodes(node->right, max(mx, node->val));
        if (node->val >= mx) {
            ++res;
        }
        return res;
    }
    int goodNodes(TreeNode* root) {
        return goodNodes(root, root->val);
    }
};