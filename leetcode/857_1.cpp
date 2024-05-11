class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        
        int n = quality.size();
        double res = 1e20;
        for (int i = 0; i < n; ++i) {
            vector<double> prices;
            for (int j = 0; j < n; ++j) {
                if (wage[i] * quality[j] >= wage[j] * quality[i] && j != i) {
                    prices.push_back((double)wage[i] / quality[i] * quality[j]);
                    // cout << "CURR = " << (double)wage[i] / quality[i] << " val = " << (double)wage[j] / quality[j] << endl;
                }
            }
            if (prices.size() >= k - 1) {
                sort(prices.begin(), prices.end());
                double price = wage[i];
                // cout << "INIT PRICE = " << price << endl;
                for (int ii = 0; ii < k - 1; ++ii) {
                    // cout << "ADD TO PRICE " << prices[ii] << endl;
                    price += prices[ii];
                }
                res = min(res, price);
            }
        }
        return res;
    }
};