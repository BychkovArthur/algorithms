/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
/*
*    1) Надём длину списка и его конец.
*    2) Найдём середину списка.
*    3) Переворачиваем правую половину списка.
*    4) Сливаем всё в один список.
*/
    void reorderList(ListNode* head) {
        // Находим длину, (1)
        size_t n = 1;
        ListNode* curr = head;
        while (curr->next) {
            ++n;
            curr = curr->next;
        }

        if (n == 1) { // Можно ли без ифа???? По идее нет, т.к. придётся ифать в пункте 2 prev->next = null;
            return;
        }
        
        // Находим центр, (2)
        // После этого у меня левая часть списка полностью отделена от правой части
        // В левой части у меня последнее ссылается на NULL
        curr = head;
        ListNode* prev = nullptr;
        for (size_t i = 0; i < n / 2; ++i) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = nullptr;

        // Переворачиваем правую половину списка, (3)
        prev = nullptr;
        while (curr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        // while (prev) {
        //     cout << prev->val << endl;
        //     prev = prev->next;
        // }
        // cout << "______________________" << endl;

        // while (head) {
        //     cout << head->val << endl;
        //     head = head->next;
        // }

        // cout << "Length = " << n << endl;

        // 4) Сливаем всё воедино.
        // Сейчас у нас два массива, которые не пересекаются.

        ListNode* left = head;
        ListNode* right = prev;
        curr = head;
        for (size_t i = 0; i < n / 2; ++i) {
            ListNode* lnext = left->next;
            ListNode* rnext = right->next;
            curr->next = right;
            if (lnext) {
                curr->next->next = lnext;
            }
            left = lnext;
            right = rnext;
            curr = curr->next->next;
        }
    }
};