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

    bool isSame(TreeNode* p, TreeNode* q) {
        if (!p && !q) {
            return true;
        }
        if (!(p && q)) {
            return false;
        }

        return p->val == q->val && isSame(p->left, q->left) && isSame(p->right, q->right);
    }

    int height(TreeNode* node) {
        if (!node) {
            return 0;
        }
        return max(height(node->left), height(node->right)) + 1;
    }

    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        int tree_height = height(root);
        int subtree_height = height(subRoot);

        if (subtree_height > tree_height) {
            return false;
        }


        queue<pair<TreeNode*, int>> q;
        int target_height = tree_height - subtree_height + 1;
        q.push({root, 1});

        while (!q.empty()) {
            TreeNode* node = q.front().first;
            int level = q.front().second;
            q.pop();

            if (level < target_height) {
                if (node->left) {
                    q.push({node->left, level + 1});
                }
                if (node->right) {
                    q.push({node->right, level + 1});
                }
                if (isSame(node, subRoot)) {
                    return true;
                }
            } else if (level == target_height) {
                if (isSame(node, subRoot)) {
                    return true;
                }
            }
        }
        return false;
    }
};