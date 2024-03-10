#include <iostream>
#include <vector>
#include <map>

using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);


    int n;
    cin >> n;



    vector<vector<int>> a(n, vector<int>(n, 0));

    //  sum            count
    map<long long int, long long int> mp;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }
    
    for (int i = 0; i < n; ++i) { // rows
        long long int row_sum = 0;
        for (int j = 0; j < n; ++j) {
            row_sum += a[i][j];
        }
        if (mp.count(row_sum)) {
            mp[row_sum]++;
        } else {
            mp[row_sum] = 1;
        }
    }

    long long int main_sum = 15;

    
    for (auto elem : mp) {
        if (elem.second > 1) {
            main_sum = elem.first;
        }
    }

    // cout << "Main sum = " << main_sum << endl;

    int r1 = -1, c1 = -1, r2 = -1, c2 = -1;

    for (int i = 0; i < n; ++i) {
        long long int row_sum = 0;
        for (int j = 0; j < n; ++j) {
            row_sum += a[i][j];
        }
        
        // cout << "Row: " << i + 1 << " sum = " << row_sum << endl;

        if (row_sum != main_sum) {
            if (r1 == -1) {
                r1 = i;
            } else {
                r2 = i;
            }
        }
    }


    for (int i = 0; i < n; ++i) {
        long long int col_sum = 0;
        for (int j = 0; j < n; ++j) {
            col_sum += a[j][i];
        }

        // cout << "col: " << i + 1 << " sum = " << col_sum << endl;

        if (col_sum != main_sum) {
            if (c1 == -1) {
                c1 = i;
            } else {
                c2 = i;
            }
        }
    }


    if (c1 == -1 && c2 == -1) { // Всё менялось в одной колонке.

        // cout << "HERE!!!\n";

        long long int  target = main_sum;
        long long int line_sum = 0;
        for (int i = 0; i < n; ++i) {
            line_sum += a[r1][i];
        }

        // cout << "Line sum = " << line_sum << endl;

        long long int delta = target - line_sum;
        // cout << "delta = " << delta << endl;

        for (int i = 0; i < n; ++i) {
            if (a[r2][i] - a[r1][i] == delta) {
                c1 = i;
                c2 = i;
                break;
            }
        }
    }



    if (r1 == -1 && r2 == -1) { // Всё менялось в одной строке.
        long long int  target = main_sum;
        long long int col_sum = 0;
        for (int i = 0; i < n; ++i) {
            col_sum += a[i][c1];
        }
        long long int delta = target - col_sum;
        for (int i = 0; i < n; ++i) {
            if (a[i][c2] - a[i][c1] == delta) {
                r1 = i;
                r2 = i;
                break;
            }
        }
    }

    std::swap(a[r1][c1], a[r2][c2]);

    for (int i = 0; i < n; ++i) {
        int row_sum = 0;
        int col_sum = 0;

        for (int j = 0; j < n; ++j) {
            row_sum += a[i][j];
            col_sum += a[j][i];
        }

        if (row_sum != main_sum || col_sum != main_sum) {
            std::swap(c1, c2);
            break;
        }
    }

    cout << r1 + 1 << ' ' << c1 + 1 << '\n' << r2 + 1 << ' ' << c2 + 1 << endl;
}