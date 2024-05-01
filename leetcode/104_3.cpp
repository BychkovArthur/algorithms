/*
    Без рекурсии через BFS
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

    int maxDepth(TreeNode* root) {
        queue<pair<TreeNode*, int>> q;
        int res = 0;
        q.push({root, 1});

        while (!q.empty()) {
            TreeNode* node = q.front().first;
            int depth = q.front().second;
            q.pop();

            if (node) {
                q.push({node->left, depth + 1});
                q.push({node->right, depth + 1});
                res = max(res, depth);
            }
        }

        return res;
    }
};