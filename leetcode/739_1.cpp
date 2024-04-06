class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        size_t n = temperatures.size();
        vector<int> ans(n, 0);
        stack<pair<int, int>> st;

        for (int i = 0; i < n; ++i) {
            if (st.empty() || st.top().first >= temperatures[i]) {
                st.push({temperatures[i], i});
            } else {
                while (!st.empty() && st.top().first < temperatures[i]) {
                    ans[st.top().second] = i - st.top().second;
                    st.pop();
                }
                st.push({temperatures[i], i});
            }
        }
        return ans;
    }
};