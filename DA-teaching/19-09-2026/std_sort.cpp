#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    size_t n;
    std::cin >> n;

    std::vector<int64_t> a(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::sort(a.begin(), a.end());
    for (size_t i = 0; i < n; ++i) {
        std::cout << a[i] << '\n';
    }
    std::cout << std::endl;

    return 0;
}
