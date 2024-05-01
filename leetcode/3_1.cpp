class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        array<bool, 256> visited = {false};

        int l = 0, r = 0;
        int res = 0;

        while (r < n) {
            while (visited[s[r]]) {
                visited[s[l++]] = false;
            }
            visited[s[r++]] = true;
            res = max(res, r - l);
        }
        return res;
    }
};