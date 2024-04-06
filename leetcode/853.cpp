class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        int res = 1;

        vector<pair<int, int>> vct(n);
        for (int i = 0; i < n; ++i) {
            vct[i] = {position[i], speed[i]};
        }
        sort(vct.begin(), vct.end());

        long long int leader_left = target - vct[n - 1].first;
        long long int leader_speed = vct[n - 1].second;

        for (int i = n - 2; i >= 0; --i) {
            long long int curr_left = target - vct[i].first;
            long long int curr_speed = vct[i].second;

            if (curr_left * leader_speed > leader_left * curr_speed) {
                ++res;
                leader_left = target - vct[i].first;
                leader_speed = vct[i].second;
            }
        }
        return res;
    }
};