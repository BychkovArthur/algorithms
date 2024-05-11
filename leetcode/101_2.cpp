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
    Решение через рекурсию
*/
class Solution {
public:
    bool help(TreeNode* n1, TreeNode* n2) {
        if (!n1 && !n2) return true;
        if (!n1 && n2 || n1 && !n2) return false;
        return n1->val == n2->val && help(n1->left, n2->right) && help(n1->right, n2->left);
    }

    bool isSymmetric(TreeNode* root) {
        return help(root->left, root->right);
    }
};