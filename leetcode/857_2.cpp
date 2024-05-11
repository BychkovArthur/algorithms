class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        int n = quality.size();
        vector<pair<double, int>> vct(n);
        priority_queue<int> pq;
        for (int i = 0; i < n; ++i) {
            vct[i] = {(double)wage[i] / quality[i], quality[i]};
        }
        sort(vct.begin(), vct.end());
        int sum = 0;
        double res = 0;
        for (int i = 0; i < k; ++i) {
            pq.push(vct[i].second);
            sum += vct[i].second;
        }
        res = sum * vct[k - 1].first;
        // Есть смысл пихать новое только в том случае, если качество СТРОГО меньше максимального.
        // В этом случае, я уменьшу сумму, а максимум или останется или увеличится.

        // Если же новое quality больше либо равно максимума, то сумма или увеличится или не изменится, 
        // и так же с максимумом, он увеличится или не изменится. Поэтому, нет смысла пихать это в очередь.

        for (int i = k; i < n; ++i) {
            if (vct[i].second < pq.top()) {
                sum += vct[i].second - pq.top();
                pq.pop();
                pq.push(vct[i].second);
                res = min(res, sum * vct[i].first);
            }
        }
        return res;
    }
};