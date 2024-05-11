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
    struct custom_less {
        bool operator()(const ListNode* a, const ListNode* b) const {
            return a->val > b->val;
        }
    };
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        custom_less comp;
        priority_queue<ListNode*, std::vector<ListNode*>, custom_less> pq;

        for (ListNode* node : lists) {
            if (node) pq.push(node);
        }

        ListNode* head = nullptr;
        ListNode* curr = nullptr;

        while (!pq.empty()) {
            ListNode* node = pq.top();
            cout << node->val << endl;
            pq.pop();
            if (node->next) pq.push(node->next);
            if (!head) {
                head = node;
                curr = node;
            } else {
                curr->next = node;
                curr = curr->next;
            }
        }

        return head;
    }
};