#include <bits/stdc++.h>
#include <vector>

using namespace std;

bool kunh(int u, const vector<vector<int>>& g, vector<int>& matching, vector<bool>& visited) {
    if (visited[u]) {
        return false;
    }
    visited[u] = true;

    // u - всегда вершина из ЛЕВОЙ доли

    for (const auto& v : g[u]) {
        if (matching[v] == -1 || kunh(matching[v], g, matching, visited)) {
            matching[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n + 1);


    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;

        g[u].push_back(v);
    }

    int ans = 0;
    /*
     * В matching для каждной вершины из ПРАВОЙ доли
     * записан сосед из ЛЕВОЙ
    **/
    vector<int> matching(n + 1, -1);
    vector<bool> visited(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        visited.assign(n + 1, false);
        ans += kunh(i, g, matching, visited);
    }

    cout << ans << '\n';
    for (int i = 1; i <= n; ++i) {
        if (matching[i] != -1) {
            //  Это u          это v
            cout << matching[i] << ' ' <<  i << '\n';
        }
    }
}