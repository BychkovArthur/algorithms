class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<array<int, 26>, vector<string>> mp;

        for (size_t i = 0; i < strs.size(); ++i) {
            array<int, 26> arr = {};
            for (size_t j = 0; j < strs[i].size(); ++j) {
                ++arr[strs[i][j] - 'a'];
            }
            mp[arr].push_back(move(strs[i]));
        }
        vector<vector<string>> res;

        for (auto& val : mp) {
            res.push_back(move(val.second));
        }
        return res;
    }
};