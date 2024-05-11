class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> ans;
        array<int, 26> a1 = {};
        array<int, 26> a2 = {};
        int s_len = s.size();
        int p_len = p.size();
        int matches = 0;
        if (p_len > s_len) return ans;

        for (int i = 0; i < p_len; ++i) {
            ++a1[s[i] - 'a'];
            ++a2[p[i] - 'a'];
        }
        for (int i = 0; i < 26; ++i) matches += (a1[i] == a2[i]);

        for (int i = p_len; i <= s_len; ++i) {
            if (matches == 26) {
                ans.push_back(i - p_len);
            }
            if (i < s_len) {
                ++a1[s[i] - 'a'];
                if (a1[s[i] - 'a'] == a2[s[i] - 'a']) ++matches;
                if (a1[s[i] - 'a'] == a2[s[i] - 'a'] + 1) --matches;
                --a1[s[i - p_len] - 'a'];
                if (a1[s[i - p_len] - 'a'] == a2[s[i - p_len] - 'a']) ++matches;
                if (a1[s[i - p_len] - 'a'] == a2[s[i - p_len] - 'a'] - 1) --matches;
            }
        }
        return ans;
    }
};