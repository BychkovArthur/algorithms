class Solution {
public:
    int maxDistToClosest(vector<int>& seats) {
        int res = 0;
        int cnt = 0;

        for (int i = 0; i <= seats.size(); ++i) {

            if (i < seats.size() && !seats[i]) {
                ++cnt;
            } else {
                if (cnt == i || i == seats.size()) { // Нули в начале или конце.
                    res = max(res, cnt);
                } else { // Не начало и не конец.
                    res = max(res, (cnt + 1) / 2);
                }
                cnt = 0;
            }
        }
        return res;
    }
};