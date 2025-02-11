class Solution {
public:
    int numTrees(int n) {
        vector<int> count(n + 1, 0);
        count[0] = 1;
        count[1] = 1;

        for (int nodes_count = 2; nodes_count <= n; ++nodes_count) {

            for (int left_subtree = 0; left_subtree <= nodes_count - 1; ++left_subtree) {
                auto right_subtree = nodes_count - 1 - left_subtree;
                count[nodes_count] += count[left_subtree] * count[right_subtree];
            }

        }
        return count[n];
    }
};