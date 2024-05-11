class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        int n = arr.size();
        long double l = 0.0, r = 1.0, mid = 0.0;
        vector<int> ans = {1, 1};

        while (true) {
            int less = 0;
            mid = (l + r) / 2;
            int ll = 0, rr = 1;
            while (rr < n) {
                if (arr[ll] < mid * arr[rr]) {
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
                l = mid;
            } else if (less > k - 1) {
                r = mid;
            }
            ans[0] = 1;
            ans[1] = 1;
        }
        return ans;
    }
};