/*

Код для следующей задачи: https://www.spoj.com/problems/MIXTURES/

Она очень похожа на задачу MMC

*/

#include <array>
#include <bits/stdc++.h>
#include <cstdint>

using namespace std;

void fill_prefix_sums(const array<int, 100>& arr, array<int, 100>& prefix_sums, int n) {
    prefix_sums.fill(0);
    prefix_sums[0] = arr[0];

    for (int i = 1; i < n; ++i) {
        prefix_sums[i] = prefix_sums[i - 1] + arr[i];
    }
}

int calculate_mixture_color(const array<int, 100>& prefix_sums, int left, int right) {
    return (left == 0 ? prefix_sums[right] : prefix_sums[right] - prefix_sums[left - 1]) % 100;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    array<int, 100> colors;
    array<int, 100> prefix_sums;
    array<array<int, 100>, 100> dp;

    while (cin >> n) {
        for (int i = 0; i < n; ++i) cin >> colors[i];
        fill_prefix_sums(colors, prefix_sums, n);

#ifdef DEBUG
        std::cout << "Readed colors: " << std::endl;
        for (int i = 0; i < n; ++i) std::cout << colors[i] << ' ';
        std::cout << "\n\nPrefix sums: " << std::endl;
        for (int i = 0; i < n; ++i) std::cout << prefix_sums[i] << ' ';
        std::cout << "\n\n";
#endif


        /* Смеси длины 1 не выделяют дым (т.к. смешиваний никаких нет): */
        for (int i = 0; i < n; ++i) {
            dp[i][i] = 0;
        }

        for (int mixture_length = 2; mixture_length <= n; ++mixture_length) {

            for (int left = 0; left <= n - mixture_length; ++left) {
                int right = left + mixture_length - 1;

#ifdef DEBUG
        std::cout << "Left = " << left << " right = " << right << " length = " << mixture_length << std::endl;
#endif

                /* 
                    Смесь ai, такая что left <= ai <= split_index - левая половина
                    Смесь ai, такая что split_index + 1 <= ai <= right - правая половина
                */
                int min_smoke = INT32_MAX;
                for (int split_index = left; split_index < right; ++split_index) {
                    int current_smoke = dp[left][split_index] +
                                        dp[split_index + 1][right] +
                                        (
                                            calculate_mixture_color(prefix_sums, left, split_index) * 
                                            calculate_mixture_color(prefix_sums, split_index + 1, right)
                                        );
                    if (current_smoke <= min_smoke) {
                        min_smoke = current_smoke;
                    }
                }
                dp[left][right] = min_smoke;
            }
        }

        cout << dp[0][n - 1] << '\n';
    }
}