#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <numeric>

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

class SegmentTree {
private:
    std::size_t n_;
    std::vector<std::size_t> data_;

    void build(
        std::size_t l,
        std::size_t r,
        std::size_t id,
        const std::vector<std::size_t>& vct
    )
    {
        if (l == r) {
            data_[id] = vct[l];
            return;
        }
        std::size_t m = (l + r) / 2;
        std::size_t lid = id * 2 + 1;
        std::size_t rid = id * 2 + 2;

        build(l, m, lid, vct);
        build(m + 1, r, rid, vct);

        data_[id] = std::min(data_[lid], data_[rid]);
    }

    std::size_t get(
        std::size_t ql,
        std::size_t qr,
        std::size_t l,
        std::size_t r,
        std::size_t id
    )
    {
        if (ql <= l && r <= qr) {
            return data_[id];
        }

        std::size_t m = (l + r) / 2;
        std::size_t lid = id * 2 + 1;
        std::size_t rid = id * 2 + 2;

        if (qr <= m) {
            return get(ql, qr, l, m, lid);
        }
        if (ql > m) {
            return get(ql, qr, m + 1, r, rid);
        }
        return std::min(get(ql, qr, l, m, lid), get(ql, qr, m + 1, r, rid));
    }

public:

    SegmentTree() : n_(0), data_() {}

    SegmentTree(const std::vector<std::size_t>& vct) : n_(vct.size()), data_(n_ * 4, 0) {
        build(0, n_ - 1, 0, vct);
    }

    void build(const std::vector<std::size_t>& vct) {
        n_ = vct.size();
        data_.resize(n_ * 4, 0);
        build(0, n_ - 1, 0, vct);
    }

    std::size_t get(
        std::size_t ql,
        std::size_t qr
    )
    {
        return get(ql, qr, 0, n_ - 1, 0);
    }

};


class SuffixArray {
private:
    const std::string& text_;
    std::size_t n_;
    std::vector<std::size_t> array_;
    std::vector<std::size_t> neighbor_lcp_;
    SegmentTree st_;


    static constexpr std::size_t different_chars = 256;

    inline bool is_sorted(const std::vector<std::size_t>& eq) const {
        /* Сортировку суффиксов можно завершать тогда,
        * когда в массиве eq все числа [0 ... n - 1]
        */
        return (n_ * (n_ - 1) / 2) == std::reduce(eq.begin(), eq.end());
    }

    void build() {
        std::size_t sz = 1;
        std::vector<std::size_t> count_sort(std::max(different_chars, n_), 0);
        std::vector<std::size_t> eq(n_, 0);
        std::vector<std::size_t> eq_buffer(n_, 0);
        std::vector<std::size_t> array_buffer(n_);
        
        /*Первоначальная сортировка подсчетом*/
        for (std::size_t i = 0; i < n_; ++i) {
            ++count_sort[text_[i]];
        }
        for (std::size_t i = 1; i < std::max(different_chars, n_); ++i) {
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

        while (!is_sorted(eq)) {
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

    bool is_suffix_lower(std::size_t suffix_id, const std::string& pattern) {
        for (std::size_t i = 0; i < pattern.size() ;++i) {
            if (i > 15) break;
            if (text_[suffix_id + i] > pattern[i]) {
                return false;
            } 
            if (text_[suffix_id + i] < pattern[i]) {
                return true;
            }
        }
        return false;
    }

    bool is_suffix_starts_with(std::size_t suffix_id, const std::string& start) {
        for (std::size_t i = 0; i < start.size(); ++i) {
            if (text_[suffix_id + i] != start[i]) return false;
        }
        return true;
    }

    void kasai() {
        std::vector<std::size_t> lcp(n_ - 1, 0);
        std::vector<std::size_t> array_inverse(n_, 0);

        for (std::size_t i = 0; i < n_; ++i) {
            array_inverse[array_[i]] = i;
        }

        std::size_t k = 0;

        for (std::size_t i = 0; i < n_ - 1; ++i) {


            if (k > 0) {
                --k;
            }
            std::size_t j = array_[array_inverse[i] - 1];

            assert(j >= 0);
            assert(j < n_);

            while (text_[j + k] == text_[i + k]) ++k;

            assert(array_inverse[i] - 1 >= 0);
            assert(array_inverse[i] - 1 < n_ - 1);

            lcp[array_inverse[i] - 1] = k;
        }
        neighbor_lcp_ = lcp;
    }

public:

    SuffixArray(const std::string& text) : text_(text), n_(text_.size() + 1), array_(n_, -1), neighbor_lcp_(n_ - 1), st_() {
        build();
        kasai();
        st_.build(neighbor_lcp_);
    }


    const std::vector<std::size_t>& get_suffix_array() {
        return array_;
    }

    std::vector<std::size_t> find_all(const std::string& pattern) {
        /* O(|si|logn_ + k|si|), где k - количество вхождений */
        std::vector<std::size_t> res;
        if (is_suffix_lower(array_[n_ - 1], pattern)) {
            return res;
        }
        std::size_t l = 0, r = n_ - 1;

        while (l < r - 1) {
            std::size_t m = (l + r) / 2;
            if (is_suffix_lower(array_[m], pattern)) {
                l = m;
            } else {
                r = m;
            }
        }
        for (std::size_t i = r; i < n_; ++i) {
            if (is_suffix_starts_with(array_[i], pattern)) {
                res.push_back(array_[i] + 1);
            } else {
                break;
            }
        }
        std::sort(res.begin(), res.end());

        return res;
    }



    std::vector<std::size_t> find_all_fast(const std::string& pattern) {
        /* O(|si|logn_ + k), где k - количество вхождений */

        std::vector<std::size_t> res;
        if (is_suffix_lower(array_[n_ - 1], pattern)) {
            return res;
        }
        std::size_t l = 0, r = n_ - 1;

        while (l < r - 1) {
            std::size_t m = (l + r) / 2;
            if (is_suffix_lower(array_[m], pattern)) {
                l = m;
            } else {
                r = m;
            }
        }

        if (!is_suffix_starts_with(array_[r], pattern)) {
            return res;
        }
        res.push_back(array_[r] + 1);
        
        for (std::size_t i = r + 1; i < n_; ++i) {

            /*Через алгоритм Касаи... я посчитал lcp для соседей.*/
            if (neighbor_lcp_[i - 1] >= pattern.size()) {
                res.push_back(array_[i] + 1);
            } else {
                break;
            }
        }
        std::sort(res.begin(), res.end());

        return res;
    }

    std::size_t lcp_with_suffix_naive(std::size_t suffix_ind, const std::string& pattern) {
        for (std::size_t i = 0; i < pattern.size(); ++i) {
            if (text_[array_[suffix_ind] + i] != pattern[i]) return i;
        }
        return pattern.size();
    }

    std::size_t common_part_from(std::size_t start, std::size_t suffix_ind, const std::string& pattern) {
        std::size_t k = 0;
        while (start + k < pattern.size() && text_[array_[suffix_ind] + start + k] == pattern[start + k]) ++k;
        return k;
    }

    std::vector<std::size_t> find_all_super_fast(const std::string& pattern) {
        /* O(|si| + log^2n_ + k), где k - количество вхождений */

        std::vector<std::size_t> res;
        if (is_suffix_lower(array_[n_ - 1], pattern)) {
            return res;
        }
        std::size_t L = 0, R = n_ - 1;
        std::size_t l = lcp_with_suffix_naive(L, pattern);
        std::size_t r = lcp_with_suffix_naive(R, pattern);


        while (L < R - 1) {
            std::size_t M = (L + R) / 2;
            std::size_t ml = st_.get(L, M - 1);
            std::size_t mr = st_.get(M, R - 1);

            if (l >= r) {
                if (ml > l) {
                    L = M;
                } else if (ml < l) {
                    R = M;
                    r = ml;
                } else {
                    std::size_t k = common_part_from(l, M, pattern);
                    if (l + k == pattern.size()) {
                        R = M;
                        r = pattern.size();
                    } else if (text_[array_[M] + l + k] < pattern[l + k]) {
                        L = M;
                        l = l + k;
                    } else if (text_[array_[M] + l + k] > pattern[l + k]) {
                        R = M;
                        r = l + k;
                    }
                }
            } else {
                if (mr > r) {
                    R = M;
                } else if (mr < r) {
                    L = M;
                    l = mr;
                } else {
                    std::size_t k = common_part_from(r, M, pattern);
                    if (r + k == pattern.size()) {
                        R = M; // Здесь не зеркалим, т.к. я нашел паттерн и я хочу, чтобы справа были >=
                        r = pattern.size();
                    } else if (text_[array_[M] + r + k] < pattern[r + k]) {
                        L = M;
                        l = r + k;
                    } else if (text_[array_[M] + r + k] > pattern[r + k]) {
                        R = M;
                        r = r + k;
                    }
                }
            }
        }

        if (!is_suffix_starts_with(array_[R], pattern)) {
            return res;
        }
        res.push_back(array_[R] + 1);
        
        for (std::size_t i = R + 1; i < n_; ++i) {

            /*Через алгоритм Касаи... я посчитал lcp для соседей.*/
            if (neighbor_lcp_[i - 1] >= pattern.size()) {
                res.push_back(array_[i] + 1);
            } else {
                break;
            }
        }
        std::sort(res.begin(), res.end());

        return res;
    } 
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string text, pattern;
    std::cin >> text;
    SuffixArray sa(text);


    std::size_t i = 0;
    while(std::cin >> pattern) {
        ++i;
        const auto& vct = sa.find_all_super_fast(pattern);

        if (vct.empty()) continue;
        std::cout << i << ": " << vct << '\n';
    }

    return 0;
}