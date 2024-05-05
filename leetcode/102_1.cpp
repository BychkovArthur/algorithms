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
    Через BFS
*/
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> vct;
        queue<TreeNode*> q;
        q.push(root);

        if (!root) {
            return vct;
        }
        int j = 0;
        while (!q.empty()) {
            vct.emplace_back();
            size_t sz = q.size();
            for (size_t i = 0; i < sz; ++i) {
                TreeNode* node = q.front();
                q.pop();
                vct[j].push_back(node->val);
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
            ++j;
        }
        return vct;
    }
};