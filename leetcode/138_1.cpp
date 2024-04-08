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


/*
*   1) Заполнить map следющим образом:
*      - Ключ для Node a это a->next
*      - Значение для Node a это порядковый номер.
*
*      Т.к. указатель на следующего это уникальный для каждой вершины объект мы теперь
*      знаем, про каждую вершину, какой у нее порядковый номер.
*      !!! Не значени Node не random не являются уникальными для вершин. Только по указателю
*      на следующую вершину мы можем дифференцировать вершины друг от друга.
*
*    2) Создадим копию списка, попутно сохранив в векторе адреса каждой из вершин.
*       Для наших новых вершин указатель random пока что не трогаем, оставляем nullptr
*
*    3) Добавляем связи используя мапу и вектор.
*
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        // (1) Заполнение мапы.
        unordered_map<Node*, int> mp;
        Node* curr = head;
        int k = 0;

        while (curr) {
            curr = curr->next;
            mp[curr] = k++;
        }
        if (k == 0) {
            return nullptr;
        }

        // (2) Создаём копию и запоминаем адреса.
        vector<Node*> nodes(k);
        curr = head;
        for (int i = 0; i < k; ++i) {
            nodes[i] = new Node(curr->val);
            if (i > 0) {
                nodes[i - 1]->next = nodes[i];
            }
            curr = curr->next;
        }

        // (3) Добавляем связи
        curr = head;
        for (int i = 0; i < k; ++i) {
            Node* key = curr->random;

            if (!key) {
                nodes[i]->random = nullptr;
            } else {
                nodes[i]->random = nodes[mp[key->next]];
            }

            curr = curr->next;
        }
        return nodes[0];
    }
};