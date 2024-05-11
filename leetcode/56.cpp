class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> res;
        int n = intervals.size();
        int last_ind = 0;
        res.emplace_back(std::initializer_list<int>{intervals[0][0], intervals[0][1]});

        for (int i = 1; i < n; ++i) {
            int& right = res[last_ind][1];
            int new_left = intervals[i][0];
            int new_right = intervals[i][1];

            if (new_left <= right) {
                right = max(right, new_right);
            } else {
                res.emplace_back(std::initializer_list<int>{new_left, new_right});
                ++last_ind;
            }
        }
        return res;
    }
};