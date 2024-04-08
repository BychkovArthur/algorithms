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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int remainder = 0;

        ListNode* dummy = new ListNode();
        ListNode* prev = dummy;

        while (l1 && l2) {
            int new_digit = l1->val + l2->val + remainder;
            if (new_digit > 9) {
                remainder = 1;
                new_digit -= 10;
            } else {
                remainder = 0;
            }
            prev->next = new ListNode(new_digit);
            prev = prev->next;
            l1 = l1->next;
            l2 = l2->next;
        }

        while (l1) {
            int new_digit = l1->val + remainder;
            if (new_digit > 9) {
                remainder = 1;
                new_digit -= 10;
            } else {
                remainder = 0;
            }
            prev->next = new ListNode(new_digit);
            prev = prev->next;
            l1 = l1->next;
        }

        while (l2) {
            int new_digit = l2->val + remainder;
            if (new_digit > 9) {
                remainder = 1;
                new_digit -= 10;
            } else {
                remainder = 0;
            }
            prev->next = new ListNode(new_digit);
            prev = prev->next;
            l2 = l2->next;
        }

        if (remainder) {
            prev->next = new ListNode(1);
        }

        ListNode* res = dummy->next;
        delete dummy;
        return res;
    }
};