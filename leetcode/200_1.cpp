class Solution {
public:
    struct pair_hash {
        size_t operator()(const pair<int, int>& pr) const {
            auto h1 = hash<int>()(pr.first);
            auto h2 = hash<int>()(pr.second);
            if (h1 == h2) return h1;
            return h1 ^ h2;
        }
    };

    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int res = 0;
        // vector<vector<bool>> marked(m, vector<bool>(n, false));
        queue<pair<int, int>> q;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1') {
                    ++res;
                    q.push({i, j}); // Начало острова
                    grid[i][j] = '0';
                    while (!q.empty()) {
                        auto pr = q.front();
                        q.pop();
                        int ii = pr.first;
                        int jj = pr.second;
                        if (ii - 1 >= 0 && grid[ii - 1][jj] == '1') {
                            grid[ii - 1][jj] = '0';
                            q.push({ii - 1, jj});
                        }
                        if (jj - 1 >= 0 && grid[ii][jj - 1] == '1') {
                            grid[ii][jj - 1] = '0';
                            q.push({ii, jj - 1});
                        }
                        if (ii + 1 < m && grid[ii + 1][jj] == '1') {
                            grid[ii + 1][jj] = '0';
                            q.push({ii + 1, jj});
                        }
                        if (jj + 1 < n && grid[ii][jj + 1] == '1') {
                            grid[ii][jj + 1] = '0';
                            q.push({ii, jj + 1});
                        }
                    }
                }
            }
        }

        return res;
    }
};