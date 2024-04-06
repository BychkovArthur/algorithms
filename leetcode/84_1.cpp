class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        vector<int> cp = heights;
        cp.push_back(0);
        int res = 0;
        stack<int> st;

        for (int i = 0; i < cp.size(); ++i) {
            if (!st.empty() && cp[i] == cp[st.top()]) {
                continue;
            }

            if (st.empty() || cp[i] > cp[st.top()]) {
                st.push(i);
            } else {
                int to_push = 0;
                while (!st.empty() && cp[i] <= cp[st.top()]) {
                    int top_ind = st.top();
                    to_push = top_ind;
                    res = max(res, cp[top_ind] * (i - top_ind));
                    st.pop();
                }
                cp[to_push] = cp[i];
                st.push(to_push);
            }
        }

        return res;
        
    }
};