#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BST.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/* Empty BST test starts here */

TEST(BSTTests, EMPTY_TREE_HEIGHT_TEST) {
    BST<int> bst;
    ASSERT_EQ(bst.height(), -1);
}

/* Small BST test starts here */

/**
 * A simple test fixture from which multiple tests
 * can be created. All fixture tests (denoted by the
 * TEST_F macro) can access the protected members of this
 * fixture. Its data is reset after every test.
 *
 * Builds the following BST:
 *         3
 *        / \
 *       1   4
 *      /     \
 *    -33     100
 */
class SmallBSTFixture : public ::testing::Test {
  protected:
    BST<int> bst;

  public:
    SmallBSTFixture() {
        // initialization code here
        vector<int> input{3, 4, 1, 100, -33};
        insertIntoBST(input, bst);
    }
    // code in SetUp() will execute just before the test ensues
    // void SetUp() {}
};

TEST_F(SmallBSTFixture, SMALL_SIZE_TEST) {
    // assert that the small BST has the correct size
    ASSERT_EQ(bst.size(), 5);
}

TEST_F(SmallBSTFixture, SMALL_INSERT_DUPLICATES_TEST) {
    // assert failed duplicate insertion
    ASSERT_FALSE(bst.insert(3));
}

// TODO: add more BST tests here

TEST_F(SmallBSTFixture, SMALL_INSERT_TEST) {
    // assert passed insertion
    ASSERT_TRUE(bst.insert(5));
}

TEST_F(SmallBSTFixture, SMALL_INSERT_AND_DUPLICATE_TEST) {
    // assert passed insertion
    ASSERT_TRUE(bst.insert(2));
    // assert failed duplicate insertion
    ASSERT_FALSE(bst.insert(2));
}

TEST_F(SmallBSTFixture, SMALL_INSERT_DUPLICATES_TEST2) {
    // assert failed duplicate insertion
    ASSERT_FALSE(bst.insert(-33));
}

// Testing Find
TEST_F(SmallBSTFixture, SMALL_FIND_TEST) { ASSERT_EQ(-33, *bst.find(-33)); }

TEST_F(SmallBSTFixture, SMALL_FIND_TEST2) { ASSERT_EQ(100, *bst.find(100)); }

TEST_F(SmallBSTFixture, SMALL_FIND_TEST3) { ASSERT_EQ(3, *bst.find(3)); }

TEST_F(SmallBSTFixture, SMALL_FIND_TEST4) {
    ASSERT_EQ(bst.end(), bst.find(1000));
}

TEST_F(SmallBSTFixture, SMALL_FIND_TEST5) {
    ASSERT_EQ(bst.end(), bst.find(10));
}

TEST_F(SmallBSTFixture, SMALL_FIND_TEST6) {
    BSTIterator<int> iter(nullptr);
    ASSERT_EQ(iter, bst.find(10));
}

// Testing Height
TEST_F(SmallBSTFixture, SMALL_HEIGHT_TEST) {
    // assert that the small BST has the correct height
    ASSERT_EQ(bst.height(), 2);
}

TEST_F(SmallBSTFixture, SMALL_HEIGHT_TEST2) {
    // assert that the small BST has the correct height
    bst.insert(5);
    bst.insert(6);
    ASSERT_EQ(bst.height(), 4);
}

// testing begin method
TEST_F(SmallBSTFixture, SMALL_BEGIN_TEST) {
    // assert that the small BST has the correct height
    ASSERT_EQ(*bst.begin(), -33);
}

TEST_F(SmallBSTFixture, SMALL_BEGIN_TEST2) {
    bst.insert(-81);
    // assert that the small BST has the correct height
    ASSERT_EQ(*bst.begin(), -81);
}

// testing inorder method
TEST_F(SmallBSTFixture, SMALL_INORDER) {
    vector<int> vect{-33, 1, 3, 4, 100};
    ASSERT_EQ(bst.inorder(), vect);
}

// testing destructor and empty method
TEST_F(SmallBSTFixture, SMALL_DESTRUCT) {
    bst.~BST();
    // assert empty
    ASSERT_TRUE(bst.empty());
    ASSERT_EQ(bst.height(), -1);
    ASSERT_EQ(bst.size(), 0);
}

// testing small balanced bst
TEST_F(SmallBSTFixture, SMALL_BALANCE) {
    bst.insert(2);
    bst.insert(1000);
    bst.insert(5);
    bst.insert(-50);
    BST<int>* bst2 = new BST<int>(bst);
    ASSERT_FALSE(bst.empty());
    ASSERT_EQ(bst2->size(), 9);
    ASSERT_EQ(bst2->height(), 3);
    ASSERT_EQ(*(bst2->begin()), -50);
    bst2->~BST();
}

TEST_F(SmallBSTFixture, SMALL_BALANCE2) {
    bst.insert(2);
    bst.insert(5);
    BST<int>* bst2 = new BST<int>(bst);
    ASSERT_FALSE(bst.empty());
    ASSERT_EQ(bst2->size(), 7);
    ASSERT_EQ(bst2->height(), 2);
    ASSERT_EQ(*(bst2->begin()), -33);
    bst2->~BST();
}

TEST_F(SmallBSTFixture, SMALL_BALANCE3) {
    bst.insert(2);
    bst.insert(5);
    bst.insert(-34);
    BST<int>* bst2 = new BST<int>(bst);
    ASSERT_FALSE(bst.empty());
    ASSERT_EQ(bst2->size(), 8);
    ASSERT_EQ(bst2->height(), 3);
    ASSERT_EQ(*(bst2->begin()), -34);
    bst2->~BST();
}

// testing deleteNode for existing nodes
TEST_F(SmallBSTFixture, SMALL_DELETE) {
    ASSERT_TRUE(bst.deleteNode(-33));
    //  ASSERT_EQ(bst.height(), 2);
}

// testing deleteNode for non existent nodes
TEST_F(SmallBSTFixture, SMALL_DELETE2) {
    ASSERT_FALSE(bst.deleteNode(13));
    ASSERT_FALSE(bst.deleteNode(36));
    // ASSERT_EQ(bst.height(), 2);
}

// testing deleteNode for the root
TEST_F(SmallBSTFixture, SMALL_DELETE3) {
    ASSERT_TRUE(bst.deleteNode(3));
    ASSERT_TRUE(bst.deleteNode(-33));
    // ASSERT_EQ(bst.height(), 4);
}

// testing deleteNode for nodes with one child
TEST_F(SmallBSTFixture, SMALL_DELETE4) {
    ASSERT_TRUE(bst.deleteNode(4));
    ASSERT_TRUE(bst.deleteNode(1));
    // ASSERT_EQ(bst.height(), 4);
}

// testing deleteNode for an inserted node
TEST_F(SmallBSTFixture, SMALL_DELETE5) {
    bst.insert(2);
    ASSERT_TRUE(bst.deleteNode(2));
    // ASSERT_EQ(bst.height(), 4);
}

TEST_F(SmallBSTFixture, SMALL_DELETE6) {
    bst.insert(2);
    ASSERT_TRUE(bst.deleteNode(1));
    ASSERT_EQ(3, *bst.find(3));
    ASSERT_EQ(100, *bst.find(100));
    ASSERT_EQ(-33, *bst.find(-33));
    ASSERT_EQ(4, *bst.find(4));
}