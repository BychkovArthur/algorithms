#include <bits/stdc++.h>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
    size_t u;
    size_t v;
    size_t w;
};

using pr = pair<size_t, size_t>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, s;
    cin >> n >> m >> s;

    priority_queue<pr, vector<pr>, greater<pr>> pq;
    vector<vector<Edge>> edges(n + 1);
    vector<size_t> d(n + 1, UINT64_MAX);
    for (int _ = 0; _ < m; ++_) {
        size_t u, v, w;
        cin >> u >> v >> w;
        edges[u].push_back({.u = u, .v = v, .w = w});
        edges[v].push_back({.u = v, .v = u, .w = w});
    }

    pq.push({0, s});
    d[s] = 0;

    while (!pq.empty()) {
        auto para = pq.top();
        pq.pop();

        // Т.к. у меня в pq может быть для одной вершины несколько весов, скипаем неоптимальные
        if (para.first != d[para.second]) continue;
        // cout << "Elem = " << para.second << ' ' << para.first << endl;

        for (auto edge : edges[para.second]) {
            if (d[edge.u] != UINT64_MAX && d[edge.v] > d[edge.u] + edge.w) {
                d[edge.v] = d[edge.u] + edge.w;
                // cout << "Relax: " << edge.v << ' ' << d[edge.v] << endl;
                pq.push({d[edge.v], edge.v});
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (d[i] == UINT64_MAX) {
            cout << -1 << ' ';
        } else {
            cout << d[i] << ' ';
        }
    }

}