class Solution {
public:

    static bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
        return a.first > b.first;
    }

    vector<string> findRelativeRanks(vector<int>& score) {
        int n = score.size();
        vector<pair<int, int>> sorted_score;
        vector<string> answer(n);
        for (int i = 0; i < n; ++i) {
            sorted_score.push_back({score[i], i});
        }
        sort(sorted_score.begin(), sorted_score.end(), cmp);
        for (int i = 0; i < n; ++i) {
            if (i == 0) {
                answer[sorted_score[i].second] = move(string("Gold Medal"));
            } else if (i == 1) {
                answer[sorted_score[i].second] = move(string("Silver Medal"));
            } else if (i == 2) {
                answer[sorted_score[i].second] = move(string("Bronze Medal"));
            } else {
                answer[sorted_score[i].second] = move(to_string(i + 1));
            }
        }
        return answer;
    }
};