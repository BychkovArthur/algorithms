class Solution {
public:
    vector<int> partitionLabels(string s) {
        vector<int> ans;
        unordered_map<char, int> mp;

        for (int i = 0; i < s.size(); ++i) mp[s[i]] = i;


        int last_ind = -1;
        int first_ind = 0;
        for (int i = 0; i < s.size(); ++i) {
            last_ind = max(last_ind, mp[s[i]]);

            if (i == last_ind) {
                ans.push_back(i - first_ind + 1);
                first_ind = i + 1;
            }
        }
        return ans;
    }
};