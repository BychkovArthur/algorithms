class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefixes(n);
        vector<int> suffixes(n);
        vector<int> res(n);

        prefixes[0] = nums[0];
        suffixes[n - 1] = nums[n - 1];
        for (int i = 1; i < n; ++i) {
            prefixes[i] = nums[i] * prefixes[i - 1];
        }
        for (int i = n - 2; i >= 0; --i) {
            suffixes[i] = nums[i] * suffixes[i + 1];
        }

        res[0] = suffixes[1];
        res[n - 1] = prefixes[n - 2];
        for (int i = 1; i < n - 1; ++i) {
            res[i] = prefixes[i - 1] * suffixes[i + 1];
        }

        return res;
    }
};