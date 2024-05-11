class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int z = 0, nz = -1;
        int n = nums.size();
        while (z < n && nz < n) {
            while (z < n && nums[z]) ++z;
            if (nz == -1) nz = z;
            while (nz < n && !nums[nz]) ++nz;
            if (z < n && nz < n) {
                swap(nums[z], nums[nz]);
            }
        }
    }
};