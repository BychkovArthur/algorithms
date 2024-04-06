class Solution {
public:
    int search(vector<int>& nums, int target) {
        auto res = lower_bound(nums.begin(), nums.end(), target);
        return res != nums.end() && *res == target ? res - nums.begin() : -1;
    }
};