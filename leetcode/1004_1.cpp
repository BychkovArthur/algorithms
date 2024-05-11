/*
    Очень красивый код для slidind window
*/

class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int res = 0;
        int l = 0;
        for (int r = 0; r < nums.size(); ++r) {
            if (k > 0 && !nums[r]) --k;
            else if (k == 0 && !nums[r]) while (nums[l++]);
            res = max(res, r - l +  1);
        }
        return res;
    }
};