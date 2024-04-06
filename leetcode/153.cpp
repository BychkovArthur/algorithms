class Solution {
public:
    int findMin(vector<int>& nums) {
        
        int n = nums.size();

        if (n == 1 || nums[0] < nums[n - 1]) {
            return nums[0];
        }

        int l = 0;
        int r = n - 1;

        while (l < r - 1) {
            int m = (l + r) / 2;

            if (nums[m] > nums[n - 1]) {
                l = m;
            } else {
                r = m;
            }
        }

        return nums[r];
    }
};