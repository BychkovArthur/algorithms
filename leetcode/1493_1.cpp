class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int prev_len = 0;
        int curr_len = 0;
        bool zero_exists = false;
        int res = 0;

        for (int i = 0; i <= nums.size(); ++i) {
            int num = i < nums.size() ? nums[i] : 0;

            if (i < nums.size() && !num) {
                zero_exists = true;
            }

            if (num) {
                ++curr_len;
            } else {
                res = max(res, curr_len);
                if (prev_len && nums[i - curr_len - 2]) {
                    res = max(res, curr_len + prev_len);
                }
                prev_len = curr_len;
                curr_len = 0;
            }
        }

        return zero_exists ? res : res - 1;
    }
};