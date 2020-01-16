#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"

using namespace std;
using namespace testing;

TEST(BST_ITERATOR_TEST, TEST_ITERATOR_INCREMENT) {
    BSTNode<int> node(3);
    BSTIterator<int> iter(&node);

    ASSERT_NE(iter, nullptr);

    iter++;

    ASSERT_EQ(iter, nullptr);
}

TEST(BST_ITERATOR_TEST, TEST_ITERATOR_INCREMENT2) {
    BSTNode<int> node(3);
    BSTIterator<int> iter(&node);
    BSTIterator<int> iter2(&node);
    BSTNode<int> node1(2);
    BSTIterator<int> iter3(&node1);

    ASSERT_TRUE(iter == iter2);
    ASSERT_TRUE(iter != iter3);
    ASSERT_FALSE(iter == iter3);
    ASSERT_FALSE(iter != iter2);

    BSTNode<int>* n1 = new BSTNode<int>(3);
    BSTNode<int>* n2 = new BSTNode<int>(1);
    BSTNode<int>* n3 = new BSTNode<int>(4);
    BSTNode<int>* n4 = new BSTNode<int>(-33);
    BSTNode<int>* n5 = new BSTNode<int>(100);
    n1->left = n2;
    n2->parent = n1;
    n2->left = n4;
    n4->parent = n2;
    n1->right = n3;
    n3->parent = n1;
    n3->right = n5;
    n5->parent = n3;

    BSTIterator<int> iter4(n4);
    ASSERT_EQ(*iter4, -33);
    ++iter4;
    BSTIterator<int> iter5(n2);
    ASSERT_EQ(iter5, iter4);
    ASSERT_TRUE(iter5 == iter4);
    iter4++;
    BSTIterator<int> iter6(n1);
    ASSERT_TRUE(iter4 == iter6);
}