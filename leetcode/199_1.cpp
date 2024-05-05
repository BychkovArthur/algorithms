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
    Решение через DFS
*/
class Solution {
public:
    void rightSideView(TreeNode* node, int level, int& max_level, vector<int>& vct) {
        if (!node) {
            return;
        }
        if (level > max_level) {
            max_level = level;
            vct.push_back(node->val);
        }
        rightSideView(node->right, level + 1, max_level, vct);
        rightSideView(node->left, level + 1, max_level, vct);
    }

    vector<int> rightSideView(TreeNode* root) {
        vector<int> vct;
        int max_level = -1;
        rightSideView(root, 0, max_level, vct);
        return vct;
    }
};