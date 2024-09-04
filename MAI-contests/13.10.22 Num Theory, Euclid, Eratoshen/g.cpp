#include <bits/stdc++.h>
#include <cstdint>

using namespace std;

using ll = int64_t;
// ll N = 1e9;

// vector<bool> isPrime(N + 1, 1);
// vector<ll> minPrimeDiv(N + 1, -1);


// void sieve() {
//     isPrime[0] = 0;
//     isPrime[1] = 0;
//     for (ll i = 2; i * i <= N; ++i) {
//         if (!isPrime[i]) continue;
//         for (ll j = i * i; j <= N; j += i) {
//             if (minPrimeDiv[j] == -1) minPrimeDiv[j] = i;
//             isPrime[j] = 0;
//         }
//     }
// }

// string buildMin(ll num) {
//     string res;
//     while (minPrimeDiv[num] != -1) {
//         if (minPrimeDiv[num] > 10) {
//             return "-1";
//         }
//         res.push_back(minPrimeDiv[num] - '0');
//         num /= minPrimeDiv[num];
//     }

//     if (minPrimeDiv[num] > 10) {
//         return "-1";
//     }
//     res.push_back(minPrimeDiv[num] - '0');
    
//     return res;
// }


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    // sieve();
    ll t;
    cin >> t;
    for (;t;--t) {
        ll num;
        cin >> num;

        if (num == 1) {
            cout << "1\n";
            continue;
        }
        if (num == 0) {
            cout << "10\n";
            continue;
        }

        // cout << buildMin(num) << '\n';
        string res;

        while (num % 5 == 0) num /= 5, res.push_back('5');
        while (num % 7 == 0) num /= 7, res.push_back('7');
        while (num % 8 == 0) num /= 8, res.push_back('8');

        int cnt_3 = 0, cnt_2 = 0;
        while (num % 3 == 0) ++cnt_3, num /= 3;
        while (num % 2 == 0) ++cnt_2, num /= 2;

        if (cnt_2 == 2 && cnt_3 % 2) {
            res += "26";
            res += string(cnt_3 / 2, '9');
        }
        if (cnt_2 == 2 && cnt_3 % 2 == 0) {
            res += "4";
            res += string(cnt_3 / 2, '9');
        }

        if (cnt_2 == 1 && cnt_3 % 2) {
            res += "6";
            res += string(cnt_3 / 2, '9');
        }
        if (cnt_2 == 1 && cnt_3 % 2 == 0) {
            res += "2";
            res += string(cnt_3 / 2, '9');
        }

        if (cnt_2 == 0 && cnt_3 % 2) {
            res += "3";
            res += string(cnt_3 / 2, '9');
        }
        if (cnt_2 == 0 && cnt_3 % 2 == 0) {
            res += string(cnt_3 / 2, '9');
        }
        
        if (num > 1) {
            cout << "-1\n";
        } else {
            sort(res.begin(), res.end());
            cout << res << '\n';
        }
    }
}