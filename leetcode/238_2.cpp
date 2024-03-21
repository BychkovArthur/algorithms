/*
    Solution O(1) space complexity
*/

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, 1);


        int curr_product = 1;
        for (ssize_t i = 1; i < n; ++i) {
            curr_product *= nums[i - 1];
            res[i] *= curr_product;
        }

        curr_product = 1;
        for (ssize_t i = n - 2; i >= 0; --i) {
            curr_product *= nums[i + 1];
            res[i] *= curr_product;
        }

        return res;
    }
};