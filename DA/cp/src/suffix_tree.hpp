#pragma once
#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;
const ll INF = 1e18;

using Inds = pair<int, int>;

struct Node;
struct Edge {
    Inds inds;
    int size;
    Node* node = nullptr;
};

struct Node {
    map<int32_t, Edge> edges;
    Node* linkSuff = nullptr;
};

struct Position {
    Node* node = nullptr;
    int letter = -1;
    int offset;
};

class SuffTree {
public:
    SuffTree(const std::vector<int32_t> &text) : text(text) {
        root->linkSuff = root;
        cur.node = root;
    }

    void dtor(Node* const node) {
        for (auto const elem : node->edges) {
            dtor(elem.second.node);
        }
        delete node;
    }
    ~SuffTree() {
        dtor(root);
    }

    void Build() {
        for (int i = 0; i < text.size(); ++i) {
            addLetter(i);

            // cout << endl << i << endl << "=========================" << endl;
            // Print();
            // cout << "=========================" << endl;
        }
    }

    void Print() {
        print();
    }

    std::vector<size_t> BuildSuffixArray() {
        std::vector<size_t> result;
        SuffixArrayBuilder(root, result, 0);
        return result;
    }
private:
    Node* const root = new Node();
    Position cur;
    const std::vector<int32_t> text;

    // Суфф массив
    void SuffixArrayBuilder(Node* node, std::vector<size_t>& suffix_array, int length) {
        if (node->edges.empty()) { // В листе
            suffix_array.push_back(text.size() - length);
            return;
        }

        for (const auto& edge : node->edges) {
            SuffixArrayBuilder(edge.second.node, suffix_array, length + edge.second.size);
        }
    }

    // Печать

    const void numbering(const Node* const node, int &counter, unordered_map<const Node*, int> &m) {
        m[node] = counter;
        for (auto const elem : node->edges) {
            ++counter;
            numbering(elem.second.node, counter, m);
        }
    }
    const void printNodes(const Node* const node, const unordered_map<const Node*, int> &m) {
        for (auto const elem : node->edges) {
            cout << m.at(node) << " " << m.at(elem.second.node) << " " << elem.second.inds.first << ":" << elem.second.inds.second << " len: " << elem.second.size << endl;
            printNodes(elem.second.node, m);
        }
    }
    const void printLinks(const Node* const node, const unordered_map<const Node*, int> &m) {
        if (node->edges.size())
            cout << m.at(node) << " " << m.at(node->linkSuff) << endl;
        for (auto const elem : node->edges) {
            printLinks(elem.second.node, m);
        }
    }
    const void print() {
        unordered_map<const Node*, int> m;
        int counter = 0;
        numbering(root, counter, m);

        cout << "Дерево:" << endl;
        printNodes(root, m);
        cout << endl << "Суффиксные ссылки:" << endl;
        printLinks(root, m);
    }


    // Построение

    const bool curIsInternal() {
        return (cur.letter == -1);
    }

    const bool checkExistsPathFromInternal(const Node* node, const int letter) {
        return (node->edges.find(text[letter]) != node->edges.end());
    }
    const bool checkExistsPathFromEdge(const Node* node, const int letter, const int offset, const int letterTarget) {
        const int letterCur = node->edges.at(text[letter]).inds.first + offset + 1;
        return (text[letterCur] == text[letterTarget]);
    }
    bool tryMove(const int letter) {
        if (curIsInternal()) {
            if (checkExistsPathFromInternal(cur.node, letter)) {
                if (cur.node->edges[text[letter]].size == 1) {
                    cur.node = cur.node->edges[text[letter]].node;
                } else {
                    cur.letter = cur.node->edges[text[letter]].inds.first;
                    cur.offset = 0;
                }
            } else {
                return false;
            }
        } else {
            if (checkExistsPathFromEdge(cur.node, cur.letter, cur.offset, letter)) {
                if (cur.node->edges[text[cur.letter]].size - 1 == cur.offset + 1) {
                    cur.node = cur.node->edges[text[cur.letter]].node;
                    cur.letter = -1;
                } else {
                    ++cur.offset;
                }
            } else {
                return false;
            }
        }

        return true;
    }

    void createLeaf(Node* node, const int letter) {
        Node* const nodeNew = new Node();
        node->edges[text[letter]] = Edge{ Inds{letter, text.size() - 1}, (int)text.size() - letter, nodeNew };
    }
    Node* split(Node* node, const int letter, const int offset, const int letterTarget) {
        Node* const nodeNew = new Node();

        const Inds indsOld = node->edges[text[letter]].inds;
        const Inds indsNewFirst{indsOld.first, indsOld.first + offset};
        const Inds indsNewSecond{indsOld.first + offset + 1, indsOld.second};
        const int letterNew = indsNewSecond.first;

        Edge edgeFirst;
        edgeFirst.inds = indsNewFirst;
        edgeFirst.size = indsNewFirst.second - indsNewFirst.first + 1;
        edgeFirst.node = nodeNew;
        Edge edgeSecond;
        edgeSecond.inds = indsNewSecond;
        edgeSecond.size = indsNewSecond.second - indsNewSecond.first + 1;
        edgeSecond.node = node->edges[text[letter]].node;

        node->edges[text[letter]] = edgeFirst;
        nodeNew->edges[text[letterNew]] = edgeSecond;

        return nodeNew;
    }

    bool passingSuffLink() {
        Node* nodeLink = cur.node->linkSuff;
        if (!curIsInternal()) {
            // Прыжки по ссылкам
            int size = cur.offset + 1;
            int offset = 0;

            // Случай коренной вершины
            if (cur.node == root) {
                --size;
                ++offset;

                if (size == 0) {
                    cur.letter = -1;
                }
            }

            while (size > 0) {
                int letterCur = cur.letter + offset;

                if (nodeLink->edges.find(text[letterCur]) == nodeLink->edges.end()) {
                    return false;
                }

                if ( nodeLink->edges[text[letterCur]].size <= size ) {
                    size -= nodeLink->edges[text[letterCur]].size;
                    offset += nodeLink->edges[text[letterCur]].size;
                    nodeLink = nodeLink->edges[text[letterCur]].node;

                    if (size == 0)
                        cur.letter = -1;
                } else {
                    cur.letter = letterCur;
                    cur.offset = size - 1;
                    break;
                }
            }
        }

        cur.node = nodeLink;
        return true;
    }

    void addLetter(const int letter) {
        Node* nodePrev = nullptr;
        while (true) {
            if (nodePrev != nullptr)
                nodePrev->linkSuff = cur.node;

            // Если есть добавляемая буква - переходим по ней, останавливаемся
            const bool isMove = tryMove(letter);
            if (isMove) {
                break;
            }

            // Добавляемой буквы нет - добавляем
            Node* nodeNew = nullptr;
            bool isCreateNewInternal = false;
            if (!curIsInternal()) {
                nodeNew = split(cur.node, cur.letter, cur.offset, letter);
                isCreateNewInternal = true;
            }
            createLeaf((isCreateNewInternal ? nodeNew : cur.node), letter);

            // Присваиваем суффиксную ссылку на предыдущем шаге созданной внутренней вершине
            if (nodePrev != nullptr)
                nodePrev->linkSuff = (isCreateNewInternal ? nodeNew : cur.node);

            // Если приделывали лист к корню - останавливаемся
            if ( (isCreateNewInternal ? nodeNew : cur.node) == root )
                break;

            // Переходим по суффиксной ссылке
            passingSuffLink();

            nodePrev = nodeNew;
        }
    }
};

//int main() {
//    ios::sync_with_stdio(false);
//    cin.tie(0);
//
//    cout << "Введите паттерн: " << endl;
//    string pattern;
//    cin >> pattern;
//
//    SuffTree st(pattern);
//    st.Build();
//    st.Print();
//
//    auto suffix_array = st.BuildSuffixArray();
//
//    for (const auto& elem : suffix_array) {
//        cout << elem << ' ';
//    }
//    cout << endl;
//
////    const auto ms = st.BuildMS(text);
////    // for (int i = 0; i < ms.size(); ++i)
////    //     cout << ms[i] << " ";
////    // cout << endl;
////
////    for (int i = 0; i < ms.size(); ++i)
////        if (ms[i] == pattern.size())
////            cout << i + 1 << "\n";
//
//    return 0;
//}