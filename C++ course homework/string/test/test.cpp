#include <gtest/gtest.h>
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include "string.hpp"

using std::pair;
using std::string;
using paircc = std::pair<const char*, const char*>;
using pairss = std::pair<size_t, size_t>;


bool operator==(const String& str1, const string& str2) {
    return str1.size() == str2.size() && !std::memcmp(str1.data(), str2.data(), str1.size());
}

bool operator==(const string& str1, const String& str2) {
    return str1.size() == str2.size() && !std::memcmp(str1.data(), str2.data(), str1.size());
}


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


class StringLeftFindParametrTest : public ::testing::TestWithParam<
                                        pair<paircc, size_t>
                                        > {};


TEST_P(StringLeftFindParametrTest, left_find) {
    // arrange
    auto input = GetParam();
    size_t correct_result = input.second;
    String str1(input.first.first);
    String str2(input.first.second);

    // act
    size_t test_result =  str1.find(str2);

    // assert
    ASSERT_EQ(test_result, correct_result);

}

INSTANTIATE_TEST_CASE_P(
        StringLeftFindTest,
        StringLeftFindParametrTest,
        ::testing::Values(
            pair<paircc, size_t>{paircc{"aaa", "aaa"}, 0},
            pair<paircc, size_t>{paircc{"aaaa", "aaa"}, 0},
            pair<paircc, size_t>{paircc{"aaaa", "aaaaa"}, 4},
            pair<paircc, size_t>{paircc{"abcd", "abcd"}, 0},
            pair<paircc, size_t>{paircc{"abcde", "accde"}, 5},
            pair<paircc, size_t>{paircc{"ccbaccba", "ba"}, 2},
            pair<paircc, size_t>{paircc{"", ""}, 0},
            pair<paircc, size_t>{paircc{"abc", ""}, 0},
            pair<paircc, size_t>{paircc{"", "aaa"}, 0},
            pair<paircc, size_t>{paircc{"asdfasdfaboba", "aboba"}, 8},
            pair<paircc, size_t>{paircc{"asdfasdfabobac", "c"}, 13},
            pair<paircc, size_t>{paircc{"asdfasdfabobac", "a"}, 0}
        ));



class StringRightFindParametrTest : public ::testing::TestWithParam<
                                        pair<paircc, size_t>
                                        > {};


TEST_P(StringRightFindParametrTest, right_find) {
    // arrange
    auto input = GetParam();
    size_t correct_result = input.second;
    String str1(input.first.first);
    String str2(input.first.second);

    // act
    size_t test_result =  str1.rfind(str2);

    // assert
    ASSERT_EQ(test_result, correct_result);

}

INSTANTIATE_TEST_CASE_P(
        StringRightFindTest,
        StringRightFindParametrTest,
        ::testing::Values(
            pair<paircc, size_t>{paircc{"aaa", "aaa"}, 0},
            pair<paircc, size_t>{paircc{"aaaa", "aaa"}, 1},
            pair<paircc, size_t>{paircc{"aboba", "aboba"}, 0},
            pair<paircc, size_t>{paircc{"cccaboba", "aboba"}, 3},
            pair<paircc, size_t>{paircc{"ccabobacccabob", "aboba"}, 2},
            pair<paircc, size_t>{paircc{"abobacccabob", "aboba"}, 0},
            pair<paircc, size_t>{paircc{"accca", "a"}, 4},
            pair<paircc, size_t>{paircc{"accc", "a"}, 0},
            pair<paircc, size_t>{paircc{"acacc", "a"}, 2},
            pair<paircc, size_t>{paircc{"acacc", ""}, 5},
            pair<paircc, size_t>{paircc{"", ""}, 0},
            pair<paircc, size_t>{paircc{"", "abasdf"}, 0}
        ));

class StringSubstrParametrTest : public ::testing::TestWithParam<
                                        pair<const char*, pairss>
                                        > {};


TEST_P(StringSubstrParametrTest, substr) {
    // arrange
    auto input = GetParam();
    String source1(input.first);
    string source2(input.first);
    size_t start_ind = input.second.first;
    size_t count = input.second.second;

    // act
    String test_result = source1.substr(start_ind, count);
    string correct_result = source2.substr(start_ind, count);

    // assert
    ASSERT_EQ(test_result, correct_result);
}

INSTANTIATE_TEST_CASE_P(
        StringSubstrTest,
        StringSubstrParametrTest,
        ::testing::Values(
            pair<const char*, pairss>{"aboba", pairss{0, 2}},
            pair<const char*, pairss>{"aboba", pairss{1, 2}},
            pair<const char*, pairss>{"aboba", pairss{2, 2}},
            pair<const char*, pairss>{"aboba", pairss{3, 2}},
            pair<const char*, pairss>{"aboba", pairss{4, 2}},
            pair<const char*, pairss>{"aboba", pairss{0, 200}},
            pair<const char*, pairss>{"a", pairss{0, 1}},
            pair<const char*, pairss>{"a", pairss{0, 100}},
            pair<const char*, pairss>{"a", pairss{0, 0}}
        ));


TEST(PushBackTest, push_back1) {
    // arrange
    String str(3, 'a');

    // act
    for (size_t i = 0; i < 12; ++i) {
        str.push_back('b');
    }

    // assert
    ASSERT_EQ(str.size(), 15);
    ASSERT_EQ(str.length(), 15);
    ASSERT_EQ(str.capacity(), 15);
    ASSERT_EQ(str, "aaabbbbbbbbbbbb");
}

TEST(PushBackTest, push_back2) {
    // arrange
    String str(3, 'a');

    // act
    for (size_t i = 0; i < 12; ++i) {
        str.push_back('b');
    }
    str.push_back('c');

    // assert
    ASSERT_EQ(str.size(), 16);
    ASSERT_EQ(str.length(), 16);
    ASSERT_EQ(str.capacity(), 31);
    ASSERT_EQ(str, "aaabbbbbbbbbbbbc");
}


TEST(PopBackTest, pop_back1) {
    // arrange
    String str("Hello World!");

    // act
    for (size_t i = 0; i < 5; ++i) {
        str.pop_back();
    }
    

    // assert
    ASSERT_EQ(str.size(), 7);
    ASSERT_EQ(str.length(), 7);
    ASSERT_EQ(str.capacity(), 12);
    ASSERT_EQ(str, "Hello W");
}


TEST(PopBackTest, pop_back2) {
    // arrange
    String str("Hello World!");

    // act
    for (size_t i = 0; i < 12; ++i) {
        str.pop_back();
    }
    

    // assert
    ASSERT_EQ(str.size(), 0);
    ASSERT_EQ(str.length(), 0);
    ASSERT_EQ(str.capacity(), 12);
    ASSERT_EQ(str, "");
}

TEST(PopBackTest, pop_back3) {
    // arrange
    String str("Hello World!");

    // act
    for (size_t i = 0; i < 11; ++i) {
        str.pop_back();
    }
    

    // assert
    ASSERT_EQ(str.size(), 1);
    ASSERT_EQ(str.length(), 1);
    ASSERT_EQ(str.capacity(), 12);
    ASSERT_EQ(str, "H");
}

TEST(AssigmentOperator, assigment_operator) {
    // arrange
    String str1("Hello World!");
    String str2(10, 'c');
    String str3;

    // act
    String test1, test2, test3;
    test1 = str1;
    test2 = str2;
    test3 = str3;
    test1 = test1;
    
    // assert
    ASSERT_EQ(test1.capacity(), str1.capacity());
    ASSERT_EQ(test1, str1);
    ASSERT_EQ(test2.capacity(), str2.capacity());
    ASSERT_EQ(test2, str2);
    ASSERT_EQ(test3.capacity(), str3.capacity());
    ASSERT_EQ(test3, str3);
}

TEST(AdditionalAssigmentOperatorTest, add_assigment_char1) {
    // arrange
    String str(3, 'a');

    // act
    for (size_t i = 0; i < 12; ++i) {
        str += 'b';
    }

    // assert
    ASSERT_EQ(str.size(), 15);
    ASSERT_EQ(str.length(), 15);
    ASSERT_EQ(str.capacity(), 15);
    ASSERT_EQ(str, "aaabbbbbbbbbbbb");
}

TEST(AdditionalAssigmentOperatorTest, add_assigment_char2) {
    // arrange
    String str(3, 'a');

    // act
    for (size_t i = 0; i < 12; ++i) {
        str += 'b';
    }
    str += 'c';

    // assert
    ASSERT_EQ(str.size(), 16);
    ASSERT_EQ(str.length(), 16);
    ASSERT_EQ(str.capacity(), 31);
    ASSERT_EQ(str, "aaabbbbbbbbbbbbc");
}

TEST(AdditionalAssigmentOperatorTest, add_assigment_string1) {
    // arrange
    String str("Hello");

    // act
    str += " World!!!";

    // assert
    ASSERT_EQ(str.size(), 14);
    ASSERT_EQ(str.length(), 14);
    ASSERT_EQ(str.capacity(), 23);
    ASSERT_EQ(str, "Hello World!!!");
}

TEST(AdditionalAssigmentOperatorTest, add_assigment_string2) {
    // arrange
    String str(10, 'a');

    // act
    for (size_t i = 0; i < 9; ++i) {
        str.pop_back();
    }
    str += "boba";

    // assert
    ASSERT_EQ(str.size(), 5);
    ASSERT_EQ(str.length(), 5);
    ASSERT_EQ(str.capacity(), 10);
    ASSERT_EQ(str, "aboba");
}

TEST(AdditionalTest, add_char1) {
    // arrange
    String str(10, 'a');

    // act
    String str2 = 'd' + str;

    // assert
    ASSERT_EQ(str2.size(), 11);
    ASSERT_EQ(str2.length(), 11);
    ASSERT_EQ(str2.capacity(), 11);
    ASSERT_EQ(str2, "daaaaaaaaaa");
}

TEST(AdditionalTest, add_char2) {
    // arrange
    String str;

    // act
    String str2 = 'd' + str;

    // assert
    ASSERT_EQ(str2.size(), 1);
    ASSERT_EQ(str2.length(), 1);
    ASSERT_EQ(str2.capacity(), 1);
    ASSERT_EQ(str2, "d");
}

TEST(AdditionalTest, add_char3) {
    // arrange
    String str(10, 'a');

    // act
    String str2 = str + 'd';

    // assert
    ASSERT_EQ(str2.size(), 11);
    ASSERT_EQ(str2.length(), 11);
    ASSERT_EQ(str2.capacity(), 11);
    ASSERT_EQ(str2, "aaaaaaaaaad");
}

TEST(AdditionalTest, add_char4) {
    // arrange
    String str;

    // act
    String str2 = str + 'd';

    // assert
    ASSERT_EQ(str2.size(), 1);
    ASSERT_EQ(str2.length(), 1);
    ASSERT_EQ(str2.capacity(), 1);
    ASSERT_EQ(str2, "d");
}

TEST(AdditionalTest, add_string1) {
    // arrange
    String str("Hello");

    // act
    String str2 = str + " World!";

    // assert
    ASSERT_EQ(str2.size(), 12);
    ASSERT_EQ(str2.length(), 12);
    ASSERT_EQ(str2.capacity(), 23);
    ASSERT_EQ(str2, "Hello World!");
}

TEST(AdditionalTest, add_string2) {
    // arrange
    String str("Hello");

    // act
    String str2 = str + "";

    // assert
    ASSERT_EQ(str2.size(), 5);
    ASSERT_EQ(str2.length(), 5);
    ASSERT_EQ(str2.capacity(), 5);
    ASSERT_EQ(str2, "Hello");
}

TEST(AdditionalTest, add_string3) {
    // arrange
    String str("Hello");

    // act
    String str2 = "World! " + str;

    // assert
    ASSERT_EQ(str2.size(), 12);
    ASSERT_EQ(str2.length(), 12);
    ASSERT_EQ(str2.capacity(), 15);
    ASSERT_EQ(str2, "World! Hello");
}

TEST(AdditionalTest, add_string4) {
    // arrange
    String str("Hello");

    // act
    String str2 = "" + str;

    // assert
    ASSERT_EQ(str2.size(), 5);
    ASSERT_EQ(str2.length(), 5);
    ASSERT_EQ(str2.capacity(), 7);
    ASSERT_EQ(str2, "Hello");
}

TEST(ClearTest, clear_test1) {
    // arrange
    String str("Hello");

    // act
    str.clear();

    // assert
    ASSERT_EQ(str.size(), 0);
    ASSERT_EQ(str.length(), 0);
    ASSERT_EQ(str.capacity(), 5);
    ASSERT_EQ(str[0], '\0');
    ASSERT_EQ(str, "");
}

TEST(ClearTest, clear_test2) {
    // arrange
    String str;

    // act
    str.clear();

    // assert
    ASSERT_EQ(str.size(), 0);
    ASSERT_EQ(str.length(), 0);
    ASSERT_EQ(str.capacity(), 15);
    ASSERT_EQ(str[0], '\0');
    ASSERT_EQ(str, "");
}

TEST(ClearTest, clear_test3) {
    // arrange
    String str;

    // act
    str.clear();
    str += "Hello";

    // assert
    ASSERT_EQ(str.size(), 5);
    ASSERT_EQ(str.length(), 5);
    ASSERT_EQ(str.capacity(), 15);
    ASSERT_EQ(str, "Hello");
}

TEST(ShkinkTest, shrink_test1) {
    // arrange
    String str("Hello world");

    // act
    for (size_t i = 0; i < 5; ++i) {
        str.pop_back();
    }
    str.shrink_to_fit();

    // assert
    ASSERT_EQ(str.size(), 6);
    ASSERT_EQ(str.length(), 6);
    ASSERT_EQ(str.capacity(), 6);
    ASSERT_EQ(str, "Hello ");
}

TEST(ShkinkTest, shrink_test2) {
    // arrange
    String str("Hello world");

    // act
    str.clear();
    str.shrink_to_fit();

    // assert
    ASSERT_EQ(str.size(), 0);
    ASSERT_EQ(str.length(), 0);
    ASSERT_EQ(str.capacity(), 0);
    ASSERT_EQ(str[0], '\0');
    ASSERT_EQ(str, "");
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}