#include <iostream>
#include <vector>

using namespace std;

const int B = 1;
const int R = 2;
const int n = 8;
const int COUNTED = 3;


int count_B(vector<vector<int>>& a, int i, int j) {
    int count = 0;
    int shift_i[] = {1, 1, -1, -1};
    int shift_j[] = {1, -1, 1, -1};
    
    for (int k = 0; k < 4; ++k) {

        int curr_i = i + shift_i[k];
        int curr_j = j + shift_j[k];

        while (0 <= curr_i && curr_i <= 7 && 0 <= curr_j && curr_j <= 7) {
            if (a[curr_i][curr_j] == 0) {
                a[curr_i][curr_j] = COUNTED;
                ++count;
            } else if (a[curr_i][curr_j] != COUNTED) {
                break;
            }
            curr_i += shift_i[k];
            curr_j += shift_j[k];
        }
    }
    return count;
}

int count_R(vector<vector<int>>& a, int i, int j) {
    int count = 0;
    int shift_i[] = {1, -1, 0, 0};
    int shift_j[] = {0, 0, 1, -1};
    
    for (int k = 0; k < 4; ++k) {

        int curr_i = i + shift_i[k];
        int curr_j = j + shift_j[k];

        while (0 <= curr_i && curr_i <= 7 && 0 <= curr_j && curr_j <= 7) {
            if (a[curr_i][curr_j] == 0) {
                a[curr_i][curr_j] = COUNTED;
                ++count;
            } else if (a[curr_i][curr_j] != COUNTED) {
                break;
            }
            curr_i += shift_i[k];
            curr_j += shift_j[k];
        }
    }
    return count;
}


int main() {
    vector<vector<int>> a(8, vector<int>(8, 0));

    string str;

    int res = 0;

    for (int i = 0; i < n; ++i) {
        
        cin >> str;

        for (int j = 0; j < n; ++j) {
            if (str[j] == 'B') a[i][j] = B;
            if (str[j] == 'R') a[i][j] = R;
            if (a[i][j]) ++res;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j] == B) {
                res += count_B(a, i, j);
            }
            if (a[i][j] == R) {
                res += count_R(a, i, j);
            }
        }
    }
    cout << 64 - res << endl;
}