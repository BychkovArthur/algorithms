    #include <bits/stdc++.h>

    #define all(x) (x).begin(), (x).end()

    using namespace std;

    using ll = int64_t;
    using ull = uint64_t;
    using vi = vector<int>;
    using vll = vector<ll>;
    using pii = pair<int, int>;
    using pll = pair<ll, ll>;

    template <typename _Key, typename _Tp>
    using umap = unordered_map<_Key, _Tp>;
    template <typename _Value>
    using uset = unordered_set<_Value>;

    static const ll mod1 = 1'000'000'007;
    static const ll mod2 = 2'147'483'647;

    ll min3(ll a, ll b, ll c) {
        if (a <= b && a <= c) return a;
        if (b <= a && b <= c) return b;
        return c;
    }

    ll max3(ll a, ll b, ll c) {
        if (a >= b && a >= c) return a;
        if (b >= a && b >= c) return b;
        return c;
    }

    ll max(const vll& vct) {
        return max3(vct[0], vct[1], vct[2]);
    }

    ll min(const vll& vct) {
        return min3(vct[0], vct[1], vct[2]);
    }

    ll calc(const vll& vct) {
        ll res = 0;
        res += vct[0] * vct[0];
        res += vct[1] * vct[1];
        res += vct[2] * vct[2];

        res += min3(vct[0], vct[1], vct[2]) * 7;
        return res;
    }



    int main() {
        ios::sync_with_stdio(false);
        cin.tie(NULL);

        ll n;
        cin >> n;

        vector<vll> players(n, vll(4));
        vll answers(n);

        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                cin >> players[i][j];
            }
        }

        // for (size_t i = 0; i < n; ++i) {
        //     for (size_t j = 0; j < 4; ++j) {
        //         cout << players[i][j] << " ";
        //     }
        //     cout << endl;
        // }


        for (size_t i = 0; i < n; ++i) {

            ll mx = max(players[i]);
            ll mn = min(players[i]);

            if (players[i][3] <= 10) {

                // vll permut(3);

                // cout << "PLAYERS: " << endl;
                // for (size_t j = 0; j < 4; ++j) {
                //     cout << players[i][j] << " ";
                // }
                // cout << endl;

                vll answer = players[i];

                for (int x1 = 0; x1 <= 10; ++x1) {
                    for (int x2 = 0; x2 <= 10; ++x2) {
                        for (int x3 = 0; x3 <= 10; ++x3) {
                            if (x1 + x2 + x3 == players[i][3]) {
                                // permut[0] = x1;
                                // permut[1] = x2;
                                // permut[2] = x3;
                                // cout << x1 << " " << x2 << " " << x3 << endl;

                                vll temp = players[i];

                                temp[0] += x1;
                                temp[1] += x2;
                                temp[2] += x3;

                                // cout << "temp: " << endl;
                                // for (size_t j = 0; j < 4; ++j) {
                                //     cout << temp[j] << " ";
                                // }
                                // cout << "calc tmp = " << calc(temp) << " calc players = " << calc(answer) << endl;
                                // cout << "\n\n\n" << endl;

                                if (calc(temp) > calc(answer)) {
                                    answer[0] = temp[0];
                                    answer[1] = temp[1];
                                    answer[2] = temp[2];
                                    // cout << "HERE " << answer[0] << " " << answer[1] << " " << answer[2] << endl;
                                }

                            }
                        }
                    }
                }

                std::swap(answer, players[i]);


            } else {


                if (players[i][0] == mx) {
                    players[i][0] += players[i][3];

                } else if (players[i][1] == mx) {
                    players[i][1] += players[i][3];

                } else if (players[i][2] == mx) {
                    players[i][2] += players[i][3];

                }


            }



        }

        for (size_t i = 0; i < n; ++i) {

            cout << calc(players[i]) << endl;
            
        }

        
        return 0;
    }