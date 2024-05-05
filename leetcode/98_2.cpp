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
        if (!node->left && !node->right) {
            return {true, node->val, node->val};

        } else if (node->left && !node->right) {
            Info left = helper(node->left);
            if (left.isValid && node->val > left.mx) {
                return {true, left.mn, node->val};
            }

        } else if (node->right && !node->left) {
            Info right = helper(node->right);
            if (right.isValid && node->val < right.mn) {
                return {true, node->val, right.mx};
            }

        } else {
            Info left = helper(node->left);
            Info right = helper(node->right);

            if (left.isValid && right.isValid &&
                node->val > left.mx && node->val < right.mn
                ) {
                return {true, left.mn, right.mx};
            }
        }
        return {false, INT64_MAX, INT64_MIN};
    }

    bool isValidBST(TreeNode* root) {
        return helper(root).isValid;
    }
};