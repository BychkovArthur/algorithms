/*
    Решение со вспомогательной функцией. Но без нее, кажется не решить, т.к. все решения используют доп функцию.

    Здесь нужна эта функция, т.к. мне нужно возвращать два параметра в рекурсии:

        1) Текущий максимальный ответ
        2) Максимальная глубина в текущем дереве.

        Например:

          _____X_____
     ___V___         X
    X       X
    |       |
    X       X
    |       |
    X       X
            |
            X

    В этом примере из вершины V мы должны вернуть две вещи:

        1) Текущий максимальный ответ res = 7
        2) Глубину этого дерева 4 (по правой стороне, она глубже)

    Таким образом, надо или менять сигнатуру исходной функции или добавлять новую функцию. Без вспомогательной - нет идей как сделать.

    И да, в этом примере ответ не проходит через корень. Через корень максимальный путь равен 6, а есть путь из 7 вершин.
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
    int diameterOfBinaryTree(TreeNode* root, int& res) {
        if (!root) {
            return -1;
        }
        if (!root->left && !root->right) {
            res = max(res, 0);
            return 0;
        }
        int left = diameterOfBinaryTree(root->left, res) + 1;
        int right = diameterOfBinaryTree(root->right, res) + 1;
        res = max(res, left + right);
        return max(left, right);

    }

    int diameterOfBinaryTree(TreeNode* root) {
        int res = 0;
        diameterOfBinaryTree(root, res);
        return res;
    }
};