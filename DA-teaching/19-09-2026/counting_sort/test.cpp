#include "counting_sort.h"

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
        {1234, 5, 0, 1000, 500, 15, 124}, 
    };

    size_t i = 0;
    for (auto testCase : testCases) {
        auto copy = testCase;
        std::sort(copy.begin(), copy.end());
        CountingSort(testCase);

        if (copy != testCase) {
            std::cout << "Wrong answer on " << i << std::endl;
        } else {
            std::cout << "OK on " << i << std::endl;
        }
        ++i;
    }
}