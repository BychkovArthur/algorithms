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

    int n, m, s = 1;
    cin >> n >> m;

    priority_queue<pr, vector<pr>, greater<pr>> pq;
    vector<vector<Edge>> edges(n + 1);

    vector<size_t> d(n + 1, UINT64_MAX);
    vector<size_t> p(n + 1, -1);

    for (int _ = 0; _ < m; ++_) {
        size_t u, v, w;
        cin >> u >> v >> w;
        edges[u].push_back({.u = u, .v = v, .w = w});
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
                p[edge.v] = edge.u;
                // cout << "Relax: " << edge.v << ' ' << d[edge.v] << endl;
                pq.push({d[edge.v], edge.v});
            }
        }
    }

    // cout << "n = " << n << endl;

    int u = n;
    vector<int> path;
    while (true) {
        // cout << u << endl;
        if (u == 1) {
            path.push_back(u);
            break;
        }
        if (u == -1) {
            cout << -1 << endl;
            return 0;
        }
        path.push_back(u);
        u = p[u];
    }

    reverse(path.begin(), path.end());
    for (auto v : path) {
        cout << v << ' ';
    }

}