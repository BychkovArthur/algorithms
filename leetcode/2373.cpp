class Solution {
public:
    vector<vector<int>> largestLocal(vector<vector<int>>& grid) {
        int n = grid.size() - 2;
        vector<vector<int>> result(n, vector<int>(n));

        array<int, 9> move_x = {1, 1, 1, -1, -1, -1, 0, 0, 0};
        array<int, 9> move_y = {1, 0, -1, 1, 0, -1, 1, 0, -1};

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int mx = 0;
                for (int k = 0; k < 9; ++k) {
                    mx = max(mx, grid[i + 1 + move_x[k]][j + 1 + move_y[k]]);
                }
                result[i][j] = mx;
            }
        }

        return result;
    }
};