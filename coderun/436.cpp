#include <bits/stdc++.h>

using namespace std;


int main() {
    int n, i = 0;
    cin >> n;
    vector<pair<int, int>> a(n);
    priority_queue<int> pq;

    for (int i = 0; i < n; ++i) {
        pair<int, int> pr;
        cin >> pr.first >> pr.second;
        a[i] = pr;
    }

    sort(a.begin(), a.end(), greater<pair<int, int>>());

    i = 0;
    for (int day = a[0].first; day >= 1; --day) {
        for (; i < a.size() && a[i].first == day; ++i) {
            pq.push(a[i].second);
        }
        if (!pq.empty()) pq.pop();
    }

    long long int res = 0;
    while (!pq.empty()) {
        res += pq.top();
        pq.pop();
    }
    std::cout << res << std::endl;
}

