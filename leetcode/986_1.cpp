/*
    TIME: O(nlogn)
    SPACE: O(n)
*/

class Solution {
public:

    static bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
        return a.first == b.first ? a.second > b.second : a.first < b.first;
    }

    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        vector<vector<int>> ans;

        vector<pair<int, int>> times;
        for (int i = 0; i < firstList.size(); ++i) {
            times.push_back({firstList[i][0], 1});
            times.push_back({firstList[i][1], -1});
        }
        for (int i = 0; i < secondList.size(); ++i) {
            times.push_back({secondList[i][0], 1});
            times.push_back({secondList[i][1], -1});
        }
        sort(times.begin(), times.end(), cmp);

        // for (auto& pr : times) {
        //     cout << pr.first << ' ' << pr.second << endl;
        // }

        int cnt = 0;
        int start = 0;
        for (auto& pr : times) {
            cnt += pr.second;
            if (pr.second == 1 && cnt == 2) {
                start = pr.first;
            }
            if (pr.second == -1 && cnt == 1) {
                ans.push_back({start, pr.first});
            }
            
        }

        return ans;
    }
};