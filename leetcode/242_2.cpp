/*

    В этом варианте я использую в два раза меньше памяти. А так же, он, возможно, немногим быстрее прошлого варианта.

*/


class Solution {
public:
    bool isAnagram(string s, string t) {
        unordered_map<char, int> mp;

        for (char& c : s) {
            if (mp.contains(c)) {
                ++mp[c];
            } else {
                mp[c] = 1;
            }
        }

        for (char& c : t) {
            if (!mp.contains(c)) {
                return false;
            }
            --mp[c];
            if (mp[c] < 0) {
                return false;
            }
        }

        for (auto& pr : mp) {
            if (pr.second != 0) {
                return false;
            }
        }
        return true;
    }
};