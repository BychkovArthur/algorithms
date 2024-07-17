class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int mx = 0;
        int l = 0;
        for (int r = 0; r < nums.size(); ++r) {
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
        return mx;
    }
};