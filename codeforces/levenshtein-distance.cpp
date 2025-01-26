/*
 * Задача: https://codeforces.com/problemset/problem/530/G
 *
**/

#include <bits/stdc++.h>
#include <ostream>
#include <vector>

using namespace std;
using ull = uint64_t;

ostream& operator<<(ostream& os, const vector<ull>& vct) {
    for (const auto& el : vct) {
        os << el << ' ';
    }
    return os;
}

ull GetLevenshteinDistance(const string& s1, const string& s2) {
    /*
     *
     *         from (s1) -> n
     *  t      . . . . . 
     *  o      . . . . .
     *  (s2)   . . . . .
     * 
     *  |
     *  V
     *  m
     * 
    **/
    ull n = s1.size();
    ull m = s2.size();

    vector<ull> previous_row(n + 1, 0);
    
    // Заполнение удаления 
    for (int i = 1; i <= n; ++i) {
        previous_row[i] = (s1[i - 1] - 'a' + 1) + previous_row[i - 1];
    }
    // cout << previous_row << endl;


    for (int i = 1; i <= m; ++i) {
        vector<ull> current_row(n + 1, 0);
        // Заполнение insert
        current_row[0] = (s2[i - 1] - 'a' + 1) + previous_row[0];

        for (int j = 1; j <= n; ++j) {
            if (s1[j - 1] == s2[i - 1]) {
                current_row[j] = previous_row[j - 1];
            } else {
                current_row[j] = min({
                    previous_row[j - 1] + abs(s1[j - 1] - s2[i - 1]), // replace
                    current_row[j - 1] + (s1[j - 1] - 'a' + 1), // delete 
                    previous_row[j] + (s2[i - 1] - 'a' + 1) // insert
                });
            }
        }
        // cout << current_row << endl;
        previous_row = current_row;
    }
    return previous_row.back();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s1, s2;
    cin >> s1 >> s2;
    cout << GetLevenshteinDistance(s1, s2);
}
