class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int res = 0;

        int l = 0;
        for (int i = 0; i < n; ++i) {
            char c = s[i];

            for (int j = l; j < i; ++j) {
                if (s[j] == c) {
                    l = j + 1;
                    break;
                }
            }

            res = max(res, i - l + 1);
        }

        return res;
    }
};