/*
    TIME: O(n)
    SPACE: O(1)
*/

class Solution {
public:

    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        vector<vector<int>> ans;

        int fst = 0;
        int scnd = 0;

        while (fst < firstList.size() && scnd < secondList.size()) {
            vector<int>& seq1 = firstList[fst];
            vector<int>& seq2 = secondList[scnd];
            if (seq1[1] < seq2[1]) {
                if (seq1[1] >= seq2[0]) {
                    ans.push_back({max(seq1[0], seq2[0]), seq1[1]});
                }
                ++fst;
            } else if (seq1[1] > seq2[1]) {
                if (seq2[1] >= seq1[0]) {
                    ans.push_back({max(seq1[0], seq2[0]), seq2[1]});
                }
                ++scnd;
            } else {
                ans.push_back({max(seq1[0], seq2[0]), seq1[1]});
                ++fst;
                ++scnd;
            }
        }

        return ans;
    }
};