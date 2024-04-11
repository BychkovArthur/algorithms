/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        unordered_set<ListNode*> visited;

        ListNode* curr = head;
        while (curr) {
            if (visited.contains(curr)) {
                return true;
            }
            visited.insert(curr);
            curr = curr->next;
        }
        return false;
    }
};