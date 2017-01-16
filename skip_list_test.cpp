// Author: xianmu <atangengineer@gmail.com>
// Created: 01/16/17
// Description: unit-test on the basis of gtest

#include <gtest/gtest.h>

#include "skip_list.h"

TEST(SkipListTest, InsertTest) {
    SkipList<int> skip_list;
    EXPECT_EQ(0, skip_list.insert(11));
    EXPECT_EQ(0, skip_list.lookup(11));
    EXPECT_EQ(-1, skip_list.lookup(12));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
