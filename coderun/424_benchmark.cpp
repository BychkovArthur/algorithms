#include <bits/stdc++.h>

using namespace std;

void addOne(string& s, int i) {
    int remainder = 1;

    while (i >= 0) {
        int sum = s[i] - '0' + remainder;
        remainder = sum / 10;
        s[i] = sum % 10 + '0';
        --i;
        if (!remainder) break;
    }
}

void leftGreater(string& s, int n, int s1, int s2) {
    int delta = s1 - s2;
    int i = n - 1;
    while (delta > 0) {
//            std::cout << "Delta = " << delta << " I = " << i << std::endl;
        int diff = min(9 - (s[i] - '0'), delta);
        delta -= diff;
        s[i--] += diff;
    }
}

string& optimal(string& s, int n) {
    int s1 = 0, s2 = 0;

    for (int i = 0; i < n / 2; ++i) {
        s1 += s[i] - '0';
    }
    for (int i = n / 2; i < n; ++i) {
        s2 += s[i] - '0';
    }

    if (s1 == 0) {
        s = string(n, '0');
        s[n / 2 - 1] = '1';
        s.back() = '1';
        return s;
    }

//    std::cout << "S1 = " << s1 << " S2 = " << s2 << std::endl;

    if (s1 > s2) {
        leftGreater(s, n, s1, s2);

    } else if (s2 > s1) {
        int delta = s2 - s1 + 1;
        int i = n - 1;
        char old_middle = s[n / 2 - 1];


//        std::cout << "Inside s2 > s1" << std::endl;

        while (delta > 0) {
//            std::cout << "delta = " << delta << " I = " << i << std::endl;
            int diff = min(s[i] - '0', delta);
            delta -= diff;
            s[i] -= diff;
            if (s[i] != '0') swap(s[i], s[n - 1]);
            --i;
        }

        if (i >= n/2 && s[i] < '9') {
            ++s[i];
//            std::cout << "Without +1 iterative " << s << endl;
        } else if (i >= n / 2 && s[i] == '9') {
            // Надо добавить 1 с переходом в новый разряд
            addOne(s, i);
//            cout << "After add 1 " << s << endl;

            if (s[n / 2 - 1] != old_middle) {
                // Левая часть увеличилась. Значит, вообще пофиг на правую, зануляем
                s1 = s2 = 0;
                for (int i = n / 2; i < n; ++i) {
                    s[i] = '0';
                }
                for (int i = 0; i < n / 2; ++i) {
                    s1 += s[i] - '0';
                }
                leftGreater(s, n, s1, s2);
            } else {
                s1 = s2 = 0;
                for (int i = 0; i < n / 2; ++i) {
                    s1 += s[i] - '0';
                }
                for (int i = n / 2; i < n; ++i) {
                    s2 += s[i] - '0';
                }

                leftGreater(s, n, s1, s2);
            }


        } else {
            s1 = s2 = 0;
            for (int i = n / 2; i < n; ++i) {
                s[i] = '0';
            }
            addOne(s, i);
            for (int i = 0; i < n / 2; ++i) {
                s1 += s[i] - '0';
            }
            leftGreater(s, n, s1, s2);
        }

    }

    return s;
}

string& nonoptimal(string& s, int n) {
    int num = stoi(s);

    while (true) {
        int s1 = 0, s2 = 0;
        string new_str = to_string(num);
        if (new_str.size() < 6) {
            new_str = string(6 - new_str.size(), '0') + new_str;
        }
        s1 = new_str[0] + new_str[1] + new_str[2] - 3 * '0';
        s2 = new_str[3] + new_str[4] + new_str[5] - 3 * '0';
        if (s1 == s2) {
            s = new_str;
            return s;
        } else {
            ++num;
        }
    }
}


int main() {
    srand(time(NULL));
    int n = 6;

//    string s1 = "099992";
//    string s2 = s1;
//
//    std::cout << optimal(s1, n) << std::endl;
//    std::cout << nonoptimal(s2, n) << std::endl;

    for (int i = 1; i <= 1000000; ++i) {
        string s1 = to_string(i);
        if (s1.size() < 6) {
            s1 = string(6 - s1.size(), '0') + s1;
        }
        std::cout << "Start " << i << "\nS = " << s1 << '\n';
        string s2(s1);
        string s3(s1);

        optimal(s1, n);
        nonoptimal(s2, n);
        if (s1 != s2) {
            std::cout << "Error on " << i << '\n';
            std::cout << "Start = " << s3 << '\n';
            std::cout << "Optimal: " << s1 << '\n';
            std::cout << "NonOptimal: " << s2 << std::endl;
            break;
        } else {
            std::cout << "Ok on " << i << "\n\n\n";
        }
    }
}