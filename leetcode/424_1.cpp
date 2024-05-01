/*
    Это решение за O(|A| * n) времени и O(k) памяти.
*/

class Solution {
public:
    int characterReplacement(string s, int k) {
        int res = 1;

        for (int i = 0; i < 26; ++i) {
            char letter = 'A' + i;
            queue<int> q;

            int l = 0, r = 0;

            while (r < s.size()) {
                if (s[r] != letter) {
                    q.push(r);
                }

                if (q.size() > k) {
                    l = q.front() + 1;
                    q.pop();
                }
                res = max(res, r - l + 1);

                ++r;
            }
        }

        return res;
    }
};