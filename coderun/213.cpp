#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

struct NodeInfo {
    string s;
    int next; // Это номер следующего узла в векторе
};


struct CompactTrie {
    vector<unordered_map<char, NodeInfo>> nodes;

    // Изначально просто добавляю корень.
    CompactTrie() : nodes(1) {}

    void push(const string& s) {
        size_t n = s.size();
        int curr_node = 0;
        int curr_str_ind = 0;
        char curr_map_char = 0;
        bool in_string = false;

        for (size_t i = 0; i < n; ++i) {
            // Я перешел в новый узел
            if (!in_string) {
                // В новом узле нет следующей буквы. Создаем новое ребро.
                if (!nodes[curr_node].contains(s[i])) {
                    nodes[curr_node][s[i]] = NodeInfo{s.substr(i), -1};
                    return;
                }
                in_string = true;
                curr_str_ind = 0;
                curr_map_char = s[i];
            }
            // Теперь обрабатываю строку на ребре
            // По идее, эту часть можно улучшить, т.к.
            // Здесь я много раз буду доставать элемент из мапы

            // Символ на ребре не совпал с текущим символом строки 
            // (один символ 100% совпал, т.к. это проверяется выше, при создании вершина)
            // Надо разделять ребро
            if (s[i] != nodes[curr_node][curr_map_char].s[curr_str_ind]) {
                // Не совпало на i-м символе. Значит, совпало ровно i символов.
                // Обрежем текущее ребро
                unordered_map<char, NodeInfo> mp;
                int prev_next_node = nodes[curr_node][curr_map_char].next;

                string s1 = nodes[curr_node][curr_map_char].s.substr(curr_str_ind); // То, что останется от текущего ребра после разреза.
                // std::cout << "Node before resize" << nodes[curr_node][curr_map_char].s << std::endl;
                nodes[curr_node][curr_map_char].s.resize(curr_str_ind); // Обрезаю ту часть ребра, которая будет выше нового узла
                // std::cout << "Node after resize" << nodes[curr_node][curr_map_char].s << std::endl;
                nodes[curr_node][curr_map_char].next = nodes.size();

                mp[s1[0]] = NodeInfo{s1, prev_next_node};
                mp[s[i]] = NodeInfo{s.substr(i), -1};
                nodes.push_back(std::move(mp));
                return;
            }

            ++curr_str_ind;
            // Достигли конца строки. Переходим к следующему ребру.
            if (curr_str_ind == nodes[curr_node][curr_map_char].s.size()) {
                curr_node = nodes[curr_node][curr_map_char].next;
                in_string = false;
            }
        }
    }

    bool contains(const string& s) {
        int curr_node = 0;
        int curr_str_ind = 0;
        char curr_map_char = 0;
        bool in_string = false;

        for (char c : s) {
            // Я перешел в новый узел
            if (!in_string) {
                // std::cout << "C = " << c << std::endl;
                // std::cout << "node = " << curr_node << "str ind = " << curr_str_ind << std::endl; 
                if (!nodes[curr_node].contains(c)) return false;
                // std::cout << "After" << std::endl;
                in_string = true;
                curr_str_ind = 0;
                curr_map_char = c;
            }
            // Теперь обрабатываю строку на ребре
            // По идее, эту часть можно улучшить, т.к.
            // Здесь я много раз буду доставать элемент из мапы

            // Символ на ребре не совпал с текущим символом строки
            if (c != nodes[curr_node][curr_map_char].s[curr_str_ind]) return false;

            ++curr_str_ind;
            // Достигли конца строки. Переходим к следующему ребру.
            if (curr_str_ind == nodes[curr_node][curr_map_char].s.size()) {
                curr_node = nodes[curr_node][curr_map_char].next;
                in_string = false;
            }
        }

        return curr_node == -1;
    }

    int calc_price(const string& s) {
        size_t n = s.size();
        int curr_node = 0;
        int curr_str_ind = 0;
        char curr_map_char = 0;
        bool in_string = false;

        for (size_t i = 0; i < n; ++i) {
            // Я перешел в новый узел
            if (!in_string) {

                in_string = true;
                curr_str_ind = 0;
                curr_map_char = s[i];
                if (nodes[curr_node][curr_map_char].next == -1 && curr_map_char == '$') return n - 1;
                if (nodes[curr_node][curr_map_char].next == -1) return i + 1;
            }
            // Теперь обрабатываю строку на ребре
            // По идее, эту часть можно улучшить, т.к.
            // Здесь я много раз буду доставать элемент из мапы

            ++curr_str_ind;
            // Достигли конца строки. Переходим к следующему ребру.
            if (curr_str_ind == nodes[curr_node][curr_map_char].s.size()) {
                curr_node = nodes[curr_node][curr_map_char].next;
                in_string = false;
            }
        }

        return curr_node == -1;
    }
};


/*
    1) Сначала надо проверить, есть ли текущая строка в Trie.
        1) Если ее нет, то просто добавляем и к ответу прибавляем длину строки
        2) Если же эта строка есть:
            1) Найдем, сколько символов необходимо напечатать, чтобы получить эту строку.


*/



int main() {
    // CompactTrie ct;

    // unordered_map<char, NodeInfo> mp = {{'a', {string("arut$"), -1}},
    //     {'b', {string("bebra$"), -1}},
    //     {'c', {string("cmo$"), -1}}};


    // ct.nodes[0] = mp;

    // ct.push("cmo$");
    // ct.push("cmo$");
    // ct.push("cmo$");
    // ct.push("cmo$");
    // ct.push("cmo$");
    // ct.push("arut$");
    // ct.push("bebra$");
    // ct.push("a$");
    // ct.push("arutt$");
    // ct.push("aru$");
    // ct.push("gay$");
    // ct.push("gorgeous$");

    // std::cout << ct.calc_price("cmo$") << std::endl;
    // std::cout << ct.calc_price("a$") << std::endl;
    // std::cout << ct.calc_price("arut$") << std::endl;
    // std::cout << ct.calc_price("arutt$") << std::endl;
    // std::cout << ct.calc_price("gay$") << std::endl;
    // std::cout << ct.calc_price("gorgeous$") << std::endl;

    // std::cout << ct.contains("cmo$") << std::endl;
    // std::cout << ct.contains("bebra$") << std::endl;
    // std::cout << ct.contains("arut$") << std::endl;
    // std::cout << ct.contains("arut") << std::endl;
    // std::cout << ct.contains("a$") << std::endl;
    // std::cout << ct.contains("zzz$") << std::endl;
    // std::cout << ct.contains("arutt") << std::endl;
    // std::cout << ct.contains("arutt$") << std::endl;

    // string a = "arut$";
    // std::cout << a << std::endl;
    // a.resize(4);
    // std::cout << a << std::endl;

    int n;
    int res = 0;
    CompactTrie ct;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        s.push_back('$');
        if (!ct.contains(s)) {
            ct.push(s);
            res += s.size() - 1;
        } else {
            res += ct.calc_price(s);
        }
    }
    cout << res;
}