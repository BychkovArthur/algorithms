class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        ssize_t l = 0;
        ssize_t r = numbers.size() - 1;

        while (l < r) {
            if (numbers[l] + numbers[r] < target) {
                ++l;
            } else if (numbers[l] + numbers[r] > target) {
                --r;
            } else {
                return {static_cast<int>(l) + 1, static_cast<int>(r) + 1};
            }
        }
        return {};
    }
};