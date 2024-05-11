class Solution {
public:
    string longestPalindrome(string s) {
        int start = 0;
        int max_len = 1;
        int n = s.size();

        for (int i = 0; i < n; ++i) {
            // 1 not even
            int l = i - 1;
            int r = i + 1;
            int curr_len = 1;
            while (l >= 0 && r < n && s[l] == s[r]) {
                --l;
                ++r;
                curr_len += 2;
            }
            if (curr_len > max_len) {
                max_len = curr_len;
                start = l + 1;
            }
            // 2 even
            l = i;
            r = i + 1;
            curr_len = 0;
            while (l >= 0 && r < n && s[l] == s[r]) {
                --l;
                ++r;
                curr_len += 2;
            }
            if (curr_len > max_len) {
                max_len = curr_len;
                start = l + 1;
            }
        }
        return s.substr(start, max_len);
    }
};