/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q, bool& find) {
        if (!root) return nullptr;

        TreeNode* l = lowestCommonAncestor(root->left, p, q, find);
        TreeNode* r = lowestCommonAncestor(root->right, p, q, find);

        if (find && l) return l;
        if (find && r) return r;

        if (l && r) {
            find = true;
            return root;
        }
        if (root == p && (l == q || r == q)) {
            find = true;
            return root;
        }
        if (root == q && (l == p || r == p)) {
            find = true;
            return root;
        }
        if (root == p || root == q) return root;
        if (l) return l;
        if (r) return r;
        return nullptr;
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        bool find = false;
        return lowestCommonAncestor(root, p, q, find);
    }
};