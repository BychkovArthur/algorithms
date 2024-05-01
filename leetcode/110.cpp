/*
    Здесь так же, как и в задаче 543 нельзя без доп функции, т.к. необходимо возвращать, подходящее ли дерево, а так же, текущую глубину.
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
    int isBalanced(TreeNode* node, bool& balanced) {
        if (!node) {
            return 0;
        }

        int left_height = isBalanced(node->left, balanced) + 1;
        int right_height = isBalanced(node->right, balanced) + 1;
        if (abs(left_height - right_height) > 1) {
            balanced = false;
        }
        return max(left_height, right_height);
    }

    bool isBalanced(TreeNode* root) {
        bool balanced = true;
        isBalanced(root, balanced);
        return balanced;
    }
};