class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int l = 0, r = 0;
        for (; r < nums.size(); ++r) {
            if (!nums[r]) k--;
            if (k < 0 && !nums[l++]) k++;
        }
        return r - l;
    }
};