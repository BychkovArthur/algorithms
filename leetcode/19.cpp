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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* prev = nullptr;
        ListNode* l = head;
        ListNode* r = head;
        ListNode* res = nullptr;
        for (int i = 0; i < n - 1; ++i) {
            r = r->next;
        }

        while (r->next) {
            prev = l;
            r = r->next;
            l = l->next;
        }

        if (!prev) {
            res = head->next;
            delete head;
        } else {
            ListNode* to_del = prev->next;
            prev->next = prev->next->next;
            delete to_del;
            res = head;
        }
        return res;
    }
};