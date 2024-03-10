#include <iostream>
#include <string>

using namespace std;

int main() {
    int g1, g2, g3, g4, type;
    string str;

    cin >> str;
    g1 = str[0] - '0';
    g2 = str[2] - '0';
    cin >> str;
    g3 = str[0] - '0';
    g4 = str[2] - '0';
    cin >> type;


    int first_team = g1 + g3;
    int second_team = g2 + g4;
    int delta = second_team - first_team;

    if (delta >= 0) {

        if (type == 1) { // Первая сначала играла дома => Сейчас играем в гостях
            cout << ((g3 + delta) > g2 ? delta : delta + 1) << endl;
        } else { // Сначала играли в гостях
            cout << (g1 > g4 ? delta : delta + 1) << endl;
        }

    } else {
        cout << 0 << endl;
    }
}