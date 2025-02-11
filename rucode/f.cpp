#include <bits/stdc++.h>

using namespace std;

bool isWhite(char c) {
    return (c == 'k' || c == 'r' || c == 'q' || c == 'n' || c == 'b' || c == 'p');
}
bool isBlack(char c) {
    return (c == 'K' || c == 'R' || c == 'Q' || c == 'N' || c == 'B' || c == 'P');
}
bool valid(int i) {
    return (0 <= i && i <= 7);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector<vector<char>> main(8, vector<char>(8));
    vector<vector<char>> white(8, vector<char>(8, '?'));
    vector<vector<char>> black(8, vector<char>(8, '?'));

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            cin >> main[i][j];
        }
    }

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            
            char c = main[i][j];
            if (isWhite(c)) {
                white[i][j] = c;

                if (c == 'k') { // король

                    if ( valid(i - 1) && valid(j - 1) )
                        white[i - 1][j - 1] = main[i - 1][j - 1];
                    if ( valid(i - 1) && valid(j + 1) )
                        white[i - 1][j + 1] = main[i - 1][j + 1];
                    if ( valid(i - 1) && valid(j) )
                        white[i - 1][j] = main[i - 1][j];
                    
                    if ( valid(i + 1) && valid(j - 1) )
                        white[i + 1][j - 1] = main[i + 1][j - 1];
                    if ( valid(i + 1) && valid(j + 1) )
                        white[i + 1][j + 1] = main[i + 1][j + 1];
                    if ( valid(i + 1) && valid(j) )
                        white[i + 1][j] = main[i + 1][j];
                    
                    if ( valid(i) && valid(j - 1) )
                        white[i][j - 1] = main[i][j - 1];
                    if ( valid(i) && valid(j + 1) )
                        white[i][j + 1] = main[i][j + 1];

                } else if (c == 'r') { // ладья

                    for (int k = 0; valid(i + k); ++k) {
                        white[i + k][j] = main[i + k][j];
                        if (isBlack(main[i + k][j]))
                            break;
                    }
                    for (int k = 0; valid(i - k); ++k) {
                        white[i - k][j] = main[i - k][j];
                        if (isBlack(main[i - k][j]))
                            break;
                    }
                    for (int k = 0; valid(j + k); ++k) {
                        white[i][j + k] = main[i][j + k];
                        if (isBlack(main[i][j + k]))
                            break;
                    }
                    for (int k = 0; valid(j - k); ++k) {
                        white[i][j - k] = main[i][j - k];
                        if (isBlack(main[i][j - k]))
                            break;
                    }

                } else if (c == 'b') { // слон

                    for (int k = 0; valid(i + k) && valid(j + k); ++k) {
                        white[i + k][j + k] = main[i + k][j + k];
                        if (isBlack(main[i + k][j + k]))
                            break;
                    }
                    for (int k = 0; valid(i + k) && valid(j - k); ++k) {
                        white[i + k][j - k] = main[i + k][j - k];
                        if (isBlack(main[i + k][j - k]))
                            break;
                    }
                    for (int k = 0; valid(i - k) && valid(j + k); ++k) {
                        white[i - k][j + k] = main[i - k][j + k];
                        if (isBlack(main[i - k][j + k]))
                            break;
                    }
                    for (int k = 0; valid(i - k) && valid(j - k); ++k) {
                        white[i - k][j - k] = main[i - k][j - k];
                        if (isBlack(main[i - k][j - k]))
                            break;
                    }

                } else if (c == 'q') { // ферзь

                    // Ладья
                    for (int k = 0; valid(i + k); ++k) {
                        white[i + k][j] = main[i + k][j];
                        if (isBlack(main[i + k][j]))
                            break;
                    }
                    for (int k = 0; valid(i - k); ++k) {
                        white[i - k][j] = main[i - k][j];
                        if (isBlack(main[i - k][j]))
                            break;
                    }
                    for (int k = 0; valid(j + k); ++k) {
                        white[i][j + k] = main[i][j + k];
                        if (isBlack(main[i][j + k]))
                            break;
                    }
                    for (int k = 0; valid(j - k); ++k) {
                        white[i][j - k] = main[i][j - k];
                        if (isBlack(main[i][j - k]))
                            break;
                    }

                    // Слон
                    for (int k = 0; valid(i + k) && valid(j + k); ++k) {
                        white[i + k][j + k] = main[i + k][j + k];
                        if (isBlack(main[i + k][j + k]))
                            break;
                    }
                    for (int k = 0; valid(i + k) && valid(j - k); ++k) {
                        white[i + k][j - k] = main[i + k][j - k];
                        if (isBlack(main[i + k][j - k]))
                            break;
                    }
                    for (int k = 0; valid(i - k) && valid(j + k); ++k) {
                        white[i - k][j + k] = main[i - k][j + k];
                        if (isBlack(main[i - k][j + k]))
                            break;
                    }
                    for (int k = 0; valid(i - k) && valid(j - k); ++k) {
                        white[i - k][j - k] = main[i - k][j - k];
                        if (isBlack(main[i - k][j - k]))
                            break;
                    }

                } else if (c == 'n') { // конь

                    if (valid(i + 2) && valid(j - 1))
                        white[i + 2][j - 1] = main[i + 2][j - 1];
                    if (valid(i + 2) && valid(j + 1))
                        white[i + 2][j + 1] = main[i + 2][j + 1];
                    if (valid(j + 2) && valid(i - 1))
                        white[i - 1][j + 2] = main[i - 1][j + 2];
                    if (valid(j + 2) && valid(i + 1))
                        white[i + 1][j + 2] = main[i + 1][j + 2];
                    if (valid(i - 2) && valid(j - 1))
                        white[i - 2][j - 1] = main[i - 2][j - 1];
                    if (valid(i - 2) && valid(j + 1))
                        white[i - 2][j + 1] = main[i - 2][j + 1];
                    if (valid(j - 2) && valid(i - 1))
                        white[i - 1][j - 2] = main[i - 1][j - 2];
                    if (valid(j - 2) && valid(i + 1))
                        white[i + 1][j - 2] = main[i + 1][j - 2];

                } else if (c == 'p') { // пешка

                    if (valid(i + 1) && valid(j - 1))
                        white[i + 1][j - 1] = main[i + 1][j - 1];
                    if (valid(i + 1) && valid(j))
                        white[i + 1][j] = main[i + 1][j];
                    if (valid(i + 1) && valid(j + 1))
                        white[i + 1][j + 1] = main[i + 1][j + 1];

                }
            }

            else if (isBlack(c)) {
                black[i][j] = c;

                if (c == 'K') { // король

                    if ( valid(i - 1) && valid(j - 1) )
                        black[i - 1][j - 1] = main[i - 1][j - 1];
                    if ( valid(i - 1) && valid(j + 1) )
                        black[i - 1][j + 1] = main[i - 1][j + 1];
                    if ( valid(i - 1) && valid(j) )
                        black[i - 1][j] = main[i - 1][j];
                    
                    if ( valid(i + 1) && valid(j - 1) )
                        black[i + 1][j - 1] = main[i + 1][j - 1];
                    if ( valid(i + 1) && valid(j + 1) )
                        black[i + 1][j + 1] = main[i + 1][j + 1];
                    if ( valid(i + 1) && valid(j) )
                        black[i + 1][j] = main[i + 1][j];
                    
                    if ( valid(i) && valid(j - 1) )
                        black[i][j - 1] = main[i][j - 1];
                    if ( valid(i) && valid(j + 1) )
                        black[i][j + 1] = main[i][j + 1];

                } else if (c == 'R') { // ладья

                    for (int k = 0; valid(i + k); ++k) {
                        black[i + k][j] = main[i + k][j];
                        if (isWhite(main[i + k][j]))
                            break;
                    }
                    for (int k = 0; valid(i - k); ++k) {
                        black[i - k][j] = main[i - k][j];
                        if (isWhite(main[i - k][j]))
                            break;
                    }
                    for (int k = 0; valid(j + k); ++k) {
                        black[i][j + k] = main[i][j + k];
                        if (isWhite(main[i][j + k]))
                            break;
                    }
                    for (int k = 0; valid(j - k); ++k) {
                        black[i][j - k] = main[i][j - k];
                        if (isWhite(main[i][j - k]))
                            break;
                    }

                } else if (c == 'B') { // слон

                    for (int k = 0; valid(i + k) && valid(j + k); ++k) {
                        black[i + k][j + k] = main[i + k][j + k];
                        if (isWhite(main[i + k][j + k]))
                            break;
                    }
                    for (int k = 0; valid(i + k) && valid(j - k); ++k) {
                        black[i + k][j - k] = main[i + k][j - k];
                        if (isWhite(main[i + k][j - k]))
                            break;
                    }
                    for (int k = 0; valid(i - k) && valid(j + k); ++k) {
                        black[i - k][j + k] = main[i - k][j + k];
                        if (isWhite(main[i - k][j + k]))
                            break;
                    }
                    for (int k = 0; valid(i - k) && valid(j - k); ++k) {
                        black[i - k][j - k] = main[i - k][j - k];
                        if (isWhite(main[i - k][j - k]))
                            break;
                    }

                } else if (c == 'Q') { // ферзь

                    // Ладья
                    for (int k = 0; valid(i + k); ++k) {
                        black[i + k][j] = main[i + k][j];
                        if (isWhite(main[i + k][j]))
                            break;
                    }
                    for (int k = 0; valid(i - k); ++k) {
                        black[i - k][j] = main[i - k][j];
                        if (isWhite(main[i - k][j]))
                            break;
                    }
                    for (int k = 0; valid(j + k); ++k) {
                        black[i][j + k] = main[i][j + k];
                        if (isWhite(main[i][j + k]))
                            break;
                    }
                    for (int k = 0; valid(j - k); ++k) {
                        black[i][j - k] = main[i][j - k];
                        if (isWhite(main[i][j - k]))
                            break;
                    }

                    // Слон
                    for (int k = 0; valid(i + k) && valid(j + k); ++k) {
                        black[i + k][j + k] = main[i + k][j + k];
                        if (isWhite(main[i + k][j + k]))
                            break;
                    }
                    for (int k = 0; valid(i + k) && valid(j - k); ++k) {
                        black[i + k][j - k] = main[i + k][j - k];
                        if (isWhite(main[i + k][j - k]))
                            break;
                    }
                    for (int k = 0; valid(i - k) && valid(j + k); ++k) {
                        black[i - k][j + k] = main[i - k][j + k];
                        if (isWhite(main[i - k][j + k]))
                            break;
                    }
                    for (int k = 0; valid(i - k) && valid(j - k); ++k) {
                        black[i - k][j - k] = main[i - k][j - k];
                        if (isWhite(main[i - k][j - k]))
                            break;
                    }

                } else if (c == 'N') { // конь

                    if (valid(i + 2) && valid(j - 1))
                        black[i + 2][j - 1] = main[i + 2][j - 1];
                    if (valid(i + 2) && valid(j + 1))
                        black[i + 2][j + 1] = main[i + 2][j + 1];
                    if (valid(j + 2) && valid(i - 1))
                        black[i - 1][j + 2] = main[i - 1][j + 2];
                    if (valid(j + 2) && valid(i + 1))
                        black[i + 1][j + 2] = main[i + 1][j + 2];
                    if (valid(i - 2) && valid(j - 1))
                        black[i - 2][j - 1] = main[i - 2][j - 1];
                    if (valid(i - 2) && valid(j + 1))
                        black[i - 2][j + 1] = main[i - 2][j + 1];
                    if (valid(j - 2) && valid(i - 1))
                        black[i - 1][j - 2] = main[i - 1][j - 2];
                    if (valid(j - 2) && valid(i + 1))
                        black[i + 1][j - 2] = main[i + 1][j - 2];

                } else if (c == 'P') { // пешка

                    if (valid(i - 1) && valid(j - 1))
                        black[i - 1][j - 1] = main[i - 1][j - 1];
                    if (valid(i - 1) && valid(j))
                        black[i - 1][j] = main[i - 1][j];
                    if (valid(i - 1) && valid(j + 1))
                        black[i - 1][j + 1] = main[i - 1][j + 1];

                }
            }

        }
    }

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            cout << white[i][j];
        }
        cout << "\n";
    }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            cout << black[i][j];
        }
        cout << "\n";
    }
}