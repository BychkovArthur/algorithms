class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        sort(piles.begin(), piles.end());
        // int mx = *max(piles.begin(), piles.end()); // Какого-то фига с этой штукой санитайзер ругается.
        int mx = 0;
        for (int i = 0; i < piles.size(); ++i) {
            mx = max(mx, piles[i]);
        }
        int l = 0;
        int r = mx;

        while (l < r - 1) {
            int m = (l + r) / 2;
            long long int hours = 0;
            for (int i = 0; i < piles.size(); ++i) {
                hours += piles[i] / m + (piles[i] % m ? 1 : 0);
            }

            if (hours > h) {
                l = m;
            } else {
                r = m;
            }
        }

        return r;
    }
};