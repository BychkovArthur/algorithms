#include <vector>
#include <iostream>

#define MIN(A, B) (A <= B ? A : B)

int main() {

    size_t n;
    size_t q;
    std::cin >> n;

    std::vector<int> vct(n);
    std::vector<int> prefix(n);
    std::vector<int> suffix(n);

    for (size_t i = 0; i < n; ++i) {
        std::cin >> vct[i];
    }

    prefix[0] = vct[0];
    for (size_t i = 1; i < n; ++i) {
        prefix[i] = MIN(vct[i], prefix[i - 1]);
    }

    suffix[n - 1] = vct[n - 1];
    for (ssize_t i = n - 2; i >= 0; --i) {
        suffix[i] = MIN(vct[i], suffix[i + 1]);
    }

    std::cin >> q;
    for (size_t i = 0; i < q; ++i) {
        size_t l, r;
        std::cin >> l >> r;
        std::cout << MIN(prefix[l - 1], suffix[r - 1]) << std::endl;
    }

    return EXIT_SUCCESS;
}