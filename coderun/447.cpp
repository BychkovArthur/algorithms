#include <bits/stdc++.h>

using namespace std;

constexpr size_t N = 1e5;
vector<bool> is_prime(N + 1, true);


void sieve() {
    is_prime[0] = false;
    is_prime[1] = false;
    for (int i = 2; i * i <= N; ++i) {
        if (!is_prime[i]) continue;
        for (int j = i * i; j <= N; j += i) {
            is_prime[j] = false;
        }
    }
}



int main() {
    sieve();
    vector<int> primes;
    for (int i = 2; i <= N; ++i) {
        if (is_prime[i]) primes.push_back(i);
    }

    int n, m;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; ++i) cin >> b[i];


    unordered_map<int, long long int> amap;
    unordered_map<int, long long int> bmap;

    for (int i = 0; i < n; ++i) {
        int num = a[i];
        for (int j = 0; num > 1 && j < primes.size(); ++j) {
            while (num % primes[j] == 0) {
                ++amap[primes[j]];
                num /= primes[j];
            }
        }
        if (num > 1) {
            ++amap[num];
        }
    }

    for (int i = 0; i < m; ++i) {
        int num = b[i];
        for (int j = 0; num > 1 && j < primes.size(); ++j) {
            while (num % primes[j] == 0) {
                ++bmap[primes[j]];
                num /= primes[j];
            }
        }
        if (num > 1) {
            ++bmap[num];
        }
    }


    unsigned long long int res = 1;
    bool greater_than_eq_10power9 = false;

    for (const auto& [prime_div, count] : amap) {
        auto total_cnt = min(count, bmap[prime_div]);

        for (int i = 0; i < total_cnt; ++i) {
            res *= prime_div;
            if (res >= 1e9) {
                res %= (uint64_t)1e9;
                greater_than_eq_10power9 = true;
            }
        }
    }

    string ans = to_string(res);

    if (greater_than_eq_10power9) {
        cout << string(9 - ans.size(), '0') << ans << endl;
    } else {
        cout << ans;
    }
}