class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> ans;
        if (!nums.size()) {
            return ans;
        }
        int start = 0;
        int n = nums.size();
        for (int i = 1; i <= n; ++i) {
            int num = i < n ? nums[i] : nums[i - 1];

            if (num - 1 != nums[i - 1]) {
                if (start == i - 1) {
                    ans.push_back(to_string(nums[start]));
                } else {
                    string n1 = to_string(nums[start]);
                    string n2 = to_string(nums[i - 1]);
                    ans.push_back(n1 + "->" + n2);
                }
                start = i;
            }
        }
        return ans;
    }
};