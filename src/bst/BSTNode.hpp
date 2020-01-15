/**
 * TODO: add file header
 */
#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iomanip>
#include <iostream>
using namespace std;

/**
 * TODO: add class header
 */
template <typename Data>
class BSTNode {
  private:
    Data data;

  public:
    BSTNode<Data>* left;
    BSTNode<Data>* right;
    BSTNode<Data>* parent;

    /** TODO */
    BSTNode(const Data& d) : data(d) { left = right = parent = nullptr; }

    /** Set the value of data */
    void setData(const Data& d) { data = d; }

    /** Get the value of data */
    Data getData() { return data; }

    /** TODO */
    BSTNode<Data>* successor() {
        // Referenced pseudocode from Stepik resource
        BSTNode<Data>* current = nullptr;
        // case 1: node has a right child
        if (right != nullptr) {
            current = right;
            while (current->left != nullptr) {
                current = current->left;
            }
            return current;
        }
        // case 2: node does not have a right child
        else {
            current = this;
            while (current->parent != nullptr) {
                if (current == current->parent->left) {
                    return current->parent;
                } else {
                    current = current->parent;
                }
            }
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
