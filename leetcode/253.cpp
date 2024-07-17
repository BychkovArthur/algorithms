/**
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        vector<pair<int, int>> vct;

        for (const auto& pr : intervals) {
            vct.push_back({pr.start, +1});
            vct.push_back({pr.end, -1});
        }

        sort(vct.begin(), vct.end());
        int cnt = 0;
        int mx = 0;

        for (const auto& pr : vct) {
            cnt += pr.second;
            mx = max(mx, cnt);
        }
        return mx;
    }
};
