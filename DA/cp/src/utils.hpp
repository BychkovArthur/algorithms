#pragma once

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <array>

#include <const.hpp>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> vct) {
    for (std::size_t i = 0; i < vct.size(); ++i) {
        os << vct[i];
        if (i != vct.size() - 1) {
            os << ", ";
        }
    }
    return os;
}

template <>
std::ostream& operator<<(std::ostream& os, const std::vector<uint8_t> vct);

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N> arr) {
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i != N - 1) {
            os << ", ";
        }
    }
    return os;
}

template <std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<uint8_t, N> arr) {
    for (std::size_t i = 0; i < N; ++i) {
        os << (int)arr[i];
        if (i != N - 1) {
            os << ", ";
        }
    }
    return os;
}

std::vector<uint16_t> CountSort(const std::vector<uint16_t>& text);

std::array<size_t, kAlphabetSize> CountBytes(const std::vector<uint8_t>& bytes);