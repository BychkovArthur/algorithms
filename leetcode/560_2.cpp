class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        int res = 0;
        int sum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            ++mp[sum];
        }
        
        sum = nums[0];
        res += mp[k];

        for (int i = 1; i < nums.size(); ++i) {
            --mp[sum];
            res += mp[k + sum];
            sum += nums[i];
        }
        return res;
    }
};