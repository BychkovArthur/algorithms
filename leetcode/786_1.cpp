class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        vector<pair<double, pair<int, int>>> vct;
        for (int i = 0; i < arr.size(); ++i) {
            for (int j = i + 1; j < arr.size(); ++j) {
                vct.push_back({(double)arr[i] / arr[j], {arr[i], arr[j]}});
            }
        }
        sort(vct.begin(), vct.end());
        vector<int> ans(2);
        ans[0] = vct[k - 1].second.first;
        ans[1] = vct[k - 1].second.second;
        return ans;
    }
};