class Solution {
public:
    int compress(vector<char>& chars) {
        int cnt = 1;
        int index = 0;
        int n = chars.size();
        for (int i = 1; i <= n; ++i) {
            bool is_sequence = (i < n) ? chars[i] == chars[i - 1] : false;
            if (is_sequence) {
                ++cnt;
            } else {
                chars[index++] = chars[i - 1];
                if (cnt > 1) {
                    string s = to_string(cnt);
                    for (char c : s) {
                        chars[index++] = c;
                    }
                }
                cnt = 1;
            }
        }
        return index;
    }
};