#include <cstddef>
#include <fstream>
#include <gtest/gtest-matchers.h>
#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <tuple>
#include <vector>

#include <utils.hpp>

#include <bitio.hpp>

#include <treap.hpp>
#include <suffix_tree.hpp>
#include <suffix_array.hpp>
#include <binary_tree.hpp>

#include <encoders/bwt.hpp>
#include <encoders/mtf.hpp>
#include <encoders/rle.hpp>
#include <encoders/huffman.hpp>

namespace {

template <typename T>
bool IsSameVectors(const std::vector<T>& lhs, const std::vector<T> rhs) {
    // std::cout << "Comparing: {" << lhs << "} and {" << rhs << "}" << std::endl;
    return lhs == rhs;
}

} // namespace

TEST(TreapTest, TestKthOrderStatistics) {
    // given
    std::vector<int64_t> values {1, 2, 15, 3, 8, 110, -18, -5, 13};

    // when
    Treap treap;
    for (const auto& value : values) {
        treap.insert(value);
    }

    // then
    ASSERT_EQ(treap.get_kth_order_statistic(1), -18);
    ASSERT_EQ(treap.get_kth_order_statistic(2), -5);
    ASSERT_EQ(treap.get_kth_order_statistic(3), 1);
    ASSERT_EQ(treap.get_kth_order_statistic(4), 2);
    ASSERT_EQ(treap.get_kth_order_statistic(5), 3);
    ASSERT_EQ(treap.get_kth_order_statistic(6), 8);
    ASSERT_EQ(treap.get_kth_order_statistic(7), 13);
    ASSERT_EQ(treap.get_kth_order_statistic(8), 15);
    ASSERT_EQ(treap.get_kth_order_statistic(9), 110);
}

class SuffixArrayParametrizedTest : public ::testing::TestWithParam< std::tuple<
                                                                        std::vector<int32_t>, std::vector<size_t>
                                                                    > > {};

TEST_P(SuffixArrayParametrizedTest, Test1) {
    // given
    const auto& input = std::get<0>(GetParam());
    const auto& expected_output = std::get<1>(GetParam());

    // when
    SuffixArray sa(input);
    const auto& actual_output = sa.GetSuffixArray();
    
    // then
    ASSERT_TRUE(IsSameVectors(actual_output, expected_output));
}

INSTANTIATE_TEST_CASE_P(
    TestCase1,
    SuffixArrayParametrizedTest,
    ::testing::Values(
        std::tuple< std::vector<int32_t>, std::vector<size_t> > {{1, 2, 3}, {0, 1, 2}},
        std::tuple< std::vector<int32_t>, std::vector<size_t> > {{1, 2, 3, 0}, {3, 0, 1, 2}},
        std::tuple< std::vector<int32_t>, std::vector<size_t> > {{1, 2, 1, 3, 1, 1, 3, 0}, {7, 4, 0, 5, 2, 1, 6, 3}},
        std::tuple< std::vector<int32_t>, std::vector<size_t> > {{1, 2, 1, 3, 1, 2, 1, 0}, {7, 6, 4, 0, 2, 5, 1, 3}},
        std::tuple< std::vector<int32_t>, std::vector<size_t> > {{}, {}},
        std::tuple< std::vector<int32_t>, std::vector<size_t> > {{1}, {0}}
    ));

class SuffixTreeParametrizedTest : public ::testing::TestWithParam< std::tuple<
        std::vector<int32_t>, std::vector<size_t>
> > {};


TEST_P(SuffixTreeParametrizedTest, Test1) {
    // given
    auto input = std::get<0>(GetParam());
    const auto& expected_output = std::get<1>(GetParam());

    // when
    input.push_back(-1);
    SuffTree st(input);
    st.Build();
    const auto& actual_output = st.BuildSuffixArray();

    // then
    ASSERT_TRUE(IsSameVectors(actual_output, expected_output));
}

INSTANTIATE_TEST_CASE_P(
        TestCase1,
        SuffixTreeParametrizedTest,
        ::testing::Values(
                std::tuple< std::vector<int32_t>, std::vector<size_t> > {{1, 2, 3}, {3, 0, 1, 2}},
                std::tuple< std::vector<int32_t>, std::vector<size_t> > {{1, 2, 3, 0}, {4, 3, 0, 1, 2}},
                std::tuple< std::vector<int32_t>, std::vector<size_t> > {{1, 2, 1, 3, 1, 1, 3, 0}, {8, 7, 4, 0, 5, 2, 1, 6, 3}},
                std::tuple< std::vector<int32_t>, std::vector<size_t> > {{1, 2, 1, 3, 1, 2, 1, 0}, {8, 7, 6, 4, 0, 2, 5, 1, 3}},
                std::tuple< std::vector<int32_t>, std::vector<size_t> > {{}, {0}},
                std::tuple< std::vector<int32_t>, std::vector<size_t> > {{1}, {1, 0}}
        ));


class BWTEncodingParametrizedTest : public ::testing::TestWithParam< std::tuple<
                                                                        std::vector<uint8_t>, BWT::Encoded
                                                                    > > {};


TEST_P(BWTEncodingParametrizedTest, Test1) {
    // given
    const auto& input = std::get<0>(GetParam());
    const auto& expected_encoded = std::get<1>(GetParam());

    // when
    BWT bwt;
    const auto encoded = bwt.Encode(input);
    
    // then
    ASSERT_EQ(encoded.index, expected_encoded.index);
    ASSERT_TRUE(IsSameVectors(encoded.text, expected_encoded.text));
}

INSTANTIATE_TEST_CASE_P(
    EncodingTest1,
    BWTEncodingParametrizedTest,
    ::testing::Values(
        std::tuple< std::vector<uint8_t>, BWT::Encoded > {{0, 2, 3}, {.text = {3, 0, 0, 2}, .index = 1}},
        std::tuple< std::vector<uint8_t>, BWT::Encoded > {{0, 3, 2}, {.text = {2, 0, 3, 0}, .index = 1}},
        std::tuple< std::vector<uint8_t>, BWT::Encoded > {{2, 0, 3}, {.text = {3, 2, 0, 0}, .index = 2}},
        std::tuple< std::vector<uint8_t>, BWT::Encoded > {{2, 3, 0}, {.text = {0, 3, 0, 2}, .index = 2}},
        std::tuple< std::vector<uint8_t>, BWT::Encoded > {{3, 2, 1}, {.text = {1, 2, 3, 0}, .index = 3}},
        std::tuple< std::vector<uint8_t>, BWT::Encoded > {{3, 1, 2}, {.text = {2, 3, 1, 0}, .index = 3}},
        std::tuple< std::vector<uint8_t>, BWT::Encoded > {{1}, {.text = {1, 0}, .index = 1}},
        std::tuple< std::vector<uint8_t>, BWT::Encoded > {{1, 2}, {.text = {2, 0, 1}, .index = 1}},
        std::tuple< std::vector<uint8_t>, BWT::Encoded > {{2, 1}, {.text = {1, 2, 0}, .index = 2}},
        std::tuple< std::vector<uint8_t>, BWT::Encoded > {{}, {.text = {0}, .index = 0}}, // Невалидная хрень. Такого не должно быть
        std::tuple< std::vector<uint8_t>, BWT::Encoded > {{1, 2, 18, 1, 12, 1, 5, 1, 2, 18, 1}, {.text = {1, 18, 5, 0, 12, 18, 1, 1, 1, 1, 2, 2}, .index = 3}}, // {1, 2, 18, 1, 12, 1, 5, 1, 2, 18, 1} = АБРАКАДАБРА, если смотреть по номерам букв
        std::tuple< std::vector<uint8_t>, BWT::Encoded > {{1, 2, 3, 1, 2, 3, 3, 3, 3, 2, 2, 2, 1, 1, 1}, {.text = {1, 1, 1, 2, 0, 3, 2, 2, 3, 1, 1, 2, 3, 3, 3, 2}, .index = 4}}
    ));


class BWTDecodingParametrizedTest : public ::testing::TestWithParam< std::tuple<
                                                                        BWT::Encoded, std::vector<uint8_t>
                                                                    > > {};


TEST_P(BWTDecodingParametrizedTest, Test1) {
    // given
    const auto& input = std::get<0>(GetParam());
    const auto& expected_decoded = std::get<1>(GetParam());

    // when
    BWT bwt;
    const auto decoded = bwt.Decode(input);

    // then
    std::cout << "Decoded: " << decoded << std::endl;
    ASSERT_TRUE(IsSameVectors(decoded, expected_decoded));
}

INSTANTIATE_TEST_CASE_P(
    DecodingTest1,
    BWTDecodingParametrizedTest,
    ::testing::Values(
        std::tuple< BWT::Encoded, std::vector<uint8_t> > {{.text = {3, 0, 0, 2}, .index = 1}, {0, 2, 3}},
        std::tuple< BWT::Encoded, std::vector<uint8_t> > {{.text = {2, 0, 3, 0}, .index = 1}, {0, 3, 2}},
        std::tuple< BWT::Encoded, std::vector<uint8_t> > {{.text = {3, 2, 0, 0}, .index = 2}, {2, 0, 3}},
        std::tuple< BWT::Encoded, std::vector<uint8_t> > {{.text = {0, 3, 0, 2}, .index = 2}, {2, 3, 0}},
        std::tuple< BWT::Encoded, std::vector<uint8_t> > {{.text = {1, 2, 3, 0}, .index = 3}, {3, 2, 1}},
        std::tuple< BWT::Encoded, std::vector<uint8_t> > {{.text = {2, 3, 1, 0}, .index = 3}, {3, 1, 2}},
        std::tuple< BWT::Encoded, std::vector<uint8_t> > {{.text = {1, 0}, .index = 1}, {1}},
        std::tuple< BWT::Encoded, std::vector<uint8_t> > {{.text = {2, 0, 1}, .index = 1}, {1, 2}},
        std::tuple< BWT::Encoded, std::vector<uint8_t> > {{.text = {1, 2, 0}, .index = 2}, {2, 1}},
//        std::tuple< BWT::Encoded, std::vector<uint8_t> > {{.text = {0}, .index = 0}, {}} // Херня тест. Такого не должно быть
        std::tuple< BWT::Encoded, std::vector<uint8_t> > {{.text = {1, 18, 5, 0, 12, 18, 1, 1, 1, 1, 2, 2}, .index = 3}, {1, 2, 18, 1, 12, 1, 5, 1, 2, 18, 1}}, // {1, 2, 18, 1, 12, 1, 5, 1, 2, 18, 1} = АБРАКАДАБРА, если смотреть по номерам букв
        std::tuple< BWT::Encoded, std::vector<uint8_t> > {{.text = {1, 1, 1, 2, 0, 3, 2, 2, 3, 1, 1, 2, 3, 3, 3, 2}, .index = 4}, {1, 2, 3, 1, 2, 3, 3, 3, 3, 2, 2, 2, 1, 1, 1}}
    ));


class MTFEncodingParametrizedTest : public ::testing::TestWithParam< std::tuple<
                                                                        std::vector<uint8_t>, std::vector<uint8_t>
                                                                    > > {};


TEST_P(MTFEncodingParametrizedTest, Test1) {
    // given
    const auto& input = std::get<0>(GetParam());
    const auto& expected_encoded = std::get<1>(GetParam());

    // when
    MTF mtf;
    const auto encoded = mtf.Encode(input);
    
    // then
    std::cout << "encode: " << encoded << std::endl;
    ASSERT_TRUE(IsSameVectors(encoded, expected_encoded));
}

INSTANTIATE_TEST_CASE_P(
    EncodingTest1,
    MTFEncodingParametrizedTest,
    ::testing::Values(
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {{1, 1, 2, 1}, {1, 0, 2, 1}},
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {{1, 1, 1, 2, 2, 1, 2, 1}, {1, 0, 0, 2, 0, 1, 1, 1}},
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {{5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 3, 3, 3, 100, 100}, {5, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 100, 0}},
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {{4, 2, 0, 3, 4, 0, 0, 0, 0, 1, 1}, {4, 3, 2, 4, 3, 2, 0, 0, 0, 4, 0}}, // РДАКРААААББ
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {{1, 0, 13, 0, 13, 0, 0, 0}, {1, 1, 13, 1, 1, 1, 0, 0}}, // bananaaa
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {{}, {}},
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {{15}, {15}},
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {{15, 15}, {15, 0}},
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {{15, 14}, {15, 15}}
    ));



class MTFDecodingParametrizedTest : public ::testing::TestWithParam< std::tuple<
                                                                        std::vector<uint8_t>, std::vector<uint8_t>
                                                                    > > {};


TEST_P(MTFDecodingParametrizedTest, Test1) {
    // given
    const auto& input = std::get<0>(GetParam());
    const auto& expected_decoded = std::get<1>(GetParam());

    // when
    MTF mtf;
    const auto decoded = mtf.Decode(input);
    
    // then
    ASSERT_TRUE(IsSameVectors(decoded, expected_decoded));
}


INSTANTIATE_TEST_CASE_P(
    DecodingTest1,
    MTFDecodingParametrizedTest,
    ::testing::Values(
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {{1, 0, 0, 2, 0, 1, 1, 1}, {1, 1, 1, 2, 2, 1, 2, 1}},
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {{5, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 100, 0}, {5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 3, 3, 3, 100, 100}},
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {{4, 3, 2, 4, 3, 2, 0, 0, 0, 4, 0}, {4, 2, 0, 3, 4, 0, 0, 0, 0, 1, 1}}, // РДАКРААААББ
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {{1, 1, 13, 1, 1, 1, 0, 0}, {1, 0, 13, 0, 13, 0, 0, 0}}, // bananaaa
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {{}, {}},
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {{15}, {15}},
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {{15, 0}, {15, 15}},
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {{15, 15}, {15, 14}}
    ));


class RLEEncodingParametrizedTest : public ::testing::TestWithParam< std::tuple<
                                                                        std::vector<uint8_t>, std::vector<RLE::Encoded>
                                                                    > > {};

TEST_P(RLEEncodingParametrizedTest, Test1) {
    // given
    const auto& input = std::get<0>(GetParam());
    const auto& expected_encoded = std::get<1>(GetParam());

    // when
    RLE rle;
    const auto encoded = rle.Encode(input);
    
    // then
    ASSERT_TRUE(IsSameVectors(encoded, expected_encoded));
}

INSTANTIATE_TEST_CASE_P(
    EncodingTest1,
    RLEEncodingParametrizedTest,
    ::testing::Values(
        std::tuple< std::vector<uint8_t>, std::vector<RLE::Encoded> > {{1, 1, 1, 1, 1}, { {.count = 5, .byte = 1} }},
        std::tuple< std::vector<uint8_t>, std::vector<RLE::Encoded> > {{1, 1, 2, 2, 2, 3, 3, 3}, { {.count = 2, .byte = 1}, {.count = 3, .byte = 2}, {.count = 3, .byte = 3} }},
        std::tuple< std::vector<uint8_t>, std::vector<RLE::Encoded> > {{1}, { {.count = 1, .byte = 1} }},
        std::tuple< std::vector<uint8_t>, std::vector<RLE::Encoded> > {{}, {}},
        std::tuple< std::vector<uint8_t>, std::vector<RLE::Encoded> > {{1, 2, 3}, { {.count = 1, .byte = 1}, {.count = 1, .byte = 2}, {.count = 1, .byte = 3} }}
    ));


class RLEDecodingParametrizedTest : public ::testing::TestWithParam< std::tuple<
                                                                        std::vector<RLE::Encoded>, std::vector<uint8_t>
                                                                    > > {};


TEST_P(RLEDecodingParametrizedTest, Test1) {
    // given
    const auto& input = std::get<0>(GetParam());
    const auto& expected_decoded = std::get<1>(GetParam());

    // when
    RLE rle;
    const auto decoded = rle.Decode(input);
    
    // then
    ASSERT_TRUE(IsSameVectors(decoded, expected_decoded));
}


INSTANTIATE_TEST_CASE_P(
    DecodingTest1,
    RLEDecodingParametrizedTest,
    ::testing::Values(
        std::tuple< std::vector<RLE::Encoded>, std::vector<uint8_t> > {{ {.count = 5, .byte = 1} }, {1, 1, 1, 1, 1}},
        std::tuple< std::vector<RLE::Encoded>, std::vector<uint8_t> > {{ {.count = 2, .byte = 1}, {.count = 3, .byte = 2}, {.count = 3, .byte = 3} }, {1, 1, 2, 2, 2, 3, 3, 3}},
        std::tuple< std::vector<RLE::Encoded>, std::vector<uint8_t> > {{ {.count = 1, .byte = 1} }, {1}},
        std::tuple< std::vector<RLE::Encoded>, std::vector<uint8_t> > {{}, {}},
        std::tuple< std::vector<RLE::Encoded>, std::vector<uint8_t> > {{ {.count = 1, .byte = 1}, {.count = 1, .byte = 2}, {.count = 1, .byte = 3} }, {1, 2, 3}}
    ));


TEST(BinaryTreeTests, ShouldSerialize1) {
    /* given   -2(c)
     *        /    \
     *       1   -2(b)
     *           /    \
     *          -2(a)  4
     *          /   \  
     *         2     3
     */
    auto node_a = std::make_unique<BinaryTree::Node>();
    node_a->left = std::make_unique<BinaryTree::Node>(2);
    node_a->right = std::make_unique<BinaryTree::Node>(3);

    auto node_b = std::make_unique<BinaryTree::Node>();
    node_b->left = std::move(node_a);
    node_b->right = std::make_unique<BinaryTree::Node>(4);

    auto node_c = std::make_unique<BinaryTree::Node>();
    node_c->left = std::make_unique<BinaryTree::Node>(1);
    node_c->right = std::move(node_b);

    BinaryTree tree(std::move(node_c));

    // when
    const auto serialized = Serialize(tree);

    // then
    ASSERT_TRUE(IsSameVectors(serialized, {-2, 1, -1, -1, -2, -2, 2, -1, -1, 3, -1, -1, 4, -1, -1}));
}

TEST(BinaryTreeTests, ShouldSerialize2) {
    /* given   -2(d)
     *         /   \
     *      -2(c)   0
     *      /   \
     *   -2(a) -2(b)
     *    /  \  /  \
     *   1   2 3   4
     */
    auto node_a = std::make_unique<BinaryTree::Node>();
    node_a->left = std::make_unique<BinaryTree::Node>(1);
    node_a->right = std::make_unique<BinaryTree::Node>(2);

    auto node_b = std::make_unique<BinaryTree::Node>();
    node_b->left = std::make_unique<BinaryTree::Node>(3);
    node_b->right = std::make_unique<BinaryTree::Node>(4);

    auto node_c = std::make_unique<BinaryTree::Node>();
    node_c->left = std::move(node_a);
    node_c->right = std::move(node_b);

    auto node_d = std::make_unique<BinaryTree::Node>();
    node_d->left = std::move(node_c);
    node_d->right = std::make_unique<BinaryTree::Node>(0);

    BinaryTree tree(std::move(node_d));

    // when
    const auto serialized = Serialize(tree);

    // then
    ASSERT_TRUE(IsSameVectors(serialized, {-2, -2, -2, 1, -1, -1, 2, -1, -1, -2, 3, -1, -1, 4, -1, -1, 0, -1, -1}));
}

TEST(BinaryTreeTests, ShouldNotSerializeCauseTreeIsEmpty) {
    // given
    BinaryTree tree(nullptr);
    std::vector<int16_t> serialized;

    // when && then
    try {
        serialized = Serialize(tree);
        FAIL() << "Expected std::logic_error";

    } catch (const std::logic_error& ex) {
        ASSERT_EQ(ex.what(), std::string("nullptr as current node in PreOrderTraversal"));
    
    } catch (...) {
        FAIL() << "Expected std::logic_error";
    }
}

TEST(BinaryTreeTests, ShouldNotSerializeCauseTreeIs) {
    /* given   -2(d)
     *         /   \
     *      -2(c)   0
     *      /   \
     *   -2(a) -2(b)
     *    /  \  /  \
     *   1   2 3  NULL
     */
    auto node_a = std::make_unique<BinaryTree::Node>();
    node_a->left = std::make_unique<BinaryTree::Node>(1);
    node_a->right = std::make_unique<BinaryTree::Node>(2);

    auto node_b = std::make_unique<BinaryTree::Node>();
    node_b->left = std::make_unique<BinaryTree::Node>(3);
    node_b->right = nullptr;

    auto node_c = std::make_unique<BinaryTree::Node>();
    node_c->left = std::move(node_a);
    node_c->right = std::move(node_b);

    auto node_d = std::make_unique<BinaryTree::Node>();
    node_d->left = std::move(node_c);
    node_d->right = std::make_unique<BinaryTree::Node>(0);

    BinaryTree tree(std::move(node_d));
    std::vector<int16_t> serialized;

    // when && then
    try {
        serialized = Serialize(tree);
        FAIL() << "Expected std::logic_error";

    } catch (const std::logic_error& ex) {
        ASSERT_EQ(ex.what(), std::string("Node with value 0 has only one child!\nleft_child_value: 3, right_child_value: -1"));
    
    } catch (...) {
        FAIL() << "Expected std::logic_error";
    }
}

TEST(BinaryTreeTests, ShouldDesirialize1) {
    /* given   -2(c)  serialized into file
     *        /    \
     *       1   -2(b)
     *           /    \
     *          -2(a)  4
     *          /   \  
     *         2     3
     */
    std::ifstream ifs("../test/static/encoded_test1.out", std::ios::binary);
    if (!ifs.is_open()) {
        FAIL() << "File not opened";
    }


    // when
    const auto deserialized = Deserialize(ifs);
    const auto serialized = Serialize(deserialized);

    // then
    ASSERT_TRUE(IsSameVectors(serialized, {-2, 1, -1, -1, -2, -2, 2, -1, -1, 3, -1, -1, 4, -1, -1}));
}


TEST(BinaryTreeTests, ShouldDesirialize2) {
    /* given   -2(d) serialized into file
     *         /   \
     *      -2(c)   0
     *      /   \
     *   -2(a) -2(b)
     *    /  \  /  \
     *   1   2 3  NULL
     */
    std::ifstream ifs("../test/static/encoded_test2.out", std::ios::binary);
    if (!ifs.is_open()) {
        FAIL() << "File not opened";
    }


    // when
    const auto deserialized = Deserialize(ifs);
    const auto serialized = Serialize(deserialized);

    // then
    ASSERT_TRUE(IsSameVectors(serialized, {-2, -2, -2, 1, -1, -1, 2, -1, -1, -2, 3, -1, -1, 4, -1, -1, 0, -1, -1}));
}


class HuffmanEncodingParametrizedTest : public ::testing::TestWithParam< std::tuple<
                                                                        std::vector<uint8_t>, std::vector<int16_t>, std::vector<uint8_t>, uint8_t
                                                                    > > {};


TEST_P(HuffmanEncodingParametrizedTest, Test1) {
    // given
    const auto& input = std::get<0>(GetParam());
    const auto& expected_serialized_model = std::get<1>(GetParam());
    const auto& expected_encoded = std::get<2>(GetParam());
    const auto& expected_alignment = std::get<3>(GetParam());

    // when
    Huffman huffman;
    const auto encoded = huffman.Encode(input);
    const auto serialized_model = Serialize(encoded.model);
    
    // then
    ASSERT_TRUE(IsSameVectors(encoded.text, expected_encoded));
    ASSERT_TRUE(IsSameVectors(serialized_model, expected_serialized_model));
    ASSERT_EQ(encoded.alignment, expected_alignment);
}

INSTANTIATE_TEST_CASE_P(
    EncodingTest1,
    HuffmanEncodingParametrizedTest,
    ::testing::Values(
        std::tuple< std::vector<uint8_t>, std::vector<int16_t>, std::vector<uint8_t>, uint8_t > {
                        {0, 1, 18, 0, 12, 0, 5, 0, 1, 18, 0},
                        {-2, 0, -1, -1, -2, -2, 5, -1, -1, 12, -1, -1, -2, 1, -1, -1, 18, -1, -1},
                        {0b01101110, 0b10101000, 0b11011100},
                        1
        }, // АБРАКАДАБРА
        std::tuple< std::vector<uint8_t>, std::vector<int16_t>, std::vector<uint8_t>, uint8_t > {
                        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2},
                        {-2, 2, -1, -1, -2, 0, -1, -1, 1, -1, -1},
                        {0b10101010, 0b10111111, 0b11110000, 0b0000000},
                        7
        }, // AAAAABBBBBCCCCC 
        std::tuple< std::vector<uint8_t>, std::vector<int16_t>, std::vector<uint8_t>, uint8_t > {
                        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                        {-2, 2, -1, -1, -2, 0, -1, -1, 1, -1, -1},
                        {0b10101010, 0b10111111, 0b11110000, 0b0000000},
                        0
        }, // AAAAABBBBBCCCCCCCCCCCC
        std::tuple< std::vector<uint8_t>, std::vector<int16_t>, std::vector<uint8_t>, uint8_t > {
                {1, 1, 1, 2, 2, 2, 3, 3, 3},
                {-2, 3, -1, -1, -2, 1, -1, -1, 2, -1, -1},
                {0b10101011, 0b11110000},
                1
        } // 111222333
    ));


TEST(HuffmanEncodingTest, ShouldThrowErrorWhenInputIsEmpty) {
    // given
    const auto& input = std::vector<uint8_t>{};

    // when && then
    Huffman huffman;
    try {
        const auto encoded = huffman.Encode(input);

    } catch (const std::logic_error& ex) {
        ASSERT_EQ(ex.what(), std::string("Input text is empty"));
    
    } catch (...) {
        FAIL() << "Expected std::logic_error";
    }
}

TEST(HuffmanEncodingTest, ShouldThrowErrorTextContainsOnlyOneDifferentByte) {
    // given
    const auto& input = std::vector<uint8_t>{0x11, 0x11, 0x11, 0x11};

    // when && then
    Huffman huffman;
    try {
        const auto encoded = huffman.Encode(input);

    } catch (const std::logic_error& ex) {
        ASSERT_EQ(ex.what(), std::string("Invalid input text. It's contains only 1 different byte"));
    
    } catch (...) {
        FAIL() << "Expected std::logic_error";
    }
}

class HuffmanDecodingParametrizedTest : public ::testing::TestWithParam< std::tuple<
                                                                        std::vector<uint8_t>, std::string, uint8_t, std::vector<uint8_t>
                                                                    > > {};

TEST_P(HuffmanDecodingParametrizedTest, Test1) {
    // given
    const auto& encoded_text = std::get<0>(GetParam());
    const auto& filename = std::get<1>(GetParam());
    const auto& alignment = std::get<2>(GetParam());
    const auto& expected_decoded = std::get<3>(GetParam());

    // when
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs.is_open()) {
        FAIL() << "File not opened";
    }
    auto tree = Deserialize(ifs);
    Huffman huffman;
    Huffman::Encoded huffman_encoded{
        .model = std::move(tree),
        .text = encoded_text,
        .alignment = alignment
    };
    const auto& decoded = huffman.Decode(huffman_encoded);
    
    // then
    ASSERT_TRUE(IsSameVectors(decoded, expected_decoded));
}


INSTANTIATE_TEST_CASE_P(
    DecodingTest1,
    HuffmanDecodingParametrizedTest,
    ::testing::Values(
        std::tuple< std::vector<uint8_t>, std::string, uint8_t, std::vector<uint8_t> > {
                        {0b01101110, 0b10101000, 0b11011100},
                        "../test/static/serialized_abracadabra.bin",
                        1,
                        {0, 1, 18, 0, 12, 0, 5, 0, 1, 18, 0}
        }, // АБРАКАДАБРА
        std::tuple< std::vector<uint8_t>, std::string, uint8_t, std::vector<uint8_t> > {
                        {0b10101010, 0b10111111, 0b11110000, 0b0000000},
                        "../test/static/serialized_abc.bin",
                        7,
                        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2}
        }, // AAAAABBBBBCCCCC
        std::tuple< std::vector<uint8_t>, std::string, uint8_t, std::vector<uint8_t> > {
                        {0b10101010, 0b10111111, 0b11110000, 0b0000000},
                        "../test/static/serialized_abc.bin",
                        0,
                        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
        } // AAAAABBBBBCCCCCCCCCCCC
    ));


class BitIOOutputParametrizedTest : public ::testing::TestWithParam< std::tuple<
                                                                        std::vector<uint8_t>, std::vector<uint8_t>
                                                                    > > {};


TEST_P(BitIOOutputParametrizedTest, Test1) {
    // given
    const auto& input = std::get<0>(GetParam());
    const auto& expected_output = std::get<1>(GetParam());
    std::vector<uint8_t> output;

    // when
    BitIO stream(output);
    for (const auto& bit : input) {
        if (bit == 0) {
            stream.Write(BitIO::Bit::kZero);
        } else {
            stream.Write(BitIO::Bit::kOne);
        }
    }
    stream.FlushOutput();
    
    // then
    ASSERT_TRUE(IsSameVectors(output, expected_output));
}

INSTANTIATE_TEST_CASE_P(
    OutputTest1,
    BitIOOutputParametrizedTest,
    ::testing::Values(
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {
                        {1, 0, 1, 0, 1, 0, 1, 0},
                        {0b10101010},
        },
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {
                        {0, 0, 1, 0, 1, 0, 1, 0},
                        {0b00101010},
        },
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {
                        {1, 1, 1, 0, 1, 0, 1, 1},
                        {0b11101011},
        },
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {
                        {1},
                        {0b10000000},
        },
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {
                        {0},
                        {0b00000000},
        },
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {
                        {1, 1, 1, 1, 1, 1, 1, 1, 1},
                        {0b11111111, 0b10000000},
        },
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {
                        {},
                        {},
        }
    ));


class BitIOInputParametrizedTest : public ::testing::TestWithParam< std::tuple<
                                                                        std::vector<uint8_t>, std::vector<uint8_t>
                                                                    > > {};

TEST_P(BitIOInputParametrizedTest, Test1) {
    // given
    auto input = std::get<0>(GetParam());
    const auto& expected = std::get<1>(GetParam());

    // when
    BitIO stream(input);
    std::vector<uint8_t> readed;
    while (!stream.Eof()){
        const auto bit = stream.Read();
        readed.push_back(bit == BitIO::Bit::kZero ? 0 : 1);
    }

    // then
    ASSERT_TRUE(IsSameVectors(readed, expected));
}

INSTANTIATE_TEST_CASE_P(
    InputTest1,
    BitIOInputParametrizedTest,
    ::testing::Values(
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {
                        {173, 15, 23},
                        {1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1},
        },
        std::tuple< std::vector<uint8_t>, std::vector<uint8_t> > {
                        {111, 0, 1},
                        {0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        }
    ));