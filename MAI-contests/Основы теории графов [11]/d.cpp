#include <bits/stdc++.h>
#include <queue>
#include <vector>

using namespace std;

vector<int> bfs(const vector<vector<int>>& g, const int u, const int v) {
    if (u == v) {
        return {u};
    }

    vector<bool> visited(g.size(), false);
    vector<int> parent(g.size(), -1);
    queue<int> q;

    visited[u] = true;
    q.push(u);

    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        for (const auto& v : g[u]) {
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    if (parent[v] == -1) {
        return {};
    }

    vector<int> res;
    int vert = v;
    while (parent[vert] != -1) {
        res.push_back(vert);
        vert = parent[vert];
    }
    res.push_back(vert);

    reverse(res.begin(), res.end());
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, u, v;
    cin >> n >> m >> u >> v;


    vector<vector<int>> g(n + 1);

    for (int i = 0; i < m; ++i) {
        int uu, vv;
        cin >> uu >> vv;
        g[uu].push_back(vv);
        g[vv].push_back(uu);
    }

    for (int i = 1; i <= n; ++i) {
        sort(g[i].begin(), g[i].end());
    }

    auto path = bfs(g, u, v);

    if (path.empty()) {
        cout << -1;
        return 0;
    }

    for (auto v : path) {
        cout << v << ' ';
    }
}