#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

int main()
{
    vector<string> strings;
    string s;
    getline(cin, s);
    stringstream ss(s);
    while (ss >> s) {
        strings.push_back(s);
    }

    map<string_view, int> mp;
    for (const auto& s : strings) {
        string_view sv = s;
        for (int i = 1; i < s.size(); ++i) {
            ++mp[sv.substr(i - 1, 2)];
        }
    }

    int max_cnt = 0;
    string_view max_val;
    for (const auto & [k, v] : mp) {
        max_cnt = max(max_cnt, v);
    }

    for (const auto & [k, v] : mp) {
        if (v == max_cnt) max_val = max(max_val, k);
    }

    cout << max_val;
    return 0;
}