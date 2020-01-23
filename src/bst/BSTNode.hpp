/**
 * Names: David Youn A15452585
 *        Jonathun Yun A15431969
 * Emails: dayoun@ucsd.edu
 *         j3yun@ucsd.edu
 * Sources: Stepik textbook
 *
 * This file contains the class and therefore the properties for a single node
 * within the Binary Search Tree. This file is used in conjunction with the
 * other two files BST.hpp and BSTIterator.hpp.
 */
#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iomanip>
#include <iostream>
using namespace std;

/**
 * This class contains the functions and variables used to create the object
 * BSTNode. It contains the instance variables left, right, and parent as
 * well as data in order to define the object.
 */
template <typename Data>
class BSTNode {
  private:
    Data data;

  public:
    BSTNode<Data>* left;
    BSTNode<Data>* right;
    BSTNode<Data>* parent;

    /**
     * Default constructor for a Node
     * Parameter(s): d - the Data that the node contains
     */
    BSTNode(const Data& d) : data(d) { left = right = parent = nullptr; }

    /** Set the value of data */
    void setData(const Data& d) { data = d; }

    /** Get the value of data */
    Data getData() { return data; }

    /**
     * Returns the next lowest greater number than the current node
     * Parameter(s): none
     */
    BSTNode<Data>* successor() {
        // Referenced pseudocode from Stepik resource
        BSTNode<Data>* current = nullptr;
        // if node has a right child
        if (right != nullptr) {
            current = right;
            // iterate down the left until smallest node is found
            while (current->left != nullptr) {
                current = current->left;
            }
            return current;
            // if node does not have a right child
        } else {
            current = this;
            // traverse up the tree until parent's left is found
            while (current->parent != nullptr) {
                if (current == current->parent->left) {
                    return current->parent;
                } else {
                    current = current->parent;
                }
            }
            // if there was no successor
            return nullptr;
        }
    }
};

/**
 * DO NOT CHANGE THIS METHOD
 * Overload operator<< to print a BSTNode's fields to an ostream.
 */
template <typename Data>
ostream& operator<<(ostream& stm, const BSTNode<Data>& n) {
    stm << '[';
    stm << setw(10) << &n;                  // address of the BSTNode
    stm << "; p:" << setw(10) << n.parent;  // address of its parent
    stm << "; l:" << setw(10) << n.left;    // address of its left child
    stm << "; r:" << setw(10) << n.right;   // address of its right child
    stm << "; d:" << n.data;                // its data field
    stm << ']';
    return stm;
}

#endif  // BSTNODE_HPP