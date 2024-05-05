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
    Решение через BFS
*/
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> vct;
        if (!root) {
            return vct;
        }
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            size_t sz = q.size();
            for (size_t i = 0; i < sz; ++i) {
                TreeNode* node = q.front();
                q.pop();
                if (i == 0) {
                    vct.push_back(node->val);
                }
                if (node->right) {
                    q.push(node->right);
                }
                if (node->left) {
                    q.push(node->left);
                }
            }
        }
        return vct;
    }
};