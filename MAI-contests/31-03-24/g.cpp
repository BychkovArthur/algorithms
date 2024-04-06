#include <bits/stdc++.h>


using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);


    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }


    sort(a.begin(), a.end());

    int mid = n / 2;

    while (true) {
        
        ++a[mid];
        --k;

        int curr_ind = mid;

        while (curr_ind < n - 1 && a[curr_ind] > a[curr_ind + 1]) {
            --k;
            ++a[++curr_ind];
            if (k < 0) {
                break;
            }
        }

        if (k < 0) {
            --a[mid];
            break;
        }

    }
    
    cout << a[mid] << endl;

}