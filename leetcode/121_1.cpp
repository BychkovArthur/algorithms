class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<int> maxs(n);

        maxs[n - 1] = prices[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            maxs[i] = max(maxs[i + 1], prices[i]);
        }
        int res = 0;
        for (int i = 0; i < n; ++i) {
            res = max(res, maxs[i] - prices[i]);
        }
        return res;
    }
};