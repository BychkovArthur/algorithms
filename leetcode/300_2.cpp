class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        /* 
         * Greedy method, O(N*logN)
        **/

        vector<vector<int>> coverings;
        coverings.push_back({nums[0]});

        for (int i = 1; i < nums.size(); ++i) {
            auto el = nums[i];

            auto it = lower_bound(
                coverings.begin(),
                coverings.end(),
                el,
                [](const auto& lhs, int el) {
                    return lhs.back() < el;
                } 
            );

            if (it == coverings.end()) {
                coverings.push_back({el});
            } else {
                it->push_back(el);
            }
        }
        return coverings.size();
    }
};