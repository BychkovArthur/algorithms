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

    enum class ContainsType {
        P,
        Q,
        Nothing,
        Both
    };

    int height(TreeNode* node) {
        if (!node) {
            return 0;
        }
        return max(height(node->left), height(node->right)) + 1;
    }

    pair<int, ContainsType> helper(TreeNode* node, TreeNode* p, TreeNode* q, int ph, int qh, TreeNode*& res) {
        if (!node) {
            return {0, ContainsType::Nothing};
        }

        auto left = helper(node->left, p, q, ph, qh, res);
        auto right = helper(node->right, p, q, ph, qh, res);
        int h = max(left.first, right.first) + 1;


        /*
            Если с одной из сторон уже есть ответ, то дальше искать обнавлять ничего нет смысла.
        */
        if (left.second == ContainsType::Both || right.second == ContainsType::Both) {
            return {h, ContainsType::Both};
        }

        /*
            Когда они на одинаковых глубинах, то при высоте ph=qh может быть только один случай,
            мы встретили или p или q.
        */

        if (ph == qh && h == ph) {
            if (node == p) {
                return {h, ContainsType::P};
            }
            if (node == q) {
                return {h, ContainsType::Q};
            }
            return {h, ContainsType::Nothing};

        } else if (h == ph) {
            bool contains_p = node == p;
            // Мы сейчас на p и в одном из детей есть q.
            if (contains_p && (left.second == ContainsType::Q || right.second == ContainsType::Q)) {
                res = node;
                return {h, ContainsType::Both};
            }
            // Мы на p и оба ребенка - пустые.
            if (contains_p && left.second == ContainsType::Nothing && right.second == ContainsType::Nothing) {
                return {h, ContainsType::P};
            }
            // Мы не на p, но в одном из детей встретили q.
            if (!contains_p && (left.second == ContainsType::Q || right.second == ContainsType::Q)) {
                return {h, ContainsType::Q};
            }
            
            // Нет p и ни один из детей ничего не значил.
            return {h, ContainsType::Nothing};

        } else if (h == qh) {
            bool contains_q = node == q;
            // Мы сейчас на q и в одном из детей есть p.
            if (contains_q && (left.second == ContainsType::P || right.second == ContainsType::P)) {
                res = node;
                return {h, ContainsType::Both};
            }
            // Мы на q и оба ребенка - пустые.
            if (contains_q && left.second == ContainsType::Nothing && right.second == ContainsType::Nothing) {
                return {h, ContainsType::Q};
            }

            // Мы не на q, но в одном из детей встретили p.
            if (!contains_q && (left.second == ContainsType::P || right.second == ContainsType::P)) {
                return {h, ContainsType::P};
            }

            // Нет q и ни один из детей ничего не значил.
            return {h, ContainsType::Nothing};
        // Теперь уже где-то найдено и p и q.
        } else {
            // С одной стороны p, с другой - q.
            if ((left.second == ContainsType::P && right.second == ContainsType::Q) ||
                (left.second == ContainsType::Q && right.second == ContainsType::P)) {
                res = node;
                return {h, ContainsType::Both};
            }
            // С одной из сторон p, с другой - nothing.
            if (left.second == ContainsType::P || right.second == ContainsType::P) {
                return {h, ContainsType::P};
            }
            // С одной из сторон q, с другой - nothing.
            if (left.second == ContainsType::Q || right.second == ContainsType::Q) {
                return {h, ContainsType::Q};
            }
            return {h, ContainsType::Nothing};
        }
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        int ph = height(p);
        int qh = height(q);
        TreeNode* res = nullptr;
        helper(root, p, q, ph, qh, res);
        return res;
    }
};