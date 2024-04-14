#include <gtest/gtest.h>
#include <iostream>
#include <unordered_map>

#include "rb.hpp"

namespace RB {

void make_left_rotation(int rotation_root, RB& tree) {
    std::pair<RB::Node*&, RB::Node*> place = tree.find(rotation_root);
    tree.left_rotation(place.first);
}

bool is_correct_parents(std::unordered_map<int, int>& parents, RB& tree) {
    std::vector<RB::Node*> seq;
    tree.get_nodes_in_NLR_traversal_order(seq);

    for (size_t i = 0; i < seq.size(); ++i) {
        RB::Node* node = seq[i];

        if (!RB::make_normal_ptr(node->parent)) {
            continue;
        }
        if (!parents.contains(node->val) || parents[node->val] != RB::make_normal_ptr(node->parent)->val) {
            return false;
        } else {
            parents.erase(node->val);
        }
    }
    return !parents.size();
}

void insert_input_values(std::vector<int>& vct, RB& tree) {
    for (size_t i = 0; i < vct.size(); ++i) {
        tree.insert(vct[i]);
    }
}

void erase_values(std::vector<int>& vct, RB& tree) {
    for (size_t i = 0; i < vct.size(); ++i) {
        tree.erase(vct[i]);
    }
}

bool is_correct_NLR_sequence(std::vector<int>& correct_sequence, RB& tree) {
    std::vector<RB::Node*> seq;
    tree.get_nodes_in_NLR_traversal_order(seq);

    if (seq.size() != correct_sequence.size()) {
        return false;
    }
    for (size_t i = 0; i < correct_sequence.size(); ++i) {
        if (correct_sequence[i] != seq[i]->val) {
            return false;
        }
    }
    return true;
}

bool is_correct_colors(std::unordered_map<int, bool>& is_black_node, RB& tree) {
    std::vector<RB::Node*> seq;
    tree.get_nodes_in_NLR_traversal_order(seq);

    if (seq.size() != is_black_node.size()) {
        return false;
    }

    for (size_t i = 0; i < seq.size(); ++i) {
        if (!is_black_node.contains(seq[i]->val) || ((RB::is_black(seq[i])) != is_black_node[seq[i]->val])) {
            return false;
        }
        is_black_node.erase(seq[i]->val);
    }
    return is_black_node.empty();
}

};


class InsertWithoutFixupParametrizedTest : public ::testing::TestWithParam<std::tuple<std::vector<int>, std::vector<int>, std::unordered_map<int, int>>> { };

TEST_P(InsertWithoutFixupParametrizedTest, IncorrectInsert) {
    // arrange
    RB::RB tree;
    auto params = GetParam();
    std::vector<int>& input = std::get<0>(params);
    std::vector<int>& correctr_NLR_sequence = std::get<1>(params);
    std::unordered_map<int, int>& parents = std::get<2>(params);

    // act
    RB::insert_input_values(input, tree);

    // assert
    ASSERT_TRUE(RB::is_correct_NLR_sequence(correctr_NLR_sequence, tree));
    ASSERT_TRUE(RB::is_correct_parents(parents, tree));
    ASSERT_EQ(tree.size(), correctr_NLR_sequence.size());
}

INSTANTIATE_TEST_CASE_P(
        InsertWithoutFixupTest,
        InsertWithoutFixupParametrizedTest,
        ::testing::Values(
                std::tuple<std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15},
                    {15},
                    {}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15, 9},
                    {15, 9},
                    {{9, 15}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {9, 15},
                    {9, 15},
                    {{15, 9}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15, 9, 100},
                    {15, 9, 100},
                    {{9, 15}, {100, 15}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15, 100, 9},
                    {15, 9, 100},
                    {{9, 15}, {100, 15}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15, 100, 9, 500},
                    {15, 9, 100, 500},
                    {{9, 15}, {100, 15}, {500, 100}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15, 100, 9, 500, 50},
                    {15, 9, 100, 50, 500},
                    {{9, 15}, {100, 15}, {500, 100}, {50, 100}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15, 100, 9, 50, 500},
                    {15, 9, 100, 50, 500},
                    {{9, 15}, {100, 15}, {500, 100}, {50, 100}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15, 100, 9, 50, 500, 15, 9, 100},
                    {15, 9, 100, 50, 500},
                    {{9, 15}, {100, 15}, {500, 100}, {50, 100}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15, 100, 9, 50, 500, -1},
                    {15, 9, -1, 100, 50, 500},
                    {{9, 15}, {100, 15}, {500, 100}, {50, 100}, {-1, 9}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15, 100, 9, 50, 52, 500, -1},
                    {15, 9, -1, 100, 50, 52, 500},
                    {{9, 15}, {100, 15}, {500, 100}, {50, 100}, {52, 50}, {-1, 9}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {1, 3, 5, 7, 9},
                    {1, 3, 5, 7, 9},
                    {{3, 1}, {5, 3}, {7, 5}, {9, 7}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {1, 3, 5, 7, 9, 2, 4, 6, 8},
                    {1, 3, 2, 5, 4, 7, 6, 9, 8},
                    {{3, 1}, {5, 3}, {7, 5}, {9, 7}, {2, 3}, {4, 5}, {6, 7}, {8, 9}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {9, 7, 5, 3, 1},
                    {9, 7, 5, 3, 1},
                    {{7, 9}, {5, 7}, {3, 5}, {1, 3}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {9, 7, 5, 3, 1, 2, 4, 6, 8},
                    {9, 7, 5, 3, 1, 2, 4, 6, 8},
                    {{7, 9}, {5, 7}, {3, 5}, {1, 3}, {2, 1}, {4, 3}, {6, 5}, {8, 7}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {9, 10, 7, 5, 3, 1, 2, 4, 6, 8},
                    {9, 7, 5, 3, 1, 2, 4, 6, 8, 10},
                    {{7, 9}, {5, 7}, {3, 5}, {1, 3}, {2, 1}, {4, 3}, {6, 5}, {8, 7}, {10, 9}}
                }
                )
        );


class EraseWithoutFixupParametrizedTest : public ::testing::TestWithParam<std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, std::unordered_map<int, int>>> { };

TEST_P(EraseWithoutFixupParametrizedTest, IncorrectErase) {
    // arrange
    RB::RB tree;
    auto params = GetParam();
    std::vector<int>& input = std::get<0>(params);
    std::vector<int>& to_erase = std::get<1>(params);
    std::vector<int>& correctr_NLR_sequence = std::get<2>(params);
    std::unordered_map<int, int>& parents = std::get<3>(params);

    // act
    RB::insert_input_values(input, tree);
    RB::erase_values(to_erase, tree);

    // assert
    ASSERT_TRUE(RB::is_correct_NLR_sequence(correctr_NLR_sequence, tree));
    ASSERT_TRUE(RB::is_correct_parents(parents, tree));
    ASSERT_EQ(tree.size(), correctr_NLR_sequence.size());
}

INSTANTIATE_TEST_CASE_P(
        EraseWithoutFixupTest,
        EraseWithoutFixupParametrizedTest,
        ::testing::Values(
                std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15},
                    {15},
                    {},
                    {}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15},
                    {},
                    {15},
                    {}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {9, 7, 5, 3, 1, 2, 4, 6, 8},
                    {},
                    {9, 7, 5, 3, 1, 2, 4, 6, 8},
                    {{7, 9}, {5, 7}, {3, 5}, {1, 3}, {2, 1}, {4, 3}, {6, 5}, {8, 7}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {1, 2, 3, 4, 5, 6, 7, 8},
                    {8},
                    {1, 2, 3, 4, 5, 6, 7},
                    {{2, 1}, {3, 2}, {4, 3}, {5, 4}, {6, 5}, {7, 6}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {1, 2, 3, 4, 5, 6, 7, 8},
                    {8, 7},
                    {1, 2, 3, 4, 5, 6},
                    {{2, 1}, {3, 2}, {4, 3}, {5, 4}, {6, 5}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {1, 2, 3, 4, 5, 6, 7, 8},
                    {7, 8},
                    {1, 2, 3, 4, 5, 6},
                    {{2, 1}, {3, 2}, {4, 3}, {5, 4}, {6, 5}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {9, 8, 7, 6, 5, 4, 3, 2, 1},
                    {1},
                    {9, 8, 7, 6, 5, 4, 3, 2},
                    {{8, 9}, {7, 8}, {6, 7}, {5, 6}, {4, 5}, {3, 4}, {2, 3}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {9, 8, 7, 6, 5, 4, 3, 2, 1},
                    {1, 2},
                    {9, 8, 7, 6, 5, 4, 3},
                    {{8, 9}, {7, 8}, {6, 7}, {5, 6}, {4, 5}, {3, 4}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {9, 8, 7, 6, 5, 4, 3, 2, 1},
                    {2, 1},
                    {9, 8, 7, 6, 5, 4, 3},
                    {{8, 9}, {7, 8}, {6, 7}, {5, 6}, {4, 5}, {3, 4}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15, 100, 9, 50, 52, 500, -1, 10},
                    {},
                    {15, 9, -1, 10, 100, 50, 52, 500},
                    {{9, 15}, {100, 15}, {-1, 9}, {10, 9}, {50, 100}, {52, 50}, {500, 100}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15, 100, 9, 50, 52, 500, -1, 10},
                    {10},
                    {15, 9, -1, 100, 50, 52, 500},
                    {{9, 15}, {100, 15}, {-1, 9},{50, 100}, {52, 50}, {500, 100}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15, 100, 9, 50, 52, 500, -1, 10},
                    {-1},
                    {15, 9, 10, 100, 50, 52, 500},
                    {{9, 15}, {100, 15}, {10, 9}, {50, 100}, {52, 50}, {500, 100}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15, 100, 9, 50, 52, 500, -1, 10},
                    {52},
                    {15, 9, -1, 10, 100, 50, 500},
                    {{9, 15}, {100, 15}, {-1, 9}, {10, 9}, {50, 100}, {500, 100}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15, 100, 9, 50, 52, 500, -1, 10},
                    {500},
                    {15, 9, -1, 10, 100, 50, 52},
                    {{9, 15}, {100, 15}, {-1, 9}, {10, 9}, {50, 100}, {52, 50}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15, 100, 8, 50, 52, 500, -1, 10, 9, 11, 49},
                    {},
                    {15, 8, -1, 10, 9, 11, 100, 50, 49, 52, 500},
                    {{8, 15}, {100, 15}, {-1, 8}, {10, 8}, {9, 10}, {11, 10}, {50, 100}, {500, 100}, {49, 50}, {52, 50}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15, 100, 8, 50, 52, 500, -1, 10, 9, 11, 49},
                    {11, 10},
                    {15, 8, -1, 9, 100, 50, 49, 52, 500},
                    {{8, 15}, {100, 15}, {-1, 8}, {9, 8}, {50, 100}, {500, 100}, {49, 50}, {52, 50}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15, 100, 8, 50, 52, 500, -1, 10, 9, 11, 49},
                    {10, 11},
                    {15, 8, -1, 9, 100, 50, 49, 52, 500},
                    {{8, 15}, {100, 15}, {-1, 8}, {9, 8}, {50, 100}, {500, 100}, {49, 50}, {52, 50}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15, 100, 8, 50, 52, 500, -1, 10, 9, 11, 49},
                    {10},
                    {15, 8, -1, 9, 11, 100, 50, 49, 52, 500},
                    {{8, 15}, {100, 15}, {-1, 8}, {9, 8}, {11, 9}, {50, 100}, {500, 100}, {49, 50}, {52, 50}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15, 100, 8, 50, 52, 500, -1, 10, 9, 11, 49},
                    {49, 50},
                    {15, 8, -1, 10, 9, 11, 100, 52, 500},
                    {{8, 15}, {100, 15}, {-1, 8}, {10, 8}, {9, 10}, {11, 10}, {500, 100}, {52, 100}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15, 100, 8, 50, 52, 500, -1, 10, 9, 11, 49},
                    {50, 49},
                    {15, 8, -1, 10, 9, 11, 100, 52, 500},
                    {{8, 15}, {100, 15}, {-1, 8}, {10, 8}, {9, 10}, {11, 10}, {500, 100}, {52, 100}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15, 100, 8, 50, 52, 500, -1, 10, 9, 11, 49},
                    {100},
                    {15, 8, -1, 10, 9, 11, 52, 50, 49, 500},
                    {{8, 15}, {52, 15}, {-1, 8}, {10, 8}, {9, 10}, {11, 10}, {50, 52}, {500, 52}, {49, 50}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15, 100, 8, 50, 52, 500, -1, 10, 9, 11, 49},
                    {8},
                    {15, -1, 10, 9, 11, 100, 50, 49, 52, 500},
                    {{-1, 15}, {100, 15}, {10, -1}, {9, 10}, {11, 10}, {50, 100}, {500, 100}, {49, 50}, {52, 50}}
                },
                std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, std::unordered_map<int, int>> {
                    {15, 100, 8, 50, 52, 500, -1, 10, 9, 11, 49},
                    {15},
                    {11, 8, -1, 10, 9, 100, 50, 49, 52, 500},
                    {{8, 11}, {100, 11}, {-1, 8}, {10, 8}, {9, 10}, {50, 100}, {500, 100}, {49, 50}, {52, 50}}
                }
                )
        );


class LeftRotationParametrizedTest : public ::testing::TestWithParam<std::tuple<std::vector<int>, int, std::vector<int>, std::unordered_map<int, int>>> { };

TEST_P(LeftRotationParametrizedTest, IncorrectLeftRotation) {
    // arrange
    RB::RB tree;
    auto params = GetParam();
    std::vector<int>& input = std::get<0>(params);
    int rotation_root = std::get<1>(params);
    std::vector<int>& correctr_NLR_sequence = std::get<2>(params);
    std::unordered_map<int, int>& parents = std::get<3>(params);

    // act
    RB::insert_input_values(input, tree);
    RB::make_left_rotation(rotation_root, tree);

    // assert
    ASSERT_TRUE(RB::is_correct_NLR_sequence(correctr_NLR_sequence, tree));
    ASSERT_TRUE(RB::is_correct_parents(parents, tree));
    ASSERT_EQ(tree.size(), correctr_NLR_sequence.size());
}

INSTANTIATE_TEST_CASE_P(
        LeftRotationTest,
        LeftRotationParametrizedTest,
        ::testing::Values(

                /*
                    ONLY GAMMA
                */
                std::tuple<std::vector<int>, int, std::vector<int>, std::unordered_map<int, int>> {
                    {1, 2},
                    1,
                    {2, 1},
                    {{1, 2}}
                },
                std::tuple<std::vector<int>, int, std::vector<int>, std::unordered_map<int, int>> {
                    {1, 2, 3, 4, 5},
                    1,
                    {2, 1, 3, 4, 5},
                    {{1, 2}, {3, 2}, {4, 3}, {5, 4}}
                },
                std::tuple<std::vector<int>, int, std::vector<int>, std::unordered_map<int, int>> {
                    {1, 2, 3, 4, 5},
                    2,
                    {1, 3, 2, 4, 5},
                    {{3, 1}, {2, 3}, {4, 3}, {5, 4}}
                },
                std::tuple<std::vector<int>, int, std::vector<int>, std::unordered_map<int, int>> {
                    {1, 2, 3, 4, 5},
                    3,
                    {1, 2, 4, 3, 5},
                    {{2, 1}, {4, 2}, {3, 4}, {5, 4}}
                },
                std::tuple<std::vector<int>, int, std::vector<int>, std::unordered_map<int, int>> {
                    {1, 2, 3, 4, 5},
                    4,
                    {1, 2, 3, 5, 4},
                    {{2, 1}, {3, 2}, {5, 3}, {4, 5}}
                },
                /*
                    ONLY GAMMA
                */

                /*
                    ONLY BETTA
                */
                std::tuple<std::vector<int>, int, std::vector<int>, std::unordered_map<int, int>> {
                    {1, 3, 2},
                    1,
                    {3, 1, 2},
                    {{2, 1}, {1, 3}}
                },
                std::tuple<std::vector<int>, int, std::vector<int>, std::unordered_map<int, int>> {
                    {1, 50, 20, 10, 25},
                    1,
                    {50, 1, 20, 10, 25},
                    {{1, 50}, {20, 1}, {10, 20}, {25, 20}}
                },
                std::tuple<std::vector<int>, int, std::vector<int>, std::unordered_map<int, int>> {
                    {-10, -100, -5, 1, 50, 20, 10, 25},
                    1,
                    {-10, -100, -5, 50, 1, 20, 10, 25},
                    {{-100, -10}, {-5, -10}, {50, -5}, {1, 50}, {20, 1}, {10, 20}, {25, 20}}
                },
                /*
                    ONLY BETTA
                */

                /*
                    ONLY ALPHA
                */
                std::tuple<std::vector<int>, int, std::vector<int>, std::unordered_map<int, int>> {
                    {10, 5, 15},
                    10,
                    {15, 10, 5},
                    {{10, 15}, {5, 10}}
                },
                std::tuple<std::vector<int>, int, std::vector<int>, std::unordered_map<int, int>> {
                    {-100, -200, -10, 10, 5, 15},
                    10,
                    {-100, -200, -10, 15, 10, 5},
                    {{10, 15}, {5, 10}, {-200, -100}, {-10, -100}, {15, -10}}
                },
                std::tuple<std::vector<int>, int, std::vector<int>, std::unordered_map<int, int>> {
                    {-100, -200, -10, 10, 5, 15, 1, 7, -1, 2, 6, 9},
                    10,
                    {-100, -200, -10, 15, 10, 5, 1, -1, 2, 7, 6, 9},
                    {{10, 15}, {5, 10}, {1, 5}, {-1, 1}, {2, 1}, {7, 5}, {6, 7}, {9, 7}, {-200, -100}, {-10, -100}, {15, -10}}
                },
                std::tuple<std::vector<int>, int, std::vector<int>, std::unordered_map<int, int>> {
                    {10, 5, 15, 1, 7, -1, 2, 6, 9},
                    10,
                    {15, 10, 5, 1, -1, 2, 7, 6, 9},
                    {{10, 15}, {5, 10}, {1, 5}, {-1, 1}, {2, 1}, {7, 5}, {6, 7}, {9, 7}}
                },
                /*
                    ONLY ALPHA
                */

                /*
                    ALPHA, BETTA AND GAMMA
                */
                std::tuple<std::vector<int>, int, std::vector<int>, std::unordered_map<int, int>> {
                    {50, 40, 100, 30, 45, 70, 200, 60, 90, 150, 300},
                    50,
                    {100, 50, 40, 30, 45, 70, 60, 90, 200, 150, 300},
                    {{50, 100}, {40, 50}, {70, 50}, {30, 40}, {45, 40}, {60, 70}, {90, 70}, {150, 200}, {300, 200}, {200, 100}}
                },
                std::tuple<std::vector<int>, int, std::vector<int>, std::unordered_map<int, int>> {
                    {-100, -200, -10, 50, 40, 100, 30, 45, 70, 200, 60, 90, 150, 300},
                    50,
                    {-100, -200, -10, 100, 50, 40, 30, 45, 70, 60, 90, 200, 150, 300},
                    {{50, 100}, {40, 50}, {70, 50}, {30, 40}, {45, 40}, {60, 70}, {90, 70}, {150, 200}, {300, 200}, {200, 100}, {-200, -100}, {-10, -100}, {100, -10}}
                }
                /*
                    ALPHA, BETTA AND GAMMA
                */             
                )
        );



// class InsertWithFixupParametrizedTest : public ::testing::TestWithParam<std::tuple<std::vector<int>, std::unordered_map<int, bool>, std::vector<int>, std::unordered_map<int, int>>> { };

// TEST_P(InsertWithFixupParametrizedTest, IncorrectFixup) {
//     // arrange
//     RB::RB tree;
//     auto params = GetParam();
//     std::vector<int>& input = std::get<0>(params);
//     std::unordered_map<int, bool> is_black_node = std::get<1>(params);
//     std::vector<int>& correctr_NLR_sequence = std::get<2>(params);
//     std::unordered_map<int, int>& parents = std::get<3>(params);

//     // act
//     RB::insert_input_values(input, tree);

//     // assert
//     ASSERT_TRUE(RB::is_correct_NLR_sequence(correctr_NLR_sequence, tree));
//     ASSERT_TRUE(RB::is_correct_parents(parents, tree));
//     ASSERT_TRUE(RB::is_correct_colors(is_black_node, tree));
//     ASSERT_EQ(tree.size(), correctr_NLR_sequence.size());
//     ASSERT_TRUE(tree.is_correct_tree());
// }

// INSTANTIATE_TEST_CASE_P(
//         InsertWithFixupTest,
//         InsertWithFixupParametrizedTest,
//         ::testing::Values(

//                 /*
//                     UNCLE IS RED
//                 */
//                 std::tuple<std::vector<int>, std::unordered_map<int, bool>, std::vector<int>, std::unordered_map<int, int>> {
//                     {1},
//                     {{1, true}},
//                     {1},
//                     {}
//                 },
//                 std::tuple<std::vector<int>, std::unordered_map<int, bool>, std::vector<int>, std::unordered_map<int, int>> {
//                     {1, 5},
//                     {{1, true}, {5, false}},
//                     {1, 5},
//                     {{5, 1}}
//                 },
//                 std::tuple<std::vector<int>, std::unordered_map<int, bool>, std::vector<int>, std::unordered_map<int, int>> {
//                     {1, 5, -10},
//                     {{1, true}, {5, false}, {-10, false}},
//                     {1, -10, 5},
//                     {{5, 1}, {-10, 1}}
//                 },
//                 std::tuple<std::vector<int>, std::unordered_map<int, bool>, std::vector<int>, std::unordered_map<int, int>> {
//                     {1, 5, -10, 3},
//                     {{1, true}, {5, true}, {-10, true}, {3, false}},
//                     {1, -10, 5, 3},
//                     {{5, 1}, {-10, 1}, {3, 5}}
//                 },
//                 std::tuple<std::vector<int>, std::unordered_map<int, bool>, std::vector<int>, std::unordered_map<int, int>> {
//                     {1, 5, -10, 7},
//                     {{1, true}, {5, true}, {-10, true}, {7, false}},
//                     {1, -10, 5, 7},
//                     {{5, 1}, {-10, 1}, {7, 5}}
//                 },
//                 std::tuple<std::vector<int>, std::unordered_map<int, bool>, std::vector<int>, std::unordered_map<int, int>> {
//                     {1, 5, -10, 7, 3},
//                     {{1, true}, {5, true}, {-10, true}, {7, false}, {3, false}},
//                     {1, -10, 5, 3, 7},
//                     {{5, 1}, {-10, 1}, {7, 5}, {3, 5}}
//                 },
//                 std::tuple<std::vector<int>, std::unordered_map<int, bool>, std::vector<int>, std::unordered_map<int, int>> {
//                     {1, 2, 3, 4, 500, 600, 700},
//                     {{1, true}, {2, true}, {3, true}, {600, true}, {4, false}, {500, false}, {700, false}},
//                     {2, 1, 4, 3, 600, 500, 700},
//                     {{1, 2}, {4, 2}, {3, 4}, {600, 4}, {500, 600}, {700, 600}}
//                 },
//                 std::tuple<std::vector<int>, std::unordered_map<int, bool>, std::vector<int>, std::unordered_map<int, int>> {
//                     {1, 2, 3, 4, 500, 600, 700, 800},
//                     {{1, true}, {2, false}, {3, true}, {600, false}, {4, true}, {500, true}, {700, true}, {800, false}},
//                     {4, 2, 1, 3, 600, 500, 700, 800},
//                     {{1, 2}, {3, 2}, {2, 4}, {600, 4}, {500, 600}, {700, 600}, {800, 700}}
//                 },
//                 std::tuple<std::vector<int>, std::unordered_map<int, bool>, std::vector<int>, std::unordered_map<int, int>> {
//                     {1, 2, 3, 4, 500, 600, 700, 650},
//                     {{1, true}, {2, false}, {3, true}, {600, false}, {4, true}, {500, true}, {700, true}, {650, false}},
//                     {4, 2, 1, 3, 600, 500, 700, 650},
//                     {{1, 2}, {3, 2}, {2, 4}, {600, 4}, {500, 600}, {700, 600}, {650, 700}}
//                 },
//                 std::tuple<std::vector<int>, std::unordered_map<int, bool>, std::vector<int>, std::unordered_map<int, int>> {
//                     {1, 2, 3, 4, 500, 600, 700, 450},
//                     {{1, true}, {2, false}, {3, true}, {600, false}, {4, true}, {500, true}, {700, true}, {450, false}},
//                     {4, 2, 1, 3, 600, 500, 450, 700},
//                     {{1, 2}, {3, 2}, {2, 4}, {600, 4}, {500, 600}, {700, 600}, {450, 500}}
//                 },
//                 std::tuple<std::vector<int>, std::unordered_map<int, bool>, std::vector<int>, std::unordered_map<int, int>> {
//                     {1, 2, 3, 4, 500, 600, 700, 550},
//                     {{1, true}, {2, false}, {3, true}, {600, false}, {4, true}, {500, true}, {700, true}, {550, false}},
//                     {4, 2, 1, 3, 600, 500, 550, 700},
//                     {{1, 2}, {3, 2}, {2, 4}, {600, 4}, {500, 600}, {700, 600}, {550, 500}}
//                 }         
//                 )
//         );


// TEST(TestFixupWithRandomInsertion, Random) {
// 	// arrange
// 	RB::RB tree;

//     std::srand(0);
// 	for (size_t i = 0; i < 100000; ++i) {
//         tree.insert(std::rand() % 1000);     // act
//         ASSERT_TRUE(tree.is_correct_tree()); // assert
//     }
// }


int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}