#include <bits/stdc++.h>

using namespace std;


vector<long long int> optimal(int n, int k, const vector<long long int>& vct) {
    multiset<long long int> pq;
    vector<long long int> ans;
    for (long long int i = 0; i < n; ++i) {
        if (pq.size() == k) {
            ans.push_back(*pq.begin());
            pq.erase(pq.find(vct[i - k]));
        }
        pq.insert(vct[i]);
    }
    if (!pq.empty()) {
        ans.push_back(*pq.begin());
    }
    return ans;
}

vector<long long int> nonoptimal(int n, int k, const vector<long long int>& vct) {
    vector<long long int> ans;
    for (int i = k - 1; i < n; ++i) {
        long long int mn = INT64_MAX;
        for (int j = i - k + 1; j <= i; ++j) mn = min(mn, vct[j]);
        ans.push_back(mn);
    }
    return ans;
}


int main() {
    long long int n, k;
    cin >> n >> k;
    vector<long long int> vct(n);
    for (long long int i = 0; i < n; ++i) cin >> vct[i];

    vector<long long int> ans = optimal(n, k, vct);

    for (auto el : ans) cout << el << '\n';


//    for (int i = 0; i < 1'000'000; ++i) {
//        int n = 15;
//        int k = rand() % 5 + 1;
//
//        vector<long long int> input(n);
//        for (int i = 0; i < n; ++i) input[i] = rand() % 100;
//
//        auto ans1 = optimal(n, k, input);
//        auto ans2 = nonoptimal(n, k, input);
//
//        if (ans1 != ans2) {
//            cout << "ERROR ON " << i + 1 << endl;
//            cout << "N = " << n << " K = " << k << endl;
//            for (auto el : input) {
//                cout << el << ' ';
//            }
//            cout << endl;
//            for (auto el : ans1) {
//                cout << el << ' ';
//            }
//            cout << endl;
//            for (auto el : ans2) {
//                cout << el << ' ';
//            }
//            cout << endl;
//            return 0;
//        } else {
//            cout << "OK ON " << i + 1 << "\n\n\n" << endl;
//        }
//
//    }
//
//    return 0;
}