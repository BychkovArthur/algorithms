#include <iostream>
#include <string>
#include <vector>

using std::vector;


int main() 
{
    int n = 8;
    vector<vector<int>> a(n, vector<int>(8, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char c;
            std::cin >> c;
            if (c == '*') a[i][j] = 1;
        }
    }

    /*
        1) xxx
            x

        2) x
           xx
           x

        3)  x
           xxx

        4)  x
           xx
            x

        Индексы слева направо, сверху вниз.
        Точка отсчета - бугорок, который единственный.
    */

    vector<vector<int>> figure_shift_x = {
        {-1, 0, 1, 0},
        {-1, -1, 0, -1},
        {0, -1, 0, 1},
        {1, 0, 1, 1},
    };
    vector<vector<int>> figure_shift_y = {
        {-1, -1, -1, 0},
        {-1, 0, 0, 1},
        {0, 1, 1, 1},
        {-1, 0, 0, 1}
    };
    int res = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j]) continue;
            
            for (int k = 0; k < 4; ++k) {
                bool good = true;
                for (int kk = 0; kk < 4; ++kk) {
                    int new_i = i + figure_shift_y[k][kk];
                    int new_j = j + figure_shift_x[k][kk];
                    if (new_i < 0 || new_i >= 8 || new_j < 0 || new_j >= 8 || a[new_i][new_j]) {
                        good = false;
                        break;
                    }
                }
                res += good;
            }
        }
    }
    std::cout << res;

	return 0;
}