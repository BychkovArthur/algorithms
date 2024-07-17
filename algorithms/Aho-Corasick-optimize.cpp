#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cstdint>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    for (const T& elem : v) {
        os << elem << ' ';
    }
    return os;
}

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::unordered_map<K, V>& mp) {
    for (const std::pair<K, V>& kv : mp) {
        os << kv.first << ": " << kv.second << '\n';
    }
    return os;
}

class AhoCorasick {
    struct Node {
        std::unordered_map<char, Node*> mp;
        
        Node* failure_link;
        Node* output_link;
        ssize_t pattern_number;

        Node() : mp(), failure_link(nullptr), output_link(nullptr), pattern_number(-1) {}
    };

    Node* root;
    const std::vector<std::string> patterns;

    void push_pattern(const std::string& pattern, ssize_t pattern_number) {
        Node* current = root;
        for (const char& letter : pattern) {
            if (!current->mp.contains(letter)) {
                current->mp[letter] = new Node();
            }
            current = current->mp[letter];
        }
        current->pattern_number = pattern_number;
    }

    bool is_terminal(Node* node) {
        return node->pattern_number != -1;
    }

    void add_failure_link(Node* parent, char target_letter) {

        /*
                    |--A1
            |--X1--X2
            |       |--A2
            R
            Для такого примера:
                1) parent = X2
                2) target_letter - буква, которая написана на ребре X2-A2 или на ребре X2-A1
                3) В итоге, я должен из вершины A1/A2 создать связь неудач.
                4) Причем, в одном выполнении этой функции я строю связь ровно для одной вершины (или только A1 или только A2).
                5) То, для какой вершины я это строю определяется target_letter - буквой на ребре.
                6) target_node - соответственно, или A1 или A2.
        */

        Node* target_node = parent->mp[target_letter];
        Node* current = parent->failure_link;

        /*
            Сначала будем идти до корня и пробовать продлить.
            Если нигде не получится продлить и мы оказались в корне, из которого
            не получилось продлить, завершаем поиск. Ссылка неудач будет на корень.
        */
        while (true) {
            // Мы прыгнули по ссылке и смогли продлить букву.
            if (current->mp.contains(target_letter)) {
                target_node->failure_link = current->mp[target_letter];
                break;
            }

            // Дошли до корня и не смогли продлить.
            // (Если бы мы могли продлить из корня, то условие выше сработало бы)
            if (current == root) {
                target_node->failure_link = root;
                break;
            }
            current = current->failure_link;
        }
    }

    void add_failure_links() {
        std::queue<Node*> nodes;

        // Для первых элементов связь неудач ведёт в корень
        for (auto& kv : root->mp) {
            kv.second->failure_link = root;
            nodes.push(kv.second);
        }

        /*  Теперь делаем индуктивный шаг.

            У нас построены все связи для для префиксов длины K.
            Будем строить связи неудач для префиксов длины K + 1.
        */
        
        while (!nodes.empty()) {
            size_t n = nodes.size();
            
            for (size_t _ = 0; _ < n; ++_) {
                // Одна конкретная вершина из BFS
                Node* current = nodes.front();
                nodes.pop();

                /*
                    Перебираем все вершины, для которых мы хотим построить
                    ссылки неудач.

                            |--A1
                    |--X1--X2
                    |       |--A2
                    R
                    В этом примере, если мы для вершин X2 и более ранних
                    вычислили суффиксные ссылки, то на текущем шаге

                    current = X2, и в цикле ниже перебираются вершины
                    A1 и A2
                */
                for (auto& kv : current->mp) {
                   add_failure_link(current, kv.first);
                   nodes.push(kv.second);
                }
            }
        }
    }

    void add_output_link(Node* start) {
        Node* current = start->failure_link;
        while (current != root) {
            if (is_terminal(current)) {
                start->output_link = current;
                break;
            }
            current = current->failure_link;
        }
    }

    void add_output_links() {
        std::queue<Node*> nodes;

        for (auto& kv : root->mp) {
            nodes.push(kv.second);
        }
        
        while (!nodes.empty()) {
            size_t n = nodes.size();
            
            for (size_t _ = 0; _ < n; ++_) {
                // Одна конкретная вершина из BFS
                Node* current = nodes.front();
                nodes.pop();
                
                add_output_link(current);

                for (auto& kv : current->mp) {
                    nodes.push(kv.second);
                }
            }
        }
    }

public:
    AhoCorasick(const std::vector<std::string>& patterns) : root(new Node()), patterns(patterns) {
        ssize_t pattern_number = 0;
        for (const std::string& pattern : patterns) {
            push_pattern(pattern, pattern_number++);
        }
        add_failure_links();
        add_output_links();
    }

    std::unordered_map<std::string, std::vector<size_t>> find(const std::string& text) {
        std::unordered_map<std::string, std::vector<size_t>> ans;
        size_t text_ptr = 0;
        Node* current = root;
        Node* current_cp = nullptr;

        while (text_ptr < text.size()) {
            bool contains = current->mp.contains(text[text_ptr]);
            
            if (current == root && !contains) {
                ++text_ptr;
                continue;
            } else if (contains) {
                // Только в случае, если я успешно сделал шаг по Trie
                // Я проверяю ответ. Иначе, сразу на следующую итерацию.
                current = current->mp[text[text_ptr]];
                ++text_ptr;
            } else {
                current = current->failure_link;
                continue;
            }

            current_cp = current;

            // Мы сейчас в терминальном узле
            if (is_terminal(current)) {
                size_t pattern_length = patterns[current->pattern_number].size();
                // Без (+1), т.к. я уже сдвинул text_ptr вперёд
                size_t index = text_ptr - pattern_length;
                ans[patterns[current->pattern_number]].push_back(index);
            }

            // Прыгаем по всем связям выхода
            while (current_cp->output_link) {
                current_cp = current_cp->output_link;
                size_t pattern_length = patterns[current_cp->pattern_number].size();
                // Без (+1), т.к. я уже сдвинул text_ptr вперёд
                size_t index = text_ptr - pattern_length;
                ans[patterns[current_cp->pattern_number]].push_back(index);
            }
        }
        
        return ans;
    }
};

using namespace std;

// unordered_map<string, vector<size_t>> naive(const vector<string>& patterns, string& text) {
//     unordered_map<string, vector<size_t>> ans;

//     for (const auto& pattern : patterns) {
//         for (size_t i = 0; i < text.size(); ++i) {
//             if (text.substr(i, pattern.size()) == pattern && find(ans[pattern].begin(), ans[pattern].end(), i) == ans[pattern].end()) {
//                 ans[pattern].push_back(i);
//             }
//         }
//     }
//     return ans;
// }

int main() {
    int t;
    cin >> t;
    for (int tt = 0; tt < t; ++tt) {
        string text;
        cin >> text;
        int n;
        cin >> n;
        vector<string> patterns(n);
        for (int i = 0; i < n; ++i) cin >> patterns[i];
        AhoCorasick ac(patterns);
        auto res = ac.find(text);

        for (int i = 0; i < n; ++i) {
            if (res.count(patterns[i])) {
                cout << 'y' << '\n';
            } else {
                cout << 'n' << '\n';
            }
        } 
    }
}

// int main() {
//     srand(time(NULL));
//     for (int _ = 0; _ < 1'000'000; ++_) {
//         int cnt = rand() % 50 + 20;
//         vector<string> patterns;
//         string text;
//         for (int i = 0; i < cnt; ++i) {
//             string s;
//             int n = rand() % 3 + 1;
//             for (int j = 0; j < n; ++j) {
//                 s.push_back('a' + rand() % 3);
//             }
//             patterns.push_back(s);
//         }
//         // cout << patterns << endl;

//         int n = rand() % 1000 + 100;
//         for (int i = 0; i < n; ++i) {
//             text.push_back('a' + rand() % 3);
//         }
//         // cout << text << endl;
        
//         auto ans1 = naive(patterns, text);
//         AhoCorasick ac(patterns);
//         auto ans2 = ac.find(text);

//         if (ans1 != ans2) {
//             cout << "Error on " << _ + 1 << endl;
//             cout << "Patterns = " << patterns << endl;
//             cout << "Text = " << text << endl;
//             cout << "Naive: " << endl << ans1;
//             cout << "Aho: " << endl << ans2;
//             break;
//         }
//         cout << "OK on " << _ + 1 << '\n';
//     }
// }

// int main() {
//     int n, m;
//     cin >> n;

//     vector<string> words(n);
//     for (int i = 0; i < n; ++i) cin >> words[i];

//     AhoCorasick ac(words);

//     cin >> m;
//     for (int i = 0; i < m; ++i) {
//         string s;
//         getline(cin, s);
//         // cout << "I = " << i << " " << s << std::endl;
//         auto mp = ac.find(s);
//         size_t mn = INT32_MAX;
//         if (!mp.empty()) {
//             for (const auto& el : mp) {
//                 for (const auto& ind : el.second) {
//                     mn = min(mn, ind);
//                 }
//             }
//             cout << i << ' ' << mn + 1;
//             return 0;
//         }
//     }
// }