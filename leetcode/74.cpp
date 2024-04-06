class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        int l = 0;
        int r = m * n - 1;

        if (matrix[l][l] > target || matrix[r / n][r % n] < target) {
            return false;
        }

        while (l < r - 1) {
            int mid = (l + r) / 2;

            int i = mid / n;
            int j = mid % n;

            if (matrix[i][j] < target) {
                l = mid;
            } else {
                r = mid;
            }
        }

        return matrix[l / n][l % n] == target || matrix[r / n][r % n] == target;       
    }
};