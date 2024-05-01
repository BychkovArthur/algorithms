/*
    Решение за O(n) времени и O(|A|) памяти
*/


class Solution {
public:
    int characterReplacement(string s, int k) {
        array<int, 26> arr = {0};

        int l = 0, r = 0;
        int res = 0;
        int mx = 0;

        while (r < s.size()) {
            
            int w = r - l + 1;

            ++arr[s[r] - 'A'];
            if (mx == arr[s[r] - 'A'] - 1) {
                ++mx;
            }

            while (w - mx > k) {
                --arr[s[l++] - 'A'];
                --w;
            }
            res = max(res, w);
            ++r;
        }
        return res;
    }
};