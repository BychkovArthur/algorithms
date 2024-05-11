#include <bits/stdc++.h>

using namespace std;

struct hash_pair {
    size_t operator()(const pair<long long int, long long int>& pr) const {
        auto hash1 = std::hash<long long int>()(pr.first);
        auto hash2 = std::hash<long long int>()(pr.second);
        if (hash1 != hash2) {
            return hash1 ^ hash2;
        }
        return hash1;
    }
};

bool optimal(const vector<pair<long long int, long long int>>& input) {
    unordered_set<pair<long long int, long long int>, hash_pair> st;
    long long int n = input.size();
    long long int sum = 0;

    for (int i = 0; i < n; ++i) {
        sum += input[i].first;
        st.insert({input[i].first, input[i].second});
    }

    for (const auto& pr : st) {
        long long int x = pr.first;
        long long int y = pr.second;

        if (x * n < sum && (2 * sum % n || !st.contains({2 * sum / n - x, y}))) {
            return false;
        } else if (x * n > sum && (2 * sum % n || !st.contains({2 * sum / n - x, y}))) {
            return false;
        }
    }
    return true;
}

bool optimal2(const vector<pair<long long int, long long int>>& input) {
    unordered_set<pair<long long int, long long int>, hash_pair> st;
    long long int n = input.size();
    long long int maxX = INT64_MIN;
    long long int minX = INT64_MAX;

    for (int i = 0; i < n; ++i) {
        st.insert({input[i].first, input[i].second});
        maxX = max(maxX, input[i].first);
        minX = min(minX, input[i].first);
    }

    long long int double_mediane = maxX + minX;

    for (const auto& pr : st) {
        if (!st.contains({double_mediane - pr.first, pr.second})) {
            return false;
        }
    }
    return true;
}

int main() {
    
    for (int i = 0; i < 1'000'000; ++i) {
        cout << "Test " << i + 1 << endl;
        long long int n = rand() % 10 + 1;
        vector<pair<long long int, long long int>> input(n);

        for (int j = 0; j < n; ++j) {
            long long int x = rand() % 11 - 5;
            long long int y = rand() % 11 - 5;
            input[j] = {x, y};
        }

        bool res1 = optimal(input);
        bool res2 = optimal(input);
        if (res1 != res2) {
            cout << "Not correct!" << endl;
            for (int j = 0; j < n; ++j) {
                cout << input[j].first << ' ' << input[j].second << endl;
            }
            break;
        }
        if (res1 && n > 5) {
            cout << "TRUE" << endl;
            for (int j = 0; j < n; ++j) {
                cout << input[j].first << ' ' << input[j].second << endl;
            }
        }
        
    }

    

    
}