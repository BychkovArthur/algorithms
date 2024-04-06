class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int res = 0;
        stack<int> st;

        for (int i = 0; i <= heights.size(); ++i) {
            int height = (i == heights.size()) ? 0 : heights[i];

            if (st.empty() || height >= heights[st.top()]) {
                st.push(i);
            } else {
                
                while (!st.empty() && height <= heights[st.top()]) {
                    int h = heights[st.top()];
                    st.pop();                                         // Получается, что суть такого решения, что мы используем индесы из стека только для того, чтобы узнать значение. А длину находим, обратившись к элементу, меньшему предыдущего.
                                                                      // Однако, из-за этого получается, что придётся хранить все дупликаты.
                    int w = st.empty() ? i : i - st.top() - 1;
                    res = max(res, h * w);
                }
                st.push(i);
            }
        }

        return res;
        
    }
};