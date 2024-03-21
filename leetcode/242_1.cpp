class Solution {
public:

    void count_chars(unordered_map<char, int>& mp, string& str) {
        for (char c : str) {
            if (mp.contains(c)) {
                ++mp[c];
            } else {
                mp[c] = 1;
            }
        }
    }

    bool isAnagram(string s, string t) {
        unordered_map<char, int> mp1;
        unordered_map<char, int> mp2;

        count_chars(mp1, s);
        count_chars(mp2, t);
        return mp1 == mp2;
    }
};