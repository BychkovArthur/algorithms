/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        // (1) Делаем так, чтобы после каждого узла исходного списка шёл узел нашего списка с таким же значением.
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            curr->next = new Node(curr->val);
            curr->next->next = next;
            curr = next;
        }

        // (2) Теперь добавляем связь random
        curr = head;
        while (curr) {
            if (!curr->random) {
                curr->next->random = nullptr;
            } else {
                curr->next->random = curr->random->next;
            }
            curr = curr->next->next;
        }

        // (3) Разъединяем эти списки.
        curr = head;
        Node* res = nullptr;
        while (curr) {
            Node* copy = curr->next;
            curr->next = curr->next->next;
            copy->next = copy->next ? copy->next->next : nullptr;
            if (!res) {
                res = copy;
            }
            curr = curr->next;
        }
        return res;
    }
};