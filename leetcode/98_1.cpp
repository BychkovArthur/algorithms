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
    struct Info {
        bool isValid;
        long long mn;
        long long mx;
    };

    Info helper(TreeNode* node) {
        if (!node) {
            return {true, INT64_MAX, INT64_MIN};
        }

        Info left = helper(node->left);
        Info right = helper(node->right);

        if (left.isValid && right.isValid &&
            node->val > left.mx && node->val < right.mn
            ) {
            // По сути, min и max нужны только чтобы у листьев вернуть верные значения.
            // Если в листьях возвращаются верные значения, то в дальнейшем можно просто
            // возвращать {true, left.mn, right.mx}
            return {true, min(left.mn, (long long)node->val), max(right.mx, (long long)node->val)};
        }

        return {false, INT64_MAX, INT64_MIN};
    }

    bool isValidBST(TreeNode* root) {
        return helper(root).isValid;
    }
};