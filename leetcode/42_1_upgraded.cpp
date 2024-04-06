class Solution {
public:
    int trap(vector<int>& height) {
        int max_height_ind = max_element(height.begin(), height.end()) - height.begin();
        int l = 0;
        int r = 1;
        int to_subtract = 0;
        int res = 0;

        for (; r <= max_height_ind; ++r) {
            if (height[r] >= height[l]) {
                res += height[l] * (r - l - 1) - to_subtract;
                to_subtract = 0;
                l = r;
            } else {
                to_subtract += height[r];
            }
        }
        
        r = height.size() - 1;
        l = r - 1;

        for (; l >= max_height_ind; --l) {
            if (height[l] >= height[r]) {
                res += height[r] * (r - l - 1) - to_subtract;
                to_subtract = 0;
                r = l;
            } else {
                to_subtract += height[l];
            }
        }
        
        return res;
    }
};