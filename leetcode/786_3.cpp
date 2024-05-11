/*
    Решение без вещественных переменных!!!
*/


class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        int n = arr.size();
        pair<uint64_t, uint64_t> l = {0, 1}, r = {1, 1}, m = {0, 0};
        vector<int> ans = {1, 1};

        while (true) {
            int less = 0;

            m.first = (l.first + r.first);
            m.second = l.second * 2;
            l.first *= 2;
            l.second *= 2;
            r.first *= 2;
            r.second *= 2;

            int ll = 0, rr = 1;
            while (rr < n) {
                if (arr[ll] * m.second < arr[rr] * m.first) {
                    less += n - rr;
                    ++ll;
                } else { // Я встретил что-то больше либо равное. Надо обновить ответ.
                    if (arr[ll] * ans[1] < arr[rr] * ans[0]) {
                        ans[0] = arr[ll];
                        ans[1] = arr[rr];
                    }
                    ++rr;
                }
            }
            if (less == k - 1) {
                break;
            } else if (less < k - 1) {
                l = m;
            } else if (less > k - 1) {
                r = m;
            }
            ans[0] = 1;
            ans[1] = 1;
        }
        return ans;
    }
};