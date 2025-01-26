class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        /* 
         * Greedy method, O(N^2)
        **/

        vector<vector<int>> coverings;
        coverings.push_back({nums[0]});

        for (int i = 1; i < nums.size(); ++i) {
            auto el = nums[i];

            bool coverage_find = false;
            for (auto& coverage : coverings) {
                if (el <= coverage.back()) {
                    coverage.push_back(el); 
                    coverage_find = true;
                    break;
                }
            }
            if (!coverage_find) {
                coverings.push_back({el});
            }
        }
        return coverings.size();
    }
};