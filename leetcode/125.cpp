class Solution {
public:

    bool isPalindrome(string s) {
        ssize_t l = 0;
        ssize_t r = s.size() - 1;

        while (l < r) {

            while (l < s.size() && !isalnum(s[l])) {
                ++l;
            }

            while (r >= 0 && !isalnum(s[r])) {
                --r;
            }

            if (l < r && tolower(s[l]) != tolower(s[r])) {
                return false;
            }
            --r;
            ++l;
        }

        return true;
    }
};