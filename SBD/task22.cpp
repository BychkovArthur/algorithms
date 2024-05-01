#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k, sum = 0;
    cin >> n >> k;
    // vector<int> prices(n);


    vector<bool> is_covered(n, false);
    vector<pair<int, int>> sorted(n);
    vector<int> answer(n, 0);
    set<int> indices;


    for (int i = 0; i < n; ++i) {
        // cin >> prices[i];
        int price;
        cin >> price;

        sorted[i] = {price, i};

        indices.insert(i);
    }

    sort(sorted.begin(), sorted.end());


    for (int i = 0; i < n; ++i) {
        int price = sorted[i].first;
        int ind = sorted[i].second;
        int count_to_buy = 0;

        if (!is_covered[ind]) { // начиная с нуля
            for (int j = 0; j < k; ++j) {

                if (ind + j >= n) break;

                if (is_covered[ind + j]) {
                    break;
                }
                ++count_to_buy;
                is_covered[ind + j] = true;

                indices.erase(ind + j);
            }

        } else {             // начиная с 1
            // // в тупую
            // int count_to_buy = 0;
            // for (int j = 0; j < k; ++j) {

            //     if (ind + j >= n) break;

            //     if (!is_covered[ind + j]) {
            //         ++count_to_buy;
            //         is_covered[ind + j] = true;
            //     }
            // }

            /*
                Если не в тупую, то надо найти первый индекс, больший текущего, который ещё не покрыт.
            */
            auto it = indices.upper_bound(ind);
            int first_zero_ind = (it == indices.end() ? -1 : *it);
            if (first_zero_ind == -1) {
                continue;
            }

            for (int j = 0; first_zero_ind + j < n && first_zero_ind + j - ind < k; ++j) {
                if (is_covered[first_zero_ind + j]) {
                    break;
                }
                ++count_to_buy;
                is_covered[first_zero_ind + j] = true;

                indices.erase(first_zero_ind + j);
            }
        }
        answer[ind] = count_to_buy;
        sum += count_to_buy * price;
    }

    cout << sum << endl;
    for (int i = 0; i < n; ++i) {
        cout << answer[i] << ' ';
    }
}