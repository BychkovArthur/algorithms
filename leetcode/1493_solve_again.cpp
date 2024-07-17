class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int k = 1;
        int mx = 0;
        int n = nums.size(), l = 0;

        for (int r = 0; r < n; ++r) {
            if (!nums[r]) {
                --k;
            }
            if (k < 0) {
                while(nums[l]) ++l;
                ++l;
                ++k;
            }
            mx = max(mx, r - l + 1);
        }

        return mx - 1;

    }
};