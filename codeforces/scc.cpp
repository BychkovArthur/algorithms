/*
 * Задача: https://codeforces.com/problemset/problem/427/C
 *
**/


#include <bits/stdc++.h>
#include <cstddef>
#include <unordered_map>
#include <vector>

using namespace std;

void topological_sort(const int u, const vector<vector<int>>& g, vector<int>& colors, vector<int>& topological_sort_vct) {
    colors[u] = 1;
    for (auto v : g[u]) {
        if (colors[v] == 0) {
            topological_sort(v, g, colors, topological_sort_vct);
        }
    }
    topological_sort_vct.push_back(u);
}

void color_dfs(const int u, const int color, const vector<vector<int>>& g, vector<int>& colors) {
    colors[u] = color;
    for (auto v : g[u]) {
        if (colors[v] == 0) {
            color_dfs(v, color, g, colors);
        }
    }
}


int main() {
    int n, m;
    cin >> n;
    vector<int> price(n + 1);
    vector<vector<int>> g(n + 1);
    vector<vector<int>> gg(n + 1);
    
    for (int i = 1; i <= n; ++i) {
        cin >> price[i];
    }

    cin >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        gg[v].push_back(u);
    }

    vector<int> colors(n + 1, 0);
    vector<int> topological_sort_vct;

    for (int i = 1; i <= n; ++i) {
        if (colors[i] == 0) {
            topological_sort(i, g, colors, topological_sort_vct);
        }
    }

    reverse(topological_sort_vct.begin(), topological_sort_vct.end());

    // for (auto v : topological_sort_vct) {
    //     cout << v << ' ';
    // }

    int color = 0;
    colors.assign(n + 1, 0);
    for (auto u : topological_sort_vct) {
        if (colors[u] == 0) {
            color_dfs(u, ++color, gg, colors);
        }
    }

    // for (int i = 1; i <= n; ++i) {
    //     cout << i << " : " << colors[i] << endl;
    // }

    unordered_map<int, int> min_prices;
    for (int i = 1; i <= n; ++i) {
        if (!min_prices.contains(colors[i])) {
            min_prices[colors[i]] = price[i];
        } else {
            min_prices[colors[i]] = min(price[i], min_prices[colors[i]]);
        }
    }

    unordered_map<int, size_t> min_price_cnt;
    for (int i = 1; i <= n; ++i) {
        if (min_prices[colors[i]] == price[i]) {
            min_price_cnt[colors[i]]++;
        }
    }

    size_t sum = 0;
    for (const auto& pr : min_prices) {
        sum += pr.second;
    }

    size_t cnt = 1;
    for (const auto& pr : min_price_cnt) {
        cnt *= pr.second;
        cnt %= 1000000007;
    }
    cout << sum << ' ' << cnt << endl;
}