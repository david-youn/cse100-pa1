/**
 * Names: David Youn A15452585
 *        Jonathun Yun A15431969
 * Emails: dayoun@ucsd.edu
 *         j3yun@ucsd.edu
 * Sources: Stepik textbook
 *
 * This file contains the class and properties of the BSTIterator. It is
 * used in conjunction with the other two files BST.hpp and BSTNode.hpp.
 */
#ifndef BSTITERATOR_HPP
#define BSTITERATOR_HPP
#include <iterator>
#include <list>
#include "BSTNode.hpp"

using namespace std;

/**
 * This class contains the properties for a BSTIterator and overrides operators
 * such as pre-increment, post-increment, deference, equals, and not equals. It
 * also contains the instance variable curr, which describes the current
 * BSTNode.
 */
template <typename Data>
class BSTIterator : public iterator<input_iterator_tag, Data> {
  private:
    BSTNode<Data>* curr;

  public:
    /**
     * Constructor that initialize the current BSTNode
     * in this BSTIterator.
     */
    BSTIterator(BSTNode<Data>* curr) : curr(curr) {}

    /** Dereference operator. */
    Data operator*() const { return curr->getData(); }

    /** Pre-increment operator. */
    BSTIterator<Data>& operator++() {
        curr = curr->successor();
        return *this;
    }

    /** Post-increment operator. */
    BSTIterator<Data> operator++(int) {
        BSTIterator before = BSTIterator(curr);
        ++(*this);
        return before;
    }

    /**
     * Overrides the boolean equals operator
     * Parameter(s): other - the other data to compare the current data to
     * Returns whether or not the data is equal to the current data
     */
    bool operator==(BSTIterator<Data> const& other) const {
        return (curr == other.curr);
    }

    /**
     * Overrides the boolean not equals operator
     * Parameter(s): other - the other data to compare the current data to
     * Returns whether or not the data is not equal to the current data
     */
    bool operator!=(BSTIterator<Data> const& other) const {
        return (curr != other.curr);
    }
};

#endif  // BSTITERATOR_HPP