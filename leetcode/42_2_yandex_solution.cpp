class Solution {
public:
    int trap(vector<int>& height) {
        int max_height_ind = max_element(height.begin(), height.end()) - height.begin();
        int res = 0;

        int prev_max = 0;

        for (int i = 0; i < max_height_ind; ++i) {
            if (height[i] > prev_max) {
                prev_max = height[i];
            } else {
                res += prev_max - height[i];
            }
        }
        prev_max = 0;
        for (int i = height.size() - 1; i > max_height_ind; --i) {
            if (height[i] > prev_max) {
                prev_max = height[i];
            } else {
                res += prev_max - height[i];
            }
        }
                
        return res;
    }
};