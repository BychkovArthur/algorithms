#include <bits/stdc++.h>

using namespace std;

void addOneOnIndex(string& s, int i) {
    /*
     * Прибавляем единицу в разряд i.
     * Если необходимо, то переносим лишнее в разряды i - 1, i - 2, ...
     * */

    int remainder = 1;

    while (i >= 0) {
        int sum = s[i] - '0' + remainder;
        remainder = sum / 10;
        s[i] = sum % 10 + '0';
        --i;
        if (!remainder) break;
    }
}

void addOne(string& s) {
    /*
     * Прибавление 1 к числу.
     * Если это число вида 9999, то оно сбрасывается до нуля.
     * */
    if (std::all_of(
            s.begin(),
            s.end(),
            [](char c) {return c == '9';}
    ))
    {
        s = string(s.size(), '0');
    } else {
        addOneOnIndex(s, s.size() - 1);
    }
}

void leftGreater(string& s, int s1, int s2) {
    int delta = s1 - s2;
    int i = s.size() - 1;
    while (delta > 0) {
        int diff = min(9 - (s[i] - '0'), delta);
        delta -= diff;
        s[i--] += diff;
    }
}

void calcSums(const string& s, int& s1, int& s2) {
    int n = s.size();
    s1 = s2 = 0;

    for (int i = 0; i < n / 2; ++i) {
        s1 += s[i] - '0';
    }
    for (int i = n / 2; i < n; ++i) {
        s2 += s[i] - '0';
    }
}

string& optimal(string& s) {
    addOne(s);

    int n = s.size(), s1 = 0, s2 = 0;

    calcSums(s, s1, s2);

    if (s1 == 0) {
        s = string(n, '0');
        s[n / 2 - 1] = '1';
        s.back() = '1';
        return s;
    }

    if (s1 > s2) {
        leftGreater(s, s1, s2);

    } else if (s2 > s1) {
        int delta = s2 - s1;
        int i = n - 1;

        while (delta > 0) {
            int diff = min(s[i] - '0', delta);
            delta -= diff;
            s[i--] -= diff;
        }

        // Случай 1 в obsidian
        if (s[i] < '9' && s[i + 1] == '0') {
            while (i >= n / 2 && s[i] == '0') --i;
            --i;
        }

        for (int j = i + 1; j < n; ++j) {
            s[j] = '0';
        }
        addOneOnIndex(s, i);
        calcSums(s, s1, s2);
        leftGreater(s, s1, s2);
    }
    return s;
}

int main() {
    string s;
    cin >> s;

    optimal(s);
    std::cout << s << std::endl;
}