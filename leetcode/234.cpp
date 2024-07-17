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
    bool isPalindrome(ListNode* head) {
        int n = 0;
        ListNode* curr = head;
        while (curr) {
            ++n;
            curr = curr->next;
        }

        if (n == 1) return true;

        curr = head;
        for (int i = 0; i < (n + 1) / 2; ++i) {
            curr = curr->next;
        }

        ListNode* prev = nullptr;
        while (curr) {
            auto next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        ListNode* new_head = prev;

        bool res = true;
        ListNode* curr1 = head;
        ListNode* curr2 = new_head;
        for (int i = 0; i < n / 2; ++i) {
            if (curr1->val != curr2->val) {
                res = false;
                break;
            }
            curr1 = curr1->next;
            curr2 = curr2->next;
        }

        // Восстановление списка.
        prev = nullptr;
        curr = new_head;
        while (curr) {
            auto next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        // curr = head;
        // while (curr) {
        //     cout << curr->val << ' ';
        //     curr = curr->next;
        // }
        return res;
    }
};