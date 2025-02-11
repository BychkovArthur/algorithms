#include <array>
#include <bits/stdc++.h>
#include <string>

using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // int t;
    // cin >> t;

    // while(t--) {


        int n;
        cin >> n;


        int full = 5 * n / 10;
        int rem = 5 * n % 10;
        array<int, 10> cnt;

        for (int i = 0; i < 10; ++i) {
            cnt[i] = 0;
        }

        for (int i = 0; i < 10; ++i) {
            cnt[i] = full;
        }

        int i = 0;
        while(rem--) {
            ++cnt[i++];
        }


        for (i = 0; i < 100000; ++i) {
            int a1 = i / 10000;
            int a2 = (i / 1000) % 10;
            int a3 = (i / 100) % 10;
            int a4 = (i / 10) % 10;
            int a5 = i % 10;

            array<int, 10> curr;
            for (int i = 0; i < 10; ++i) {
                curr[i] = 0;
            }
            ++curr[a1];
            ++curr[a2];
            ++curr[a3];
            ++curr[a4];
            ++curr[a5];


            bool ok = true;
            for (int i = 0; i < 10; ++i) {
                if (cnt[i] < curr[i]) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                for (int i = 0; i < 10; ++i) {
                    cnt[i] -= curr[i];
                }
                cout << a1 << a2 << a3 << a4 << a5 << '\n';
            }
        }
        // for (int i = 0; i < 10; ++i) {
        //     if (cnt[i] > 0) {
        //         cout << "PIZDEC!";
        //     }
        // }
    // }
}