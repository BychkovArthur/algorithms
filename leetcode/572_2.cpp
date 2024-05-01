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

    // Работает за O(min(N, M))
    bool isSame(TreeNode* p, TreeNode* q) {
        if (!p && !q) {
            return true;
        }
        if (!(p && q)) {
            return false;
        }

        return p->val == q->val && isSame(p->left, q->left) && isSame(p->right, q->right);
    }

    // Работает за O(N)
    int height(TreeNode* node) {
        if (!node) {
            return 0;
        }
        return max(height(node->left), height(node->right)) + 1;
    }

    /*
        Здесь первым делом происходит DFS, для нахождения глубины.
        Простой DFS работает за O(N)


        Однако, здесь на определенных уровнях (когда высота текущего поддерева исходного
        дерева root равна высоте subRoot) выполняется процедура isSame.

        Самый максимум, что мы сделаем в этом процедуре - пройдёмся по поддереву исходного
        дерева root полностью снова (т.к. сложность O(min(N, M)) ).

        Таким образом, мы перебираем все узлы из которых теоретически (совпадение высоты)
        может начаться subTree.

        В худшем случае для всего исходного дерава root мы сделаем дополнительно N операций,
        т.к. просто пройдёмся по всем вершинам ещё раз. Это случится, если мы запустим isSame
        от корня.
        Если же мы запускаем isSame не от корня, то всё, что выше этого уровня, никак дополнительно проверяться
        не будет. Т.е. мы сделаем меньше N дополнительных операций для сравнения деревьев.

        Например:

                      1
            ____________________
            |                   |
            2                  29
        _______
        |     |
        3     4

        Если в этом дереве мы будем искать поддерево 29, то процедура isSame запуститься только из вершин 29, 3, 4.
        Таким образом, мы повторно обойдём только деревья, которые начинаются в этих вершинах.
        
        Поддеревья из вершин 1 и 2 мы трогать не будем.
    */

    int helper(TreeNode* node, TreeNode* subRoot, bool& isSubtree, int subtree_height) {
        if (!node) {
            return 0;
        }

        int height = 1 + max(
            helper(node->left, subRoot, isSubtree, subtree_height),
            helper(node->right, subRoot, isSubtree, subtree_height)
        );

        if (height == subtree_height && !isSubtree) {
            isSubtree = isSame(node, subRoot);
        }

        return height;
    }

    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        int subtree_height = height(subRoot); // O(M)
        bool isSubtree = false;
        helper(root, subRoot, isSubtree, subtree_height);
        return isSubtree;
    }
};