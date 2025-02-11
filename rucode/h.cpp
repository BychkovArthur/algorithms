#include <bits/stdc++.h>
#include <unordered_map>
#include <vector>

using namespace std;

using ll = uint64_t;

const ll N = 1e5 + 10;

bool is_prime[N];

void fill() {
    for (ll i = 0; i < N; ++i) {
        is_prime[i] = true;
    }
    is_prime[0] = false;
    is_prime[1] = false;

    for (ll i = 2; i < N; ++i) {
        if (!is_prime[i]) continue;
        for (ll j = i * i; j < N; j += i) {
            is_prime[j] = false;
        }
    }
}

unordered_map<ll, ll> fact(ll n) {
    unordered_map<ll, ll> ans;
    for (int i = 2; i <= n; ++i) {
        while (is_prime[i] && n % i == 0) {
            ans[i]++;
            n /= i;
        }
    }
    return ans;
}

int dfs(vector<ll>& visited, vector<vector<ll>>& graph, int start) {
    int ans=0;
    queue<int> q;
    q.push(start);
    visited[start] = 1;

    while(!q.empty()){
        int x = q.front();
        q.pop();

        ans++;
        // visited[x] = 1;
        for(auto child: graph[x]){
            if (!visited[child]) {
                q.push(child);
            }
            visited[child] = 1;
        }
    }
    return ans;
}

int main() {

    fill();


    // for (int i = 0; i < 100; ++i) {
    //     if (is_prime[i])
    //         cout << "i = " << i << " primt = " << is_prime[i] << endl;
    // }


    // auto mp1 = fact(11);

    // for (const auto& el : mp1) {
    //     cout << el.first << ' ' << el.second << endl;
    // }

    ll n, k;
    cin >> n >> k;
    if (k == 0) {
        cout << "0 1" <<endl;
        return 0;
    }

    vector<vector<ll>> graph(n + 1);
    vector<ll> visited(n + 1, 0);

    // for (int i = 1; i < n; ++i) {
    //     visited[i] = 0;
    // }

    auto mp1 = fact(n);
    auto mp2 = fact(n - 1);

    for (const auto& pr : mp2) {
        mp1[pr.first] += pr.second;
    }

    // в mp1 все делители.

    for (int i = 0; i < k; ++i) {
        ll u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<ll> v;

    for(int i=1;i<=n;i++){
        if (!visited[i]) {
            v.push_back(dfs(visited, graph, i));
        }
    }

    ll sum  = 0;
    ll sum2 = n * (n - 1);
    for (const auto& el : v) {
        sum += el * (el - 1);
    }

    // cout << sum << ' ' << n * n - n << endl;    
    for (auto pr : mp1) {
        while (mp1[pr.first] > 0 && sum % pr.first == 0) {
            sum /= pr.first;
            sum2 /= pr.first;
            mp1[pr.first]--;
        }
    }
    cout << sum << ' ' << sum2 << endl;
}