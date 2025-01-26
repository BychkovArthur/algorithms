#include <bits/stdc++.h>
#include <queue>
#include <vector>

using namespace std;

vector<int> bfs(const vector<vector<int>>& g, const int u) {
    vector<bool> visited(g.size(), false);
    vector<int> d(g.size(), -1);
    queue<int> q;

    d[u] = 0;
    visited[u] = true;
    q.push(u);

    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        for (const auto& v : g[u]) {
            if (!visited[v]) {
                visited[v] = true;
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }

    return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, u;
    cin >> n >> m >> u;


    vector<vector<int>> g(n + 1);

    for (int i = 0; i < m; ++i) {
        int uu, vv;
        cin >> uu >> vv;
        g[uu].push_back(vv);
        g[vv].push_back(uu);
    }

    auto d = bfs(g, u);

    for (int i = 1; i <= n; ++i) {
        cout << d[i] << ' ';
    }
}