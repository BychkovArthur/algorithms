#include <iostream>
#include <vector>

std::vector<int> z_func(const std::string& s) {
    int l = 0, r = 0, n = s.size();
    std::vector<int> z(n, 0);
    z[0] = n;

    for (int i = 1; i < n; ++i) {
        if (i < r)  z[i] = std::min(z[i - l], r - i);

        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string s;
    std::cin >> s;
    std::vector<int> z = z_func(s);
    for (const auto& e : z) {
        std::cout << e << ' ';
    }
}