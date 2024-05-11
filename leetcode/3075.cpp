class Solution {
public:
    long long maximumHappinessSum(vector<int>& happiness, int k) {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cout.tie(0);
        sort(happiness.begin(), happiness.end(), greater<int>());
        long long res = 0;

        for (int i = 0; i < k; ++i) {
            res += max(0, happiness[i] - i);
        }

        return res;
    }
};