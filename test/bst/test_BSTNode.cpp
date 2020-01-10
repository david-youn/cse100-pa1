#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BSTNode.hpp"

using namespace std;
using namespace testing;

TEST(BST_NODE_TESTS, TEST_SUCCESSOR) {
    BSTNode<int> node(3);
    ASSERT_EQ(node.successor(), nullptr);
}

TEST(BST_NODE_TESTS, TEST_CONSTRUCTOR) {
    BSTNode<int> node(2);
    ASSERT_EQ(node.getData(), 2);
}