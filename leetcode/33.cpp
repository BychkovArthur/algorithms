class Solution {
public:
    int search(vector<int>& nums, int target) {

        int shift = 0;
        int n = nums.size();

        if (n == 1) {
            return nums[0] == target ? 0 : -1;
        }

        if (nums[0] >= nums[n - 1]) {
            int l = 0;
            int r = n - 1;

            while (l < r - 1) {
                int m = (l + r) / 2;

                if (nums[m] < nums[n - 1]) {
                    r = m;
                } else {
                    l = m;
                }
            }
            shift = r;
        }

        int l = 0;
        int r = n - 1;

        if (nums[(l + shift) % n] > target || nums[(r + shift) % n] < target) {
            return -1;
        }

        while (l < r - 1) {
            int m = (l + r) / 2;

            if (nums[(m + shift) % n] < target) {
                l = m;
            } else {
                r = m;
            }
        }

        if (nums[(r + shift) % n] == target) {
            return (r + shift) % n;
        } else if (nums[(l + shift) % n] == target) {
            return (l + shift) % n;
        }
        return -1;
    }
};