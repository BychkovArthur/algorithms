#include <bits/stdc++.h>
#include <cstdint>
#include <vector>

using namespace std;

struct WEdge {
    int64_t u;
    int64_t v;
    int64_t w;
};

vector<int64_t> BellmanFord(const vector<vector<WEdge>>& g, int start) {
    auto n = g.size();
    vector<int64_t> d(n, INT64_MAX);
    d[start] = 0;

    for (int _ = 0; _ < n - 1; ++_) {
        for (int v = 0; v < n; ++v) {
            for (const auto& edge : g[v]) {
                if (d[edge.u] == INT64_MAX) continue;
                if (d[edge.v] > d[edge.u] + edge.w) {
                    d[edge.v] = d[edge.u] + edge.w;
                }
            }
        }
    }

    return d;
}

vector<int64_t> Dijkstra(const vector<vector<WEdge>>& reweighted, int start) {
    int n = reweighted.size();
    vector<int64_t> distances(n, INT64_MAX);

    set<pair<int64_t, int>> st;
    st.insert({0, start});
    distances[start] = 0;

    while (!st.empty()) {
        auto pr = *st.begin();
        st.erase(st.begin());

        if (distances[pr.second] != pr.first) continue;

        for (const auto& edge : reweighted[pr.second]) {
            assert(distances[edge.u] != INT64_MAX);
            if (distances[edge.v] > distances[edge.u] + edge.w) {
                distances[edge.v] = distances[edge.u] + edge.w;
                st.insert({distances[edge.v], edge.v});
            }
        }
    }

    return distances;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);


    int n;
    cin >> n;
    int s = n; // Super-вершина
    vector<vector<WEdge>> g(n + 1);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int w;
            cin >> w;
            if (i == j) continue;

            g[i].push_back({i, j, w});
        }
    }

    // 1) Добавили супер-вершину, у нулевые ребра он нее.
    for (int i = 0; i < n; ++i) {
        g[s].push_back({s, i, 0});
    }

    // 2) Нашли кратчайшие пути с помощью Белмана-Форда
    auto d = BellmanFord(g, s);

    // 3) Перевзвешиваем ребра
    vector<vector<WEdge>> reweighted(n);
    for (int i = 0; i < n; ++i) {
        reweighted[i] = g[i];
        for (auto& edge : reweighted[i]) {
            edge.w = edge.w + d[edge.u] - d[edge.v];
        }
    }

    // 4) Запускаем дейкстру для всех вершин
    vector<vector<int64_t>> distances(n);
    for (int i = 0; i < n; ++i) {
        distances[i] = Dijkstra(reweighted, i);
    }

    // 5) Перевзвешиваем ребра обратно
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            distances[i][j] = distances[i][j] - d[i] + d[j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << distances[i][j] << ' ';
        }
        cout << '\n';
    }
}