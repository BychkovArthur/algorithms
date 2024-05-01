/*
    Решение за O(|A| * n) по времени и O(1) по памяти
*/

class Solution {
public:
    int characterReplacement(string s, int k) {
        int res = 0;
        int n = s.size();
        for (char letter = 'A'; letter <= 'Z'; ++letter) {
            int l = 0, r = 0;
            int cnt = 0;

            while (r < n) {
                if (s[r] != letter) {
                    while (cnt == k) {
                        if (s[l++] != letter) {
                            --cnt;
                        }
                    }
                    ++cnt;
                }
                ++r;
                res = max(res, r - l);
            }

        }
        return res;

    }
};