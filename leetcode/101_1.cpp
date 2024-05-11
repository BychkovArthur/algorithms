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
    bool isSymmetric(TreeNode* root) {
        if (!root->right && !root->left) return true;

        vector<TreeNode*> nodes;
        if (root->left && root->right && root->left->val == root->right->val) {
            nodes.push_back(root->left);
            nodes.push_back(root->right);
        } else {
            return false;
        }

        while (!nodes.empty()) {
            int n = nodes.size();
            int l = 0;
            int r = n - 1;
            while (l < r) {
                TreeNode* left_node = nodes[l++];
                TreeNode* right_node = nodes[r--];
                if (!(
                    (
                        (left_node->right && right_node->left && left_node->right->val == right_node->left->val) || 
                        (!left_node->right && !right_node->left)
                    ) &&
                    (
                        (left_node->left && right_node->right && left_node->left->val == right_node->right->val) || 
                        (!left_node->left && !right_node->right)
                    )
                   )) {
                    return false;
                   }
            }
            vector<TreeNode*> new_nodes;
            for (TreeNode* node : nodes) { // Уровень, что я сейчас пушбэкаю точно хорош, т.к. он прошёл проверку выше.
                if (node->left) new_nodes.push_back(node->left);
                if (node->right) new_nodes.push_back(node->right);
            }
            nodes = move(new_nodes);
        }
        return true;
    }
};