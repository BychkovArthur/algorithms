#include <bits/stdc++.h>

using namespace std;

bool check_win(int x, int y, set<pair<int, int>>& st) {
    
    for (int i = 0; i < 5; ++i) {
        bool win = true;
        for (int new_x = x - i; new_x < x - i + 5; ++new_x) {
            if (!st.contains({new_x, y})) {
                win = false;
            }
        }
        if (win) {
            return true;
        }
    }

    for (int i = 0; i < 5; ++i) {
        bool win = true;
        for (int new_y = y - i; new_y < y - i + 5; ++new_y) {
            if (!st.contains({x, new_y})) {
                win = false;
            }
        }
        if (win) {
            return true;
        }
    }

    for (int i = 0; i < 5; ++i) {
        bool win = true;
        for (int new_x = x - i, new_y = y - i; new_x < x - i + 5; ++new_x, ++new_y) {
            if (!st.contains({new_x, new_y})) {
                win = false;
            }
        }
        if (win) {
            return true;
        }
    }

    for (int i = 0; i < 5; ++i) {
        bool win = true;
        for (int new_x = x - i, new_y = y + i; new_x < x - i + 5; ++new_x, --new_y) {
            if (!st.contains({new_x, new_y})) {
                win = false;
            }
        }
        if (win) {
            return true;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    
    set<pair<int, int>> player1;
    set<pair<int, int>> player2;
    
    int n;
    cin >> n;
    
    int win_player = 0;
    bool play_after_won = false;

    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        if (win_player) {
            play_after_won = true;
            break;
        }

        if (!(i % 2)) {
            player1.insert({x, y});
            if(check_win(x, y, player1)) {
                win_player = 1;
            }
        } else {
            player2.insert({x, y});
            if(check_win(x, y, player2)) {
                win_player = 2;
            }
        }
    }

    if (play_after_won) {
        cout << "Inattention" << endl;
    } else {
        if (!win_player) {
            cout << "Draw" << endl;
        }
        if (win_player == 1) {
            cout << "First" << endl;
        }
        if (win_player == 2) {
            cout << "Second" << endl;
        }
    }
}