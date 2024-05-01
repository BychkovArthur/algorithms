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
    С доп функцией
    Более логичное решение чем другое, т.к. использую доп функцию, в которой я ничего не возвращаю,
    вместо того, чтобы игнорировать возвращаемое значение в функции invertTree, как это в решении 226_2.cpp
*/
class Solution {
public:
    void swap_child(TreeNode* node) {
        if (!node) {
            return;
        }

        swap(node->left, node->right);
        swap_child(node->left);
        swap_child(node->right);
    }
    TreeNode* invertTree(TreeNode* root) {
        swap_child(root);
        return root;
    }
};