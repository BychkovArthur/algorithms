class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> cp = nums;
        int l = 0, r = static_cast<int>(nums.size() - 1);

        sort(cp.begin(), cp.end());

        while (true) {
            if (cp[l] + cp[r] > target) {
                --r;
            } else if (cp[l] + cp[r] < target) {
                ++l;
            } else {
                vector<int> res(2);
                res[0] = find(nums.begin(), nums.end(), cp[l]) - nums.begin();
                for (size_t i = 0; i < nums.size(); ++i) {
                    if (nums[i] == cp[r] && i != res[0]) {
                        res[1] = i;
                        break;
                    }
                }
                return res;
            }
        }
    }
};