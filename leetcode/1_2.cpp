/*
    Решение через unordered_map 
*/


class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mp;

        for (size_t i = 0; i < nums.size(); ++i) {
            if (mp.contains(target - nums[i])) {
                return {static_cast<int>(i), mp[target - nums[i]]};
            }
            mp[nums[i]] = i;
        }
        return {1, 1};
    }
};