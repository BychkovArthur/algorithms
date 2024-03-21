class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> mp;

        for (const auto& nm : nums) {
            ++mp[nm];
        }

        vector<vector<int>> elems_by_frequence(nums.size() + 1);

        for (const auto& pr : mp) {
            elems_by_frequence[pr.second].push_back(pr.first);
        }

        vector<int> ans;

        for (ssize_t i = nums.size(); i >= 0 && k; --i) {
            // ans.insert(ans.end(), elems_by_frequence[i].begin(), elems_by_frequence[i].end());
            for (const auto& el : elems_by_frequence[i]) {
                ans.push_back(el);
                --k;
                if (!k) {
                    break;
                }
            }
            
        }

        return ans;
    }
};