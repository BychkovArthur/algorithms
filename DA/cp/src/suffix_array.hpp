#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>
#include <sys/types.h>
#include <numeric>

class SuffixArray {
private:
    const std::vector<int32_t> text_;
    std::size_t n_;
    std::vector<std::size_t> array_;

    inline bool IsSorted(const std::vector<std::size_t>& eq) const;

    void Build();

public:

    SuffixArray(const std::vector<int32_t>& text);

    const std::vector<std::size_t>& GetSuffixArray();
};