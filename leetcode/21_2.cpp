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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* head = nullptr;
        ListNode* prev = nullptr;
        ListNode* curr = nullptr;

        while (list1 || list2) {
            if (!list1 || (list2 && list2->val < list1->val)) {
                curr = list2;
                list2 = list2->next;
            } else {
                curr = list1;
                list1 = list1->next;
            }

            if (!head) {
                head = curr;
            }

            if (prev) {
                prev->next = curr;
            }
            prev = curr;
        }
        return head;
    }
};