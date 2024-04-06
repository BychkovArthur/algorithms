class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int l = 0;
        int r = n - 1;

        if (nums[0] > target || nums[n - 1] < target) {
            return -1;
        }
        while (l < r - 1) {
            int mid = (l + r) / 2;
            if (nums[mid] < target) {
                l = mid;
            } else {
                r = mid;
            }
        }
        if (nums[l] == target) {
            return l;
        } else if (nums[r] == target) {
            return r;
        }
        return -1;
    }
};