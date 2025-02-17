/*
    Решение c использованием доп функции
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

    int maxDepth(TreeNode* node, int depth) {
        if (!node) {
            return depth - 1;
        }

        return max(maxDepth(node->left, depth + 1), maxDepth(node->right, depth + 1));
    }

    int maxDepth(TreeNode* root) {
        return maxDepth(root, 1);
    }
};