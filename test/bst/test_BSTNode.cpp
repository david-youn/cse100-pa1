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

TEST(BST_NODE_TESTS, TEST_SUCCESSOR2) {
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
    ASSERT_EQ(n4->successor(), n2);
    ASSERT_EQ(n2->successor(), n1);
    ASSERT_EQ(n5->successor(), nullptr);
    ASSERT_EQ(n3->successor(), n5);
    ASSERT_EQ(n1->successor(), n3);
}

TEST(BST_NODE_TESTS, TEST_SUCCESSOR3) {
    BSTNode<int>* n1 = new BSTNode<int>(7);
    BSTNode<int>* n2 = new BSTNode<int>(4);
    BSTNode<int>* n3 = new BSTNode<int>(3);
    BSTNode<int>* n4 = new BSTNode<int>(5);
    BSTNode<int>* n5 = new BSTNode<int>(8);
    BSTNode<int>* n6 = new BSTNode<int>(9);
    n1->left = n2;
    n2->parent = n1;
    n2->left = n3;
    n3->parent = n2;
    n2->right = n4;
    n4->parent = n2;
    n1->right = n5;
    n5->parent = n1;
    n5->right = n6;
    n6->parent = n5;
    ASSERT_EQ(n6->successor(), nullptr);
    ASSERT_EQ(n4->successor(), n1);
    ASSERT_EQ(n2->successor(), n4);

    BSTNode<int>* n7 = new BSTNode<int>(6);
    n2->right = n7;
    n7->parent = n2;
    n7->left = n4;
    n4->parent = n7;
    ASSERT_EQ(n2->successor(), n4);
}

TEST(BST_NODE_TESTS, TEST_SETDATA) {
    BSTNode<int>* n1 = new BSTNode<int>(3);
    ASSERT_EQ(n1->getData(), 3);
    n1->setData(5);
    ASSERT_EQ(n1->getData(), 5);
    n1->setData(-10);
    ASSERT_EQ(n1->getData(), -10);
}

TEST(BST_NODE_TESTS, TEST_GETDATA) {
    BSTNode<int>* n1 = new BSTNode<int>(3);
    int check = n1->getData();
    ASSERT_EQ(check, 3);
}

TEST(BST_NODE_TESTS, TEST_CONSTRUCTOR2) {
    BSTNode<int> node(0);
    ASSERT_EQ(node.getData(), 0);
    ASSERT_EQ(node.parent, nullptr);
    ASSERT_EQ(node.left, nullptr);
    ASSERT_EQ(node.right, nullptr);
}

TEST(BST_NODE_TESTS, TEST_CONSTRUCTOR3) {
    BSTNode<int>* n1 = new BSTNode<int>(3);
    BSTNode<int> node(-3);
    n1->left = &node;
    ASSERT_EQ(node.getData(), -3);
    ASSERT_EQ(n1->left->getData(), -3);
    ASSERT_EQ(n1->right, nullptr);
    ASSERT_EQ(node.parent, nullptr);
    ASSERT_EQ(node.left, nullptr);
    ASSERT_EQ(node.right, nullptr);
}