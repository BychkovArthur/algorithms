#include "lsd_sort.h"

#include <limits>
#include <iostream>
#include <algorithm>


int main() {
    std::vector<std::vector<size_t>> testCases = {
        {},
        {1},
        {0},
        {0, 1, 2, 3, 4}, // Sorted
        {5, 4, 3, 2, 0}, // Reversed
        {1, 3, 4, 3, 5, 3, 0, 3}, // Duplicates
        {7, 7, 7, 7, 7, 7}, // All same
        {12341661, 5, 0, 999999999, 1234444, 15, 124}, 
        {0, 1, std::numeric_limits<size_t>::max(), 0, 1, 500, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::min()},
    };

    size_t i = 0;
    for (auto testCase : testCases) {
        auto copy = testCase;
        std::sort(copy.begin(), copy.end());
        LSD(testCase);

        if (copy != testCase) {
            std::cout << "Wrong answer on " << i << std::endl;
        } else {
            std::cout << "OK on " << i << std::endl;
        }
        ++i;
    }
}