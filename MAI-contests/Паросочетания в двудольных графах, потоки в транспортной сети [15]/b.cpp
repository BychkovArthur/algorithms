#include <bits/stdc++.h>
#include <vector>

using namespace std;

bool kunh(int u, const vector<vector<int>>& g, vector<int>& matching, vector<bool>& visited) {
    // u - всегда вершина из ЛЕВОЙ доли
    if (visited[u]) {
        return false;
    }
    visited[u] = true;

    for (const auto& v : g[u]) {
        // Сначала пытаемся без рекурсии втупую найти пару
        if (matching[v] == -1) {
            matching[v] = u;
            return true;
        }
    }
    
    for (const auto& v : g[u]) {
        // Уже после - рекурсия.
        if (kunh(matching[v], g, matching, visited)) {
            matching[v] = u;
            return true;
        }
    }
    return false;
}

bool IsDvudolniy(int u, const vector<vector<int>>& g, vector<int>& colors, int color) {
    colors[u] = color;

    int next_color = (color == 1 ? 2 : 1);

    for (const auto& v : g[u]) {
        if (colors[v] == next_color) {
            continue;
        }
        if (colors[v] == color) {
            return false;
        }
        if (!IsDvudolniy(v, g, colors, next_color)) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n + 1);
    // vector<vector<int>> gg(n + 1);
    vector<int> colors(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;

        if (u == v) {
            cout << -1 << endl;
            return 0;
        }

        // gg[u].push_back(v);
        g[u].push_back(v);
        g[v].push_back(u);
    }


    for (int i = 1; i <= n; ++i) {
        if (colors[i] == 0) {
            if (!IsDvudolniy(i, g, colors, 1)) {
                cout << -1 << endl;
                return 0;
            }
        }
    }

    vector<int> s1;
    vector<int> s2;
    
    for (int i = 1; i <= n; ++i) {
        if (colors[i] == 1) s1.push_back(i);
        if (colors[i] == 2) s2.push_back(i);
        if (colors[i] != 1 && colors[i] != 2) return 228;
    }


    int ans = 0;
    vector<int> matching(n + 1, -1);
    vector<bool> visited(n + 1, false);
    for (const auto& u : s1) {
        visited.assign(n + 1, false);
        ans += kunh(u, g, matching, visited);
    }

    cout << ans << '\n';
    for (int i = 1; i <= n; ++i) {
        if (matching[i] != -1) {
            //  Это u          это v
            cout << matching[i] << ' ' <<  i << '\n';
        }
    }

}