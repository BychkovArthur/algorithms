#include <gtest/gtest.h>
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include "string.hpp"

using std::pair;
using paircc = std::pair<const char*, const char*>;

class StringEqualityParametrTest : public ::testing::TestWithParam<
                                        pair<paircc, bool>
                                        > {};

TEST_P(StringEqualityParametrTest, equal) {
    // arrange
    auto input = GetParam();
    bool correct_result = input.second;
    String str1(input.first.first);
    String str2(input.first.second);

    // act
    bool test_result = (str1 == str2);  

    // assert
    ASSERT_EQ(test_result, correct_result);

}

INSTANTIATE_TEST_CASE_P(
        StringEqualityTest,
        StringEqualityParametrTest,
        ::testing::Values(
            pair<paircc, bool>{paircc{"aaa", "aaa"}, true},
            pair<paircc, bool>{paircc{"aaaa", "aaa"}, false},
            pair<paircc, bool>{paircc{"abcd", "abcd"}, true},
            pair<paircc, bool>{paircc{"abcde", "accde"}, false},
            pair<paircc, bool>{paircc{"", ""}, true},
            pair<paircc, bool>{paircc{"abc", ""}, false}
        ));


class StringNotEqualityParametrTest : public ::testing::TestWithParam<
                                        pair<paircc, bool>
                                        > {};

TEST_P(StringNotEqualityParametrTest, not_equal) {
    // arrange
    auto input = GetParam();
    bool correct_result = input.second;
    String str1(input.first.first);
    String str2(input.first.second);

    // act
    bool test_result = (str1 != str2);  

    // assert
    ASSERT_EQ(test_result, correct_result);

}

INSTANTIATE_TEST_CASE_P(
        StringNotEqualityTest,
        StringNotEqualityParametrTest,
        ::testing::Values(
            pair<paircc, bool>{paircc{"aaa", "aaa"}, false},
            pair<paircc, bool>{paircc{"aaaa", "aaa"}, true},
            pair<paircc, bool>{paircc{"abcd", "abcd"}, false},
            pair<paircc, bool>{paircc{"abcde", "accde"}, true},
            pair<paircc, bool>{paircc{"", ""}, false},
            pair<paircc, bool>{paircc{"abc", ""}, true}
        ));


class StringLowerThanParametrTest : public ::testing::TestWithParam<
                                        pair<paircc, bool>
                                        > {};


TEST_P(StringLowerThanParametrTest, lower_than) {
    // arrange
    auto input = GetParam();
    bool correct_result = input.second;
    String str1(input.first.first);
    String str2(input.first.second);

    // act
    bool test_result = (str1 < str2);  

    // assert
    ASSERT_EQ(test_result, correct_result);

}

INSTANTIATE_TEST_CASE_P(
        StringLowerThanTest,
        StringLowerThanParametrTest,
        ::testing::Values(
            pair<paircc, bool>{paircc{"aaa", "aaa"}, false},
            pair<paircc, bool>{paircc{"aaaa", "aaa"}, false},
            pair<paircc, bool>{paircc{"aaaa", "aaaaa"}, true},
            pair<paircc, bool>{paircc{"abcd", "abcd"}, false},
            pair<paircc, bool>{paircc{"abcde", "accde"}, true},
            pair<paircc, bool>{paircc{"accde", "abcde"}, false},
            pair<paircc, bool>{paircc{"", ""}, false},
            pair<paircc, bool>{paircc{"abc", ""}, false},
            pair<paircc, bool>{paircc{"", "aaa"}, true}
        ));


class StringGreaterThanParametrTest : public ::testing::TestWithParam<
                                        pair<paircc, bool>
                                        > {};


TEST_P(StringGreaterThanParametrTest, greater_than) {
    // arrange
    auto input = GetParam();
    bool correct_result = input.second;
    String str1(input.first.first);
    String str2(input.first.second);

    // act
    bool test_result = (str1 > str2);  

    // assert
    ASSERT_EQ(test_result, correct_result);

}

INSTANTIATE_TEST_CASE_P(
        StringGreaterThanTest,
        StringGreaterThanParametrTest,
        ::testing::Values(
            pair<paircc, bool>{paircc{"aaa", "aaa"}, false},
            pair<paircc, bool>{paircc{"aaaa", "aaa"}, true},
            pair<paircc, bool>{paircc{"aaaa", "aaaaa"}, false},
            pair<paircc, bool>{paircc{"abcd", "abcd"}, false},
            pair<paircc, bool>{paircc{"abcde", "accde"}, false},
            pair<paircc, bool>{paircc{"accde", "abcde"}, true},
            pair<paircc, bool>{paircc{"", ""}, false},
            pair<paircc, bool>{paircc{"abc", ""}, true},
            pair<paircc, bool>{paircc{"", "aaa"}, false}
        ));

class StringLowerThanEqParametrTest : public ::testing::TestWithParam<
                                        pair<paircc, bool>
                                        > {};


TEST_P(StringLowerThanEqParametrTest, greater_than) {
    // arrange
    auto input = GetParam();
    bool correct_result = input.second;
    String str1(input.first.first);
    String str2(input.first.second);

    // act
    bool test_result = (str1 <= str2);  

    // assert
    ASSERT_EQ(test_result, correct_result);
}

INSTANTIATE_TEST_CASE_P(
        StringLowerThanEqTest,
        StringLowerThanEqParametrTest,
        ::testing::Values(
            pair<paircc, bool>{paircc{"aaa", "aaa"}, true},
            pair<paircc, bool>{paircc{"aaaa", "aaa"}, false},
            pair<paircc, bool>{paircc{"aaaa", "aaaaa"}, true},
            pair<paircc, bool>{paircc{"abcd", "abcd"}, true},
            pair<paircc, bool>{paircc{"abcde", "accde"}, true},
            pair<paircc, bool>{paircc{"accde", "abcde"}, false},
            pair<paircc, bool>{paircc{"", ""}, true},
            pair<paircc, bool>{paircc{"abc", ""}, false},
            pair<paircc, bool>{paircc{"", "aaa"}, true}
        ));


class StringGreaterThanEqParametrTest : public ::testing::TestWithParam<
                                        pair<paircc, bool>
                                        > {};


TEST_P(StringGreaterThanEqParametrTest, greater_than) {
    // arrange
    auto input = GetParam();
    bool correct_result = input.second;
    String str1(input.first.first);
    String str2(input.first.second);

    // act
    bool test_result = (str1 >= str2);  

    // assert
    ASSERT_EQ(test_result, correct_result);

}

INSTANTIATE_TEST_CASE_P(
        StringGreaterThanEqTest,
        StringGreaterThanEqParametrTest,
        ::testing::Values(
            pair<paircc, bool>{paircc{"aaa", "aaa"}, true},
            pair<paircc, bool>{paircc{"aaaa", "aaa"}, true},
            pair<paircc, bool>{paircc{"aaaa", "aaaaa"}, false},
            pair<paircc, bool>{paircc{"abcd", "abcd"}, true},
            pair<paircc, bool>{paircc{"abcde", "accde"}, false},
            pair<paircc, bool>{paircc{"accde", "abcde"}, true},
            pair<paircc, bool>{paircc{"", ""}, true},
            pair<paircc, bool>{paircc{"abc", ""}, true},
            pair<paircc, bool>{paircc{"", "aaa"}, false}
        ));


TEST(Constructors, default_constructor) {
    // arrange
    String str;

    // assert
    ASSERT_EQ(str.size(), 0);
    ASSERT_EQ(str.length(), 0);
    ASSERT_EQ(str.capacity(), 15);
    ASSERT_EQ(str[0], '\0');
}

TEST(Constructors, c_str_constructor1) {
    // arrange
    char c_str[] = "Test string";
    size_t len = strlen(c_str);
    String str("Test string");

    // assert
    for (size_t i = 0; i < len; ++i) {
        ASSERT_EQ(str[i], c_str[i]);
    }
    ASSERT_EQ(str.size(), 11);
    ASSERT_EQ(str.length(), 11);
    ASSERT_EQ(str.capacity(), 11);
    ASSERT_EQ(str[11], '\0');
}

TEST(Constructors, c_str_constructor2) {
    // arrange
    String str("");

    // assert
    ASSERT_EQ(str.size(), 0);
    ASSERT_EQ(str.length(), 0);
    ASSERT_EQ(str.capacity(), 0);
    ASSERT_EQ(str[0], '\0');
}


TEST(Constructors, n_chars_constructor1) {
    // arrange
    String str(0, 'c');

    // assert
    ASSERT_EQ(str.size(), 0);
    ASSERT_EQ(str.length(), 0);
    ASSERT_EQ(str.capacity(), 0);
    ASSERT_EQ(str[0], '\0');
}

TEST(Constructors, n_chars_constructor2) {
    // arrange
    String str(5, 'c');

    // assert
    for (size_t i = 0; i < 5; ++i) {
        ASSERT_EQ(str[i], 'c');
    }
    ASSERT_EQ(str.size(), 5);
    ASSERT_EQ(str.length(), 5);
    ASSERT_EQ(str.capacity(), 5);
    ASSERT_EQ(str[5], '\0');
}

TEST(Constructors, copy_constructor1) {
    // arrange
    String str(5, 'c');

    // act
    String copy(str);

    // assert
    for (size_t i = 0; i < 5; ++i) {
        ASSERT_EQ(copy[i], 'c');
    }
    ASSERT_TRUE(copy == str);
    ASSERT_EQ(str.size(), 5);
    ASSERT_EQ(str.length(), 5);
    ASSERT_EQ(str.capacity(), 5);
    ASSERT_EQ(str[5], '\0');
}

TEST(Constructors, copy_constructor2) {
    // arrange
    String str;

    // act
    String copy(str);

    // assert
    ASSERT_TRUE(copy == str);
    ASSERT_EQ(str.size(), 0);
    ASSERT_EQ(str.length(), 0);
    ASSERT_EQ(str.capacity(), 15);
    ASSERT_EQ(str[0], '\0');
}



int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}