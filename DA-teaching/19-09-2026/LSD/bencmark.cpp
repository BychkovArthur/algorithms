#include "lsd_sort.h"

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

namespace {

using Clock = std::chrono::steady_clock;
using SortFunction = void (*)(std::vector<std::uint64_t>&);

struct BenchmarkResult {
    double minimumMs = 0.0;
    double medianMs = 0.0;
    double averageMs = 0.0;
    bool correct = true;
};

void standardSort(std::vector<std::uint64_t>& values) {
    std::sort(values.begin(), values.end());
}

std::vector<std::uint64_t> generateValues(std::size_t size,
                                          std::uint64_t seed) {
    std::mt19937_64 generator(seed);
    std::uniform_int_distribution<int> distribution(
        std::numeric_limits<int>::min(),
        std::numeric_limits<int>::max()
    );
    std::vector<std::uint64_t> values(size);

    for (std::uint64_t& value : values) {
        value = distribution(generator);
    }

    return values;
}

BenchmarkResult runBenchmark(
    SortFunction sortFunction,
    const std::vector<std::uint64_t>& source,
    const std::vector<std::uint64_t>& expected,
    std::size_t repetitions) {
    std::vector<double> times;
    times.reserve(repetitions);
    bool correct = true;

    for (std::size_t repetition = 0; repetition < repetitions; ++repetition) {
        // Копирование не входит в измеряемое время.
        std::vector<std::uint64_t> values = source;

        const auto start = Clock::now();
        sortFunction(values);
        const auto finish = Clock::now();

        const std::chrono::duration<double, std::milli> elapsed =
            finish - start;
        times.push_back(elapsed.count());
        correct = correct && (values == expected);
    }

    std::sort(times.begin(), times.end());

    double sum = 0.0;
    for (const double time : times) {
        sum += time;
    }

    return {
        times.front(),
        times[times.size() / 2],
        sum / static_cast<double>(times.size()),
        correct,
    };
}

void printResult(const char* name, const BenchmarkResult& result) {
    std::cout << std::left << std::setw(12) << name
              << " min: " << std::right << std::setw(10) << result.minimumMs
              << " ms, median: " << std::setw(10) << result.medianMs
              << " ms, average: " << std::setw(10) << result.averageMs
              << " ms, result: " << (result.correct ? "OK" : "WRONG")
              << '\n';
}

}  // namespace

int main(int argc, char* argv[]) {
    std::size_t size = 1'000'000;
    std::size_t repetitions = 5;
    std::uint64_t seed = 42;

    try {
        if (argc > 1) {
            size = std::stoull(argv[1]);
        }
        if (argc > 2) {
            repetitions = std::stoull(argv[2]);
        }
        if (argc > 3) {
            seed = std::stoull(argv[3]);
        }
    } catch (const std::exception& error) {
        std::cerr << "Invalid argument: " << error.what() << '\n';
        return 1;
    }

    if (argc > 4 || repetitions == 0) {
        std::cerr << "Usage: " << argv[0]
                  << " [array_size] [repetitions] [seed]\n";
        return 1;
    }

    const std::vector<std::uint64_t> source = generateValues(size, seed);
    std::vector<std::uint64_t> expected = source;
    std::sort(expected.begin(), expected.end());

    std::cout << "Elements: " << size
              << ", repetitions: " << repetitions
              << ", seed: " << seed << "\n\n";
    std::cout << std::fixed << std::setprecision(3);

    const BenchmarkResult userResult =
        runBenchmark(LSD, source, expected, repetitions);
    const BenchmarkResult standardResult =
        runBenchmark(standardSort, source, expected, repetitions);

    printResult("userSort", userResult);
    printResult("std::sort", standardResult);

    if (userResult.correct && standardResult.correct &&
        userResult.medianMs > 0.0) {
        std::cout << "\nstd::sort / userSort median ratio: "
                  << standardResult.medianMs / userResult.medianMs << 'x'
                  << '\n';
    } else if (!userResult.correct) {
        std::cout << "\nComparison is unavailable: userSort produced a wrong "
                     "result.\n";
    }

    return userResult.correct ? 0 : 2;
}