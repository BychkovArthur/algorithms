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
    Recursive solution
*/
class Solution {
public:
    void kthSmallest(TreeNode* node, int k, int& number, int& res) {
        if (!node) {
            return;
        }

        kthSmallest(node->left, k, number, res);

        ++number;
        if (number == k) {
            res = node->val;
        }

        kthSmallest(node->right, k, number, res);
    }

    int kthSmallest(TreeNode* root, int k) {
        int number = 0;
        int res = 0;
        kthSmallest(root, k, number, res);
        return res;
    }
};