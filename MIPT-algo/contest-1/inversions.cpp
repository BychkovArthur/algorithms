#include <iostream>
#include <vector>

size_t merge(std::vector<int>& vct, std::vector<int>& buffer, size_t l, size_t r, size_t m) {
    size_t inversions = 0;
    size_t lptr = l;
    size_t rptr = m + 1;
    size_t i = 0;

    while (lptr <= m || rptr <= r) {
        // Можно делать ++i после, но тогда надо в if-else
        // В моём случае на одной итерации могут сработать сразу оба условия.
        if (lptr <= m && ((rptr <= r && vct[lptr] <= vct[rptr]) || rptr > r)) {
            buffer[l + i++] = vct[lptr++];
        }
        if (rptr <= r && ((lptr <= m && vct[lptr] > vct[rptr]) || lptr > m)) {
            buffer[l + i++] = vct[rptr++];
            inversions += (m + 1) - lptr;
        }
        
    }


    // Вот эту вещь можно сделать быстрее, если сделать 
    // Так же, как у меня в лабе по ОС'ям
    // Надо поддерживать смотреть на четность текущей глубины
    // В дереве и судя по этому, решать, куда все сливать.

    for (size_t j = l; j <= r; ++j) {
        vct[j] = buffer[j];
    }

    return inversions;
}

size_t inverse(std::vector<int>& vct, std::vector<int>& buffer, size_t l, size_t r) {
    
    if (l == r) {
        return 0;
    }

    size_t inversions = 0;

    size_t m = (l + r) / 2;

    inversions += inverse(vct, buffer, l, m);
    inversions += inverse(vct, buffer, m + 1, r);

    inversions += merge(vct, buffer, l, r, m);

    return inversions;
}

size_t inverse(std::vector<int>& vct) {
    std::vector<int> buffer(vct);

    return inverse(vct, buffer, 0, vct.size() - 1);
}

int main() {
    size_t n = 0;

    std::cin >> n;
    
    std::vector<int> vct(n); 

    for (size_t i = 0; i < n; ++i) {
        std::cin >> vct[i];
    }

    std::cout << inverse(vct) << std::endl;
}