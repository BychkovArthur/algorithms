#include <algorithm>
#include <iostream>
#include <vector>

#define all(x) x.begin(), x.end()

using namespace std;

bool can_be_covered_by_segments(vector<long long int>& a, long long int segment_len,
                                long long int max_segment_cnt) {
    long long int covered_up = a[0] + segment_len;
    long long int segment_cnt = 1;

    for (long long int i = 1; i < a.size(); ++i) {
        if (segment_cnt > max_segment_cnt) {
            break;
        }

        if (a[i] > covered_up) {
            covered_up = a[i] + segment_len;
            ++segment_cnt;
        }
    }

    return segment_cnt <= max_segment_cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    long long int n, k;
    cin >> n >> k;
    vector<long long int> a(n);

    for (long long int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sort(all(a));

    long long int l = -1;
    long long int r = 2e9;

    while (l < r - 1) {
        long long int m = (l + r) / 2;

        if (can_be_covered_by_segments(a, m, k)) {
            r = m;
        } else {
            l = m;
        }
    }

    cout << r << endl;
}