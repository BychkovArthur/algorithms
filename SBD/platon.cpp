#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector<pair<ll,ll>> r_c(n);
    for (int i = 0; i < n; ++i) {
        ll r, c;
        cin >> r >> c;
        r_c[i] = {r, c};
    }

    map<pair<ll, ll>, int> m;

    int isFirst = 1;
    for (int I = 0; I < n; ++I) {
        ll r = r_c[I].first,
        c = r_c[I].second;

        m[{r, c}] = isFirst;

        // Проверка вертикали
        int number = 0; // сколько набрали нужных
        for (ll i = r - 4; i <= r + 4; ++i) {
            if (m.find({i, c}) != m.end()) {
                if (m[{i, c}] == isFirst)
                    ++number;
            } else {
                if (number == 5)
                    break;
                else
                    number = 0;
            }
        }

        if (number == 5) {
            if (I == n - 1) {
                if (isFirst)
                    cout << "First" << "\n";
                else
                    cout << "Second" << "\n";
            } else {
                cout << "Inattention" << "\n";
            }
            return 0;
        }

        // Проверка горизонтали
        number = 0; // сколько набрали нужных
        for (ll i = c - 4; i <= c + 4; ++i) {
            if (m.find({r, i}) != m.end()) {
                if (m[{r, i}] == isFirst)
                    ++number;
            } else {
                if (number == 5)
                    break;
                else
                    number = 0;
            }
        }

        if (number == 5) {
            if (I == n - 1) {
                if (isFirst)
                    cout << "First" << "\n";
                else
                    cout << "Second" << "\n";
            } else {
                cout << "Inattention" << "\n";
            }
            return 0;
        }

        // Проверка диагонали левый нижний - правый верхний
        number = 0; // сколько набрали нужных
        for (int i = -4; i <= 4; ++i) {
            if (m.find({r + i, c + i}) != m.end()) {
                if (m[{r + i, c + i}] == isFirst)
                    ++number;
            } else {
                if (number == 5)
                    break;
                else
                    number = 0;
            }
        }

        if (number == 5) {
            if (I == n - 1) {
                if (isFirst)
                    cout << "First" << "\n";
                else
                    cout << "Second" << "\n";
            } else {
                cout << "Inattention" << "\n";
            }
            return 0;
        }

        // Проверка диагонали левый верхний - правый нижний
        number = 0; // сколько набрали нужных
        for (int i = -4; i <= 4; ++i) {
            if (m.find({r - i, c + i}) != m.end()) {
                if (m[{r - i, c + i}] == isFirst)
                    ++number;
            } else {
                if (number == 5)
                    break;
                else
                    number = 0;
            }
        }

        if (number == 5) {
            if (I == n - 1) {
                if (isFirst)
                    cout << "First" << "\n";
                else
                    cout << "Second" << "\n";
            } else {
                cout << "Inattention" << "\n";
            }
            return 0;
        }

        if (isFirst)
            isFirst = 0;
        else
            isFirst = 1;
    }

    cout << "Draw" << "\n";

    return 0;
}
