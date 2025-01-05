#include "suffix_array.hpp"

#include <iostream>

#include "const.hpp"



inline bool SuffixArray::IsSorted(const std::vector<std::size_t>& eq) const {
    /* Сортировку суффиксов можно завершать тогда,
     * когда в массиве eq все числа [0 ... n - 1]
     */
    return (n_ * (n_ - 1) / 2) == std::reduce(eq.begin(), eq.end());
}

void SuffixArray::Build() {
    std::size_t sz = 1;
    std::vector<std::size_t> count_sort(std::max(kAlphabetSize, n_), 0);
    std::vector<std::size_t> eq(n_, 0);
    std::vector<std::size_t> eq_buffer(n_, 0);
    std::vector<std::size_t> array_buffer(n_);
    
    /*Первоначальная сортировка подсчетом*/
    for (std::size_t i = 0; i < n_; ++i) {
        ++count_sort[text_[i]];
    }
    for (std::size_t i = 1; i < std::max(kAlphabetSize, n_); ++i) {
        count_sort[i] += count_sort[i - 1];
    }
    for (ssize_t i = n_ - 1; i >= 0; --i) {
        array_[--count_sort[text_[i]]] = i;
    }
    /*Первоначальная сортировка подсчетом*/


    /*Первоначальный подсчет eq*/
    for (std::size_t i = 1; i < n_; ++i) {
        if (text_[array_[i]] != text_[array_[i - 1]]) {
            eq[array_[i]] = eq[array_[i - 1]] + 1;
        } else {
            eq[array_[i]] = eq[array_[i - 1]];
        }
    }
    /*Первоначальный подсчет eq*/

    while (!IsSorted(eq)) {
        std::cout << "Building suffix array.." << std::endl;
        std::fill(count_sort.begin(), count_sort.end(), 0);
        eq_buffer = eq;
        
        /* Подсчет p'*/
        for (std::size_t i = 0; i < n_; ++i) {
            array_buffer[i] = (array_[i] + n_ - sz) % n_;
        }
        /* Подсчет p'*/

        /* Подсчет p''*/
        for (std::size_t i = 0; i < n_; ++i) {
            ++count_sort[eq[array_buffer[i]]];
        }
        for (std::size_t i = 1; i < n_; ++i) {
            count_sort[i] += count_sort[i - 1];
        }
        for (ssize_t i = n_ - 1; i >= 0; --i) {
            array_[--count_sort[eq[array_buffer[i]]]] = array_buffer[i];
        }
        /* Подсчет p''*/
        
        /* Подсчет eq*/
        eq[0] = 0;
        for (std::size_t i = 1; i < n_; ++i) {
            if (
                eq_buffer[array_[i - 1]] < eq_buffer[array_[i]] ||
                eq_buffer[array_[i - 1]] == eq_buffer[array_[i]] && eq_buffer[(array_[i - 1] + sz) % n_] < eq_buffer[(array_[i] + sz) % n_]
            ) {
                eq[array_[i]] = eq[array_[i - 1]] + 1;
            } else {
                eq[array_[i]] = eq[array_[i - 1]];
            }
        }
        /* Подсчет eq*/

        sz <<= 1;
    }
}

SuffixArray::SuffixArray(const std::vector<int32_t>& text)
    : text_(text),
      n_(text_.size()),
      array_(n_, -1)
{
    Build();
}

const std::vector<std::size_t>& SuffixArray::GetSuffixArray() {
    return array_;
}