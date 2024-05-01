/*
    Решение за O(n * |A|) времени и O(|A|) памяти
*/

class Solution {
public:
    int characterReplacement(string s, int k) {
        array<int, 26> arr = {0};

        int l = 0, r = 0;
        int res = 0;

        while (r < s.size()) {
            
            int w = r - l + 1;
            int mx = 0;

            ++arr[s[r] - 'A'];
            for (int i = 0; i < 26; ++i) {
                mx = max(mx, arr[i]);
            }
            while (w - mx > k) {
                --arr[s[l++] - 'A'];
                --w;
                mx = 0;
                for (int i = 0; i < 26; ++i) {
                    mx = max(mx, arr[i]);
                }
            }
            res = max(res, w);
            ++r;
        }
        return res;
    }
};