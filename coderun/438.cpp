#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    const int n = 3;
    vector<string> strings(n);
    cin >> strings[0] >> strings[1] >> strings[2];

    vector<vector<char>> chars(n);
    vector<vector<int>> count(n);

    for (int i = 0; i < n; ++i) {
        int cnt = 0;
        for (int j = 0; j < strings[i].size(); ++j) {



            if (j == 0 || strings[i][j] != strings[i][j - 1]) {
                chars[i].push_back(strings[i][j]);
            }

            if (j > 0 && strings[i][j] != strings[i][j - 1]) {
//                std::cout << "I = " << i << " J = " << j << std::endl;
                if (count[i].empty()) {
                    count[i].push_back(j);
                    cnt += j;
                }
                else {
                    count[i].push_back(j - cnt);
                    cnt += j - cnt;
                }
            }
        }
        count[i].push_back(strings[i].size() - cnt);
    }

    if (chars[0] != chars[1] || chars[1] != chars[2]) {
        std::cout << "IMPOSSIBLE" << std::endl;
        return 0;
    }

    vector<int> res_cnt;

    for (int i = 0; i < count[0].size(); ++i) {
        int a = count[0][i], b = count[1][i], c = count[2][i];
        res_cnt.push_back(a + b + c - max({a, b, c}) - min({a, b, c}));
    }

    for (int i = 0; i < res_cnt.size(); ++i) {
        std::cout << std::string(res_cnt[i], chars[0][i]);
    }

    return 0;
}