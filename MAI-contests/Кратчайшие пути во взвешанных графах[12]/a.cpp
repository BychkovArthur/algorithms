#include <atomic>
#include <bits/stdc++.h>
#include <cstddef>
#include <cstdint>
#include <vector>

using namespace std;

struct WeightEdge {
    int w;
    int u;
    int v;
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, s;
    cin >> n >> m >> s;

    vector<int64_t> d(n + 1, INT64_MAX);
    d[s] = 0;

    vector<WeightEdge> edges;
    for (int i = 0; i < m; ++i) {
        WeightEdge edge;
        cin >> edge.u >> edge.v >> edge.w;
        edges.push_back(edge);
    }

    for (int i = 0; i < n - 1; ++i) {
        for (const auto& edge : edges) {
            if (d[edge.u] == INT64_MAX) continue;

            if (d[edge.u] + edge.w < d[edge.v]) {
                d[edge.v] = d[edge.u] + edge.w;
            }
        }
    }

    for (const auto& edge : edges) {
        if (d[edge.u] == INT64_MAX) continue;

        if (d[edge.u] + edge.w < d[edge.v]) {
            cout << "Negative cycle" << endl;
            return 0;
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (d[i] == INT64_MAX) {
            cout << "inf ";
        } else {
            cout << d[i] << ' ';
        }
    }
}