class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> answer;
        size_t n = nums.size();
        set<pair<int, pair<int, int>>> st;

        for (size_t i = 0; i < n; ++i) {
            for (size_t j = i + 1; j < n; ++j) {
                for (size_t k = j + 1; k < n; ++k) {
                    if (nums[i] + nums[j] + nums[k] == 0) {
                        ssize_t mn = min(nums[i], min(nums[j], nums[k]));
                        ssize_t mx = max(nums[i], max(nums[j], nums[k]));
                        ssize_t md = nums[i] + nums[j] + nums[k] - mn - mx;
                        pair<int, pair<int, int>> pr;
                        pr.first = mn;
                        pr.second.first = md;
                        pr.second.second = mx;
                        st.insert(pr);
                    }
                }
            }
        }
        for (auto& pr : st) {
            answer.push_back({pr.first, pr.second.first, pr.second.second});
        }

        return answer;
    }
};