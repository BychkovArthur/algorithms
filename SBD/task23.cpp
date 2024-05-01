#include <bits/stdc++.h>

using namespace std;

using ll = long long int;

struct offer {
    ll u;
    ll v;
    ll t;
    ll c;
};

struct limitation {
    ll u;
    ll v;
    ll t;
};

bool is_good(vector<vector<ll>> matrix, vector<offer>& offers, vector<limitation>& limitations, ll max_c, ll n) {

    for (int i = 0; i < offers.size(); ++i) {
        offer offer = offers[i];
        if (offer.c <= max_c) {
            matrix[offer.u][offer.v] = offer.t;
            matrix[offer.v][offer.u] = offer.t;
        }
    }

    // for (int u = 1; u <= n; ++u) {
    //     for (int v = 1; v <= n; ++v) {
    //         cout << matrix[u][v] << ' ';
    //     }
    //     cout << endl;
    // }

    for (int k = 1; k <= n; ++k) {
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                matrix[u][v] = min(matrix[u][v], matrix[u][k] + matrix[k][v]);
            }
        }
    }


    for (int i = 0; i < limitations.size(); ++i) {
        limitation lim = limitations[i];
        if (matrix[lim.u][lim.v] > lim.t) {
            return false;
        }
    }

    return true;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, m, k, p;
    cin >> n >> m;
    vector<vector<ll>> matrix(n + 1, vector<ll>(n + 1, 1e18));
    
    // cout << INT64_MAX << endl;
    // for (int u = 1; u <= n; ++u) {
    //     for (int v = 1; v <= n; ++v) {
    //         cout << matrix[u][v] << ' ';
    //     }
    //     cout << endl;
    // }

    for (int i = 0; i < m; ++i) {
        ll u, v, t;
        cin >> u >> v >> t;

        matrix[u][v] = t;
        matrix[v][u] = t;
    }
    for (int i = 0; i <= n; ++i) {
        matrix[i][i] = 0;
    }


    cin >> k;
    vector<offer> offers(k);

    for (int i = 0; i < k; ++i) {
        ll u, v, t, c;
        cin >> u >> v >> t >> c;
        offers[i] = {u, v, t, c};
    }

    cin >> p;
    vector<limitation> limitations(p);

    for (int i = 0; i < p; ++i) {
        ll u, v, t;
        cin >> u >> v >> t;
        limitations[i] = {u, v, t};
    }


    if (is_good(matrix, offers, limitations, 0, n)) { // можно сразу
        cout << 0;
        return 0;
    }
    if (!is_good(matrix, offers, limitations, 1e9, n)) { // вообще нельзя
        cout << -1;
        return 0;
    }

    ll l = 0, r = 1e9;

    while (l < r - 1) {
        ll mm = (l + r) / 2;
        if (is_good(matrix, offers, limitations, mm, n)) {
            // cout << "good " << mm << endl;
            r = mm;
        } else {
            // cout << "bad " << mm << endl;
            l = mm;
        }
    }

    vector<ll> res;
    for (int i = 0; i < offers.size(); ++i) {
        offer offer = offers[i];
        if (offer.c <= r) {
            res.push_back(i + 1);
        }
    }

    cout << res.size() << endl;
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i] << ' ';
    }
}