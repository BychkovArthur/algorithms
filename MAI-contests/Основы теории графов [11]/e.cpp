#include <bits/stdc++.h>
#include <cassert>
#include <vector>

using namespace std;


vector<int> colors;
vector<int> path_;
int cnt = 0;

void dfs(const int prev, const int u, const vector<vector<int>>& g, vector<int>& path) {
    if (colors[u] == 2) {
        return;
    }

    path.push_back(u);
    if (colors[u] == 1) {
        path_ = path;
        path.pop_back();
        ++cnt;
        return;
    }
    colors[u] = 1;

    for (auto v : g[u]) {
        if (v != prev) {
            dfs(u, v, g, path);
        }
        
    }

    path.pop_back();
    colors[u] = 2;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<vector<int>> g(n + 1);
    colors.resize(n + 1, 0);

    int u, v;
    while (cin >> u >> v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> path;

    for (int i = 1; i <= n; ++i) {
        dfs(-1, i, g, path);
        assert(path.empty());
    }

    const auto start = find(path_.begin(), path_.end(), path_.back());

    assert(start != path_.end());
    assert(start != (path_.end() - 1));
    
    sort(start + 1, path_.end());
    for (auto it = start + 1; it != path_.end(); ++it) {
        cout << *it << ' ';
    }
    assert(cnt == 1);
}