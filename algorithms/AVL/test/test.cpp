#include <gtest/gtest.h>
#include <tuple>
#include <vector>
#include "AVL.hpp"

using namespace avl;

void insert_input_values(std::vector<int64_t>& vct, AVL& tree) {
    for (size_t i = 0; i < vct.size(); ++i) {
        tree.insert(vct[i]);
    }
}

bool is_correct_NLR_sequence(std::vector<int64_t>& correct_sequence, AVL& tree) {
    std::vector<AVL::Node*> seq;
    tree.get_nodes_from_NLR_traversal(seq);

    if (seq.size() != correct_sequence.size()) {
        return false;
    }
    for (size_t i = 0; i < correct_sequence.size(); ++i) {
        if (correct_sequence[i] != seq[i]->value) {
            return false;
        }
    }
    return true;

}

class SmallLeftRotationParametrizedTests : public ::testing::TestWithParam<std::pair<std::vector<int64_t>, std::vector<int64_t>>> { };

TEST_P(SmallLeftRotationParametrizedTests, IncorrectRotation) {
    // arrange
    AVL tree;
    auto params = GetParam();
    std::vector<int64_t>& input = params.first;
    std::vector<int64_t>& correctr_NLR_sequence = params.second;

    // act
    insert_input_values(input, tree);
    tree.small_left_rotation(tree.root);

    // assert
    ASSERT_TRUE(is_correct_NLR_sequence(correctr_NLR_sequence, tree));

}

INSTANTIATE_TEST_CASE_P(
        SmallLeftRotationTests,
        SmallLeftRotationParametrizedTests,
        ::testing::Values(
                std::pair<std::vector<int64_t>, std::vector<int64_t>> {
                    {9, 15},
                    {15, 9}
                },
                std::pair<std::vector<int64_t>, std::vector<int64_t>> {
                    {9, 15, 150, 90, 200},
                    {15, 9, 150, 90, 200}
                },
                std::pair<std::vector<int64_t>, std::vector<int64_t>> {
                    {9, 30, 25, 20, 27},
                    {30, 9, 25, 20, 27}
                },
                std::pair<std::vector<int64_t>, std::vector<int64_t>> {
                    {50, 100, 30, 20, 40},
                    {100, 50, 30, 20, 40}
                },
                std::pair<std::vector<int64_t>, std::vector<int64_t>> {
                    {50, 100, 70, 200, 60, 90, 150, 300},
                    {100, 50, 70, 60, 90, 200, 150, 300}
                },
                std::pair<std::vector<int64_t>, std::vector<int64_t>> {
                    {50, 100, 200, 150, 300, 30, 20, 40},
                    {100, 50, 30, 20, 40, 200, 150, 300}
                },
                std::pair<std::vector<int64_t>, std::vector<int64_t>> {
                    {50, 30, 100, 20, 40, 70, 60, 90},
                    {100, 50, 30, 20, 40, 70, 60, 90}
                },
                std::pair<std::vector<int64_t>, std::vector<int64_t>> {
                    {50, 30, 100, 20, 40, 70, 60, 90, 200, 150, 300},
                    {100, 50, 30, 20, 40, 70, 60, 90, 200, 150, 300}
                }
                )
        );


class SmallRightRotationParametrizedTests : public ::testing::TestWithParam<std::pair<std::vector<int64_t>, std::vector<int64_t>>> { };

TEST_P(SmallRightRotationParametrizedTests, IncorrectRotation) {
    // arrange
    AVL tree;
    auto params = GetParam();
    std::vector<int64_t>& input = params.first;
    std::vector<int64_t>& correctr_NLR_sequence = params.second;

    // act
    insert_input_values(input, tree);
    tree.small_right_rotation(tree.root);

    // assert
    ASSERT_TRUE(is_correct_NLR_sequence(correctr_NLR_sequence, tree));

}

INSTANTIATE_TEST_CASE_P(
        SmallRightRotationTests,
        SmallRightRotationParametrizedTests,
        ::testing::Values(
                std::pair<std::vector<int64_t>, std::vector<int64_t>> {
                    {15, 9},
                    {9, 15},
                },
                std::pair<std::vector<int64_t>, std::vector<int64_t>> {
                    {15, 9, 150, 90, 200},
                    {9, 15, 150, 90, 200},
                },
                std::pair<std::vector<int64_t>, std::vector<int64_t>> {
                    {30, 9, 25, 20, 27},
                    {9, 30, 25, 20, 27},
                },
                std::pair<std::vector<int64_t>, std::vector<int64_t>> {
                    {100, 50, 30, 20, 40},
                    {50, 30, 20, 40, 100},
                },
                std::pair<std::vector<int64_t>, std::vector<int64_t>> {
                    {100, 50, 70, 60, 90, 200, 150, 300},
                    {50, 100, 70, 60, 90, 200, 150, 300},
                },
                std::pair<std::vector<int64_t>, std::vector<int64_t>> {
                    {100, 50, 30, 20, 40, 200, 150, 300},
                    {50, 30, 20, 40, 100, 200, 150, 300},
                },
                std::pair<std::vector<int64_t>, std::vector<int64_t>> {
                    {100, 50, 30, 20, 40, 70, 60, 90},
                    {50, 30, 20, 40, 100, 70, 60, 90},
                },
                std::pair<std::vector<int64_t>, std::vector<int64_t>> {
                    {100, 50, 30, 20, 40, 70, 60, 90, 200, 150, 300},
                    {50, 30, 20, 40, 100, 70, 60, 90, 200, 150, 300},
                }
                )
        );


int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}