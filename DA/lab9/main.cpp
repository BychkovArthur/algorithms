#include <bits/stdc++.h>
#include <utility>

using namespace std;

vector<vector<int>> graph;
vector<int> matching;
vector<bool> used;

bool augment(int v) {
    if (used[v]) {
        return false;
    }
    used[v] = true;
    for (const auto& to : graph[v]) {
        if (matching[to] == -1 || augment(matching[to])) {
            matching[to] = v;
            return true;
        }
    }
    return false;
}


bool is_bipartite(int n) {
    vector<int> color(n, -1);
    queue<int> q;
    
    for (int start = 0; start < n; ++start) {
        if (color[start] == -1) {
            color[start] = 0;
            q.push(start);

            while (!q.empty()) {
                int v = q.front();
                q.pop();

                for (const auto& to : graph[v]) {
                    if (color[to] == -1) {
                        color[to] = 1 - color[v];
                        q.push(to);
                    } else if (color[to] == color[v]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    graph.resize(n);
    matching.resize(n, -1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for (int i = 0; i < n; ++i) {
        sort(graph[i].begin(), graph[i].end(), less<int>());
    }

    if (!is_bipartite(n)) {
        cout << "-1";
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        used.assign(n, false);
        augment(i);
    }

    set<pair<int, int>> edges;

    for (int i = 0; i < n; ++i) {
        if (matching[i] != -1) {
            edges.insert(
                i < matching[i]
                ? make_pair(i, matching[i])
                : make_pair(matching[i], i)
            );
        }
    }

    cout << edges.size() << '\n';
    for (const auto& edge: edges) {
        cout << edge.first + 1 << ' ' << edge.second + 1 << '\n';
    }
}