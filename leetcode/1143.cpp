class Solution {
public:
    int longestCommonSubsequence(const string& text1, const string& text2) {
        int n = text1.size();
        int m = text2.size();

        vector<int> previous_row(n + 1, 0);
        vector<int> current_row(n + 1, 0);
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                
                if (text1[j - 1] == text2[i - 1]) {
                    current_row[j] = previous_row[j - 1] + 1;
                } else {
                    current_row[j] = max(current_row[j - 1], previous_row[j]);
                }

            }
            previous_row = current_row;
        }
        return previous_row.back();
    }
};