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
    Через DFS
*/
class Solution {
public:
    void levelOrder(TreeNode* node, vector<vector<int>>& vct, int level) {
        if (level == vct.size()) {
            vct.emplace_back();
        }
        vct[level].push_back(node->val);
        if (node->left) {
            levelOrder(node->left, vct, level + 1);
        }
        if (node->right) {
            levelOrder(node->right, vct, level + 1);
        }
    }

    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> vct;
        if (root) {
            levelOrder(root, vct, 0);
        }
        return vct;
    }
};