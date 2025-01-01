class BWT {

    std::vector<uint8_t> CalculateEncodedText(const std::vector<uint8_t>& text, const std::vector<std::size_t>& suffix_array) {
        auto n = suffix_array.size();
        std::vector<uint8_t> result;
        result.reserve(n);

        for (const auto& i : suffix_array) {
            // Это последний байт в каждом циклическом сдвиге.
            uint8_t last_byte = text[(i + (n - 1)) % n];
            // result.push_back(last_byte == '\0' ? '$' : last_byte);   // На 3
            result.push_back(last_byte);                             // На 5
        }
        return result;
    }

    // size_t CalculateEncodedIndex5(const std::vector<std::size_t>& suffix_array) {
    //     return std::find(suffix_array.begin(), suffix_array.end(), 0) - suffix_array.begin();
    // }
    size_t CalculateEncodedIndex(const std::vector<uint8_t>& encoded) {
        return std::find(encoded.begin(), encoded.end(), 0) - encoded.begin();
    }

    std::vector<size_t> GetDecodingPermutation(const std::vector<uint8_t>& first, const std::vector<uint8_t>& last) {
        std::array<size_t, kAlphabetSize> counter;
        std::vector<size_t> result;
        result.reserve(first.size());

        assert(first.size() > 0);
        assert(first.size() == last.size());

        for (size_t i = 0; i < first.size(); ++i) {
            uint8_t byte = first[i];
            counter[byte] = i;
        }

        for (ssize_t i = first.size() - 1; i >= 0; --i) {
            uint8_t byte = last[i];
            result[counter[byte]--] = i;
        }
        return result;
    }

    std::vector<int32_t> ConvertToVectorWithSentinel(const std::vector<uint8_t>& text) {
        std::vector<int32_t> result(text.begin(), text.end());
        // result.push_back(-1);
        return result;
    }

public:

    std::vector<uint8_t> Encode(const std::vector<uint8_t>& text) {
        SuffixArray suffix_array_factory(ConvertToVectorWithSentinel(text));
        const auto& suffix_array = suffix_array_factory.get_suffix_array();

        // assert(text.size() + 1 == suffix_array.size()); // для байт
        assert(text.size() == suffix_array.size());

        return CalculateEncodedText(text, suffix_array);
    }

    std::vector<uint8_t> Decode(const std::vector<uint8_t>& encoded) {
        auto first = CountSort(encoded);
        auto last = encoded;

        auto permutation = GetDecodingPermutation(first, last);

        // Это в случае с заданием на 3
        size_t index = CalculateEncodedIndex(encoded);
        std::vector<uint8_t> result;
        result.reserve(first.size());

        result.push_back(first[index]);
        for (size_t i = 0; i < first.size() - 2; ++i) { // вот здесь мб проблема с индексом будет
            index = permutation[index];
            result.push_back(first[index]);
        }

        return result;
    }
};