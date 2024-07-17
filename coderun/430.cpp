#include <bits/stdc++.h>

using namespace std;



int main() {
    constexpr int n1 = 10;
    constexpr int n2 = 45;
    constexpr int n3 = 120;
    constexpr int n4 = 210;
    constexpr int n5 = 252;
    constexpr int n6 = 210;
    constexpr int n7 = 120;
    constexpr int n8 = 45;
    constexpr int n9 = 10;
    constexpr int n10 = 1;

    array<int, n1> a1 = {};
    array<int, n2> a2 = {};
    array<int, n3> a3 = {};
    array<int, n4> a4 = {};
    array<int, n5> a5 = {};
    array<int, n6> a6 = {};
    array<int, n7> a7 = {};
    array<int, n8> a8 = {};
    array<int, n9> a9 = {};
    array<int, n10> a10 = {};


    int n, index = 0;
    string s;
    vector<int> digits(10, 0);
    cin >> n;

    for (int ii = 0; ii < n; ++ii) {
        cin >> s;
        for (int i = 0; i < 10; ++i) digits[i] = 0;
        for (char c : s) digits[c - '0'] = 1;


        index = 0;
        for (int x1 = 0; x1 < 10; ++x1) {
            if (digits[x1]) {
                ++a1[index];
            }
            ++index;
        }


        index = 0;
        for (int x1 = 0; x1 < 10; ++x1) {
            for (int x2 = x1 + 1; x2 < 10; ++x2) {
                if (digits[x1] && digits[x2]) {
                    ++a2[index];
                }
                ++index;
            }
        }

        index = 0;
        for (int x1 = 0; x1 < 10; ++x1) {
            for (int x2 = x1 + 1; x2 < 10; ++x2) {
                for (int x3 = x2 + 1; x3 < 10; ++x3) {
                    if (digits[x1] && digits[x2] && digits[x3]) {
                        ++a3[index];
                    }
                    ++index;
                }
            }
        }

        index = 0;
        for (int x1 = 0; x1 < 10; ++x1) {
            for (int x2 = x1 + 1; x2 < 10; ++x2) {
                for (int x3 = x2 + 1; x3 < 10; ++x3) {
                    for (int x4 = x3 + 1; x4 < 10; ++x4) {
                        if (digits[x1] && digits[x2] && digits[x3] && digits[x4]) {
                            ++a4[index];
                        }
                        ++index;
                    }
                }
            }
        }

        index = 0;
        for (int x1 = 0; x1 < 10; ++x1) {
            for (int x2 = x1 + 1; x2 < 10; ++x2) {
                for (int x3 = x2 + 1; x3 < 10; ++x3) {
                    for (int x4 = x3 + 1; x4 < 10; ++x4) {
                        for (int x5 = x4 + 1; x5 < 10; ++x5) {
                            if (digits[x1] && digits[x2] && digits[x3] && digits[x4] && digits[x5]) {
                                ++a5[index];
                            }
                            ++index;
                        }
                    }
                }
            }
        }

        index = 0;
        for (int x1 = 0; x1 < 10; ++x1) {
            for (int x2 = x1 + 1; x2 < 10; ++x2) {
                for (int x3 = x2 + 1; x3 < 10; ++x3) {
                    for (int x4 = x3 + 1; x4 < 10; ++x4) {
                        for (int x5 = x4 + 1; x5 < 10; ++x5) {
                            for (int x6 = x5 + 1; x6 < 10; ++x6) {
                                if (digits[x1] && digits[x2] && digits[x3] && digits[x4] && digits[x5] && digits[x6]) {
                                    ++a6[index];
                                }
                                ++index;
                            }
                        }
                    }
                }
            }
        }

        index = 0;
        for (int x1 = 0; x1 < 10; ++x1) {
            for (int x2 = x1 + 1; x2 < 10; ++x2) {
                for (int x3 = x2 + 1; x3 < 10; ++x3) {
                    for (int x4 = x3 + 1; x4 < 10; ++x4) {
                        for (int x5 = x4 + 1; x5 < 10; ++x5) {
                            for (int x6 = x5 + 1; x6 < 10; ++x6) {
                                for (int x7 = x6 + 1; x7 < 10; ++x7) {
                                    if (digits[x1] && digits[x2] && digits[x3] && digits[x4] && digits[x5] && digits[x6] && digits[x7]) {
                                        ++a7[index];
                                    }
                                    ++index;
                                }
                            }
                        }
                    }
                }
            }
        }

        index = 0;
        for (int x1 = 0; x1 < 10; ++x1) {
            for (int x2 = x1 + 1; x2 < 10; ++x2) {
                for (int x3 = x2 + 1; x3 < 10; ++x3) {
                    for (int x4 = x3 + 1; x4 < 10; ++x4) {
                        for (int x5 = x4 + 1; x5 < 10; ++x5) {
                            for (int x6 = x5 + 1; x6 < 10; ++x6) {
                                for (int x7 = x6 + 1; x7 < 10; ++x7) {
                                    for (int x8 = x7 + 1; x8 < 10; ++x8) {
                                        if (digits[x1] && digits[x2] && digits[x3] && digits[x4] && digits[x5] && digits[x6] && digits[x7] && digits[x8]) {
                                            ++a8[index];
                                        }
                                        ++index;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        index = 0;
        for (int x1 = 0; x1 < 10; ++x1) {
            for (int x2 = x1 + 1; x2 < 10; ++x2) {
                for (int x3 = x2 + 1; x3 < 10; ++x3) {
                    for (int x4 = x3 + 1; x4 < 10; ++x4) {
                        for (int x5 = x4 + 1; x5 < 10; ++x5) {
                            for (int x6 = x5 + 1; x6 < 10; ++x6) {
                                for (int x7 = x6 + 1; x7 < 10; ++x7) {
                                    for (int x8 = x7 + 1; x8 < 10; ++x8) {
                                        for (int x9 = x8 + 1; x9 < 10; ++x9) {
                                            if (digits[x1] && digits[x2] && digits[x3] && digits[x4] && digits[x5] && digits[x6] && digits[x7] && digits[x8] && digits[x9]) {
                                                ++a9[index];
                                            }
                                            ++index;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        if (digits[0] && digits[1] && digits[2] && digits[3] && digits[4] && digits[5] && digits[6] && digits[7] && digits[8] && digits[9]) {
            ++a10[0];
        }
    }

    long long int s1 = 0;
    long long int s2 = 0;
    long long int s3 = 0;
    long long int s4 = 0;
    long long int s5 = 0;
    long long int s6 = 0;
    long long int s7 = 0;
    long long int s8 = 0;
    long long int s9 = 0;
    long long int s10 = 0;

    for (int i = 0; i < n1; ++i) s1 += (static_cast<long long int>(a1[i]) * (a1[i] - 1)) / 2;
    for (int i = 0; i < n2; ++i) s2 += (static_cast<long long int>(a2[i]) * (a2[i] - 1)) / 2;
    for (int i = 0; i < n3; ++i) s3 += (static_cast<long long int>(a3[i]) * (a3[i] - 1)) / 2;
    for (int i = 0; i < n4; ++i) s4 += (static_cast<long long int>(a4[i]) * (a4[i] - 1)) / 2;
    for (int i = 0; i < n5; ++i) s5 += (static_cast<long long int>(a5[i]) * (a5[i] - 1)) / 2;
    for (int i = 0; i < n6; ++i) s6 += (static_cast<long long int>(a6[i]) * (a6[i] - 1)) / 2;
    for (int i = 0; i < n7; ++i) s7 += (static_cast<long long int>(a7[i]) * (a7[i] - 1)) / 2;
    for (int i = 0; i < n8; ++i) s8 += (static_cast<long long int>(a8[i]) * (a8[i] - 1)) / 2;
    for (int i = 0; i < n9; ++i) s9 += (static_cast<long long int>(a9[i]) * (a9[i] - 1)) / 2;
    for (int i = 0; i < n10; ++i) s10 += (static_cast<long long int>(a10[i]) * (a10[i] - 1)) / 2;

//    for (int i = 0; i < n1; ++i) {
//        std::cout << "a1[" << i << "] = " << a1[i] << std::endl;
//    }
//
//    index = 0;
//    for (int x1 = 0; x1 < 10; ++x1) {
//        for (int x2 = x1 + 1; x2 < 10; ++x2) {
//            std::cout << "a2[" << x1 << ", " << x2 << "] = " << a2[index++] << std::endl;
//        }
//    }
//    std::cout << "\n\n\n";

//    index = 0;
//    for (int x1 = 0; x1 < 10; ++x1) {
//        for (int x2 = x1 + 1; x2 < 10; ++x2) {
//            for (int x3 = x2 + 1; x3 < 10; ++x3) {
//                std::cout << "a2[" << x1 << ", " << x2 << ", " << x3 << "] = " << a3[index++] << std::endl;
//            }
//
//        }
//    }

    std::cout << s1 - s2 + s3 - s4 + s5 - s6 + s7 - s8 + s9 - s10 << std::endl;
}