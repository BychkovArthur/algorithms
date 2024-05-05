/*
    Более красивое решение!!!! Через sliding window
*/

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int res = 0, l = 0, k = 1;
        for (int r = 0; r < nums.size(); ++r) {
            if (k > 0 && !nums[r]) --k;
            else if (k == 0 && !nums[r]) while (nums[l++]);
            res = max(res, r - l + 1);
        }
        return res - 1;
    }
};
