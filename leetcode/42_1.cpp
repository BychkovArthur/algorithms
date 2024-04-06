class Solution {
public:
    int trap(vector<int>& height) {
        if (height.size() == 1 || height.size() == 2) {
            return 0;
        }

        int max_height_ind = max_element(height.begin(), height.end()) - height.begin();

        int l = 0;
        int r = 1;
        int to_subtract = 0;
        int res = 0;
        while (r <= max_height_ind) {
            if (height[r] >= height[l]) {
                res += min(height[l], height[r]) * ((r - l) - 1) - to_subtract;
                to_subtract = 0;
                ++r;
                l = r - 1;
            } else {
                to_subtract += height[r++];
            }
        }
        r = height.size() - 1;
        l = r - 1;

        while (l >= max_height_ind) {
            if (height[l] >= height[r]) {
                res += min(height[l], height[r]) * ((r - l) - 1) - to_subtract;
                to_subtract = 0;
                --l;
                r = l + 1;
            } else {
                to_subtract += height[l--];
            }
        }

        cout << res << endl;

        return res;
    }
};