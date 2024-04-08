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
*    1) Найдём сразу середину списка, использовав быстрый и медленный указатели.
*    2) Переворачиваем правую половину списка.
*    3) Сливаем всё в один список.
*/
    void reorderList(ListNode* head) {

        if (!head->next) {
            return;
        }
        
        // (1) Находим центр
        // После этого у меня левая часть списка полностью отделена от правой части
        // В левой части у меня последнее ссылается на NULL
        ListNode* slow = head;
        ListNode* prev = nullptr;
        ListNode* fast = head->next;

        while (fast) {
            prev = slow;
            slow = slow->next;
            if (fast->next) {
                fast = fast->next->next;
            } else {
                fast = fast->next;
            }
        }
        prev->next = nullptr;

        // (2) Переворачиваем правую половину списка.
        prev = nullptr;
        ListNode* curr = slow;
        while (curr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        // (3) Сливаем всё воедино.
        // Сейчас у нас два массива, которые не пересекаются.
        ListNode* left = head;
        ListNode* right = prev;
        curr = head;
        while (left) {
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