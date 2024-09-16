#include <bits/stdc++.h>
#include <cstddef>
#include <string>
#include <sys/types.h>
#include <tuple>
#include <unordered_map>
#include <vector>

using namespace std;


class Ukkonen {
public:
    using size_type = std::size_t;
    using ssize_type = ssize_t;

private:

    struct Node {
        unordered_map<char, std::tuple<size_type, size_type, Node*>> mp;
        ssize_type num;

        Node() : num(-1) {}
        Node(ssize_type num) : num(num) {}
    };

    const std::string& text;
    Node* root;

    void build_suff_tree() {
        size_type n = text.size();
        size_type leafNumber = 0;

        Node* currNode = root;
        char currNodeChar = 0;
        size_type currPosInNode = -1;

        for (ssize_type i = 0; i < text.size(); ++i) {
            char c = text[i];


            if (currNode == root) {
                if (currPosInNode == -1) {
                    if (currNode->mp.count(c)) {
                        currNodeChar = c;
                        currPosInNode = 0;
                    } else {
                        currNode->mp[c] = std::make_tuple(i, n - 1, new Node(leafNumber++));
                    }

                } else {
                    auto& [l, r, next] = currNode->mp[c];
                    
                    if (currPosInNode == r - l) {
                        currNode = next;
                        currNodeChar = 0;
                        currPosInNode = -1;
                        --i;
                        continue;

                    } else if (currPosInNode < r - l && c == text[l + currPosInNode + 1]) {
                        ++currPosInNode;
                    } else if (currPosInNode < r - l && c != text[l + currPosInNode + 1]) {
                        // split ребра
                        // [3, 5], currPos = 1 => не совпадение в 5
                        auto oldr = r;
                        r = l + currPosInNode;
                        
                        next->mp[c] = std::make_tuple(i, n - 1, new Node(leafNumber++));
                        next->mp[text[r + 1]] = std::make_tuple(r + 1, oldr, new Node(currNode->num));
                        currNode->num = -1;

                        // переход по суфф ссылкам с добавлением новых
                    }

                }
            }

        }
    }



public:
    

    Ukkonen(const std::string& text) : text(text), root(new Node) {
        build_suff_tree();
    }

    bool contains(const std::string& pattern);
    size_type count(const std::string& pattern);
    std::vector<size_type> occurrences(const std::string& pattern);
};


int main() {
    auto tp = make_tuple(1, 2, 3);

    auto& [x, y, z] = tp;
    x = 15;

    cout << get<0>(tp) << endl;;
}
