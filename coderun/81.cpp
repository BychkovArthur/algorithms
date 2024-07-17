#include <bits/stdc++.h>

int main()
{
    int a, b, c;
    std::cin >> a >> b >> c;

    std::cout << (a + b + c - std::max(a, std::max(b, c)) > std::max(a, std::max(b, c)) ? "YES" : "NO") << std::endl;


    return 0;
}