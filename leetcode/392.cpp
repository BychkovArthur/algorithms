class Solution {
public:
    bool isSubsequence(string s, string t) {
        int sub_ptr = 0;
        int n = s.size();
        int m = t.size();

        for (int i = 0; i < m; ++i) {
            if (sub_ptr == n) return true;
            if (s[sub_ptr] == t[i]) ++sub_ptr;
        }

        if (sub_ptr == n) return true;

        return false;
    }
};