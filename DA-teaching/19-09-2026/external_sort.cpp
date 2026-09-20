#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <iostream>


static constexpr const char* FILE_NAME = "./data/input.txt";
static constexpr size_t CHUNK_SIZE = 100'000;  // 0.8 МБ
static constexpr const char* CHUNK_PREFIX = "./data/tmp/output_chunk_";
static constexpr const char* OUTPUT_FILE = "./data/external_sort.txt";


/*
    NOTE: Эта функция предполагает, что n во входных данных отсутствует.
    Т.е. если первым числом будет идти количество элементов (n), то это n
    воспримется, как обычный элемент и будет сортиться
*/
std::vector<std::string> SplitToChunks() {
    std::ifstream ifs(FILE_NAME);
    std::vector<int64_t> buffer;
    std::vector<std::string> chunkNames;
    buffer.reserve(CHUNK_SIZE);

    size_t outputChunkNumber = 0;
    int64_t x;
    while (ifs >> x) {
        buffer.push_back(x);

        if (buffer.size() == CHUNK_SIZE) {
            std::sort(buffer.begin(), buffer.end());
            // "./data/tmp/output_chunk_i"
            std::string chunkName = std::string(CHUNK_PREFIX) + std::to_string(outputChunkNumber++);
            chunkNames.push_back(chunkName);
            std::ofstream ofs(chunkName);

            if (!ofs.is_open()) {
                throw std::runtime_error("File " + chunkName + " was not opened");
            }

            for (auto elem : buffer) {
                ofs << elem << ' ';
            }
            buffer.clear();
        }
    }

    if (!buffer.empty()) {
        std::sort(buffer.begin(), buffer.end());
        std::string chunkName = std::string(CHUNK_PREFIX) + std::to_string(outputChunkNumber++);
        chunkNames.push_back(chunkName);
        std::ofstream ofs(chunkName);

        for (auto elem : buffer) {
            ofs << elem << ' ';
        }
        buffer.clear();
    }

    return chunkNames;
}

struct THeapItem {
    int64_t x;
    size_t chunkNumber;

    THeapItem(int64_t x, size_t chunkNumber)
        : x(x)
        , chunkNumber(chunkNumber) { }


    bool operator>(const THeapItem& other) const {
        return x > other.x;
    }
};

int main() {
    const auto chunkNames = SplitToChunks();
    // streams[i] = читалка iго чанка
    std::vector<std::ifstream> streams;
    for (const auto& chunkName : chunkNames) {
        streams.emplace_back(chunkName);
    }

    std::priority_queue<
        THeapItem,
        std::vector<THeapItem>,
        std::greater<THeapItem>
    > pq;
    for (size_t i = 0; i < streams.size(); ++i) {
        int64_t x;
        streams[i] >> x;
        pq.emplace(x, i);
    }

    std::ofstream ofs(OUTPUT_FILE);
    while (!pq.empty()) {
        auto elem = pq.top();
        pq.pop();
        ofs << elem.x;
        ofs << '\n';

        int64_t newX;
        if (streams[elem.chunkNumber] >> newX) {
            pq.emplace(newX, elem.chunkNumber);
        }
    }

    return 0;
}