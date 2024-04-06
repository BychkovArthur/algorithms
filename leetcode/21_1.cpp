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

        while (list1 || list2) {
            ListNode* new_node = new ListNode();
            if (!head) {
                head = new_node;
            }
            if (!list1 || (list2 && list2->val < list1->val)) {
                new_node->val = list2->val;
                list2 = list2->next;
            } else {
                new_node->val = list1->val;
                list1 = list1->next;
            }

            if (prev) {
                prev->next = new_node;
            }
            prev = new_node;
        }
        return head;
    }
};