/**
 * TODO: add file header
 */
#ifndef BST_HPP
#define BST_HPP
#include <iostream>
#include <queue>
#include <vector>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"
using namespace std;

/**
 * TODO: add class header
 */
template <typename Data>
class BST {
  protected:
    // pointer to the root of this BST, or 0 if the BST is empty
    BSTNode<Data>* root;

    // number of Data items stored in this BST.
    unsigned int isize;

    // height of this BST.
    int iheight;

  public:
    /** Define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /**
     * Default constructor.
     * Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(-1) {}

    /** TODO */
    BST(const BST<Data>& bst) : root(0), isize(0), iheight(-1) {}

    /** TODO */
    ~BST() {}

    /** TODO */
    bool insert(const Data& item) {
        BSTNode<Data>* item_ptr = new BSTNode<Data>(item);
        // if there is no root
        if (root == 0 || root == nullptr) {
            root = item_ptr;
            return true;
        }
        BSTNode<Data>* ptr = root;
        BSTNode<Data>* prev_ptr = nullptr;
        while (ptr != nullptr) {
            prev_ptr = ptr;
            // checking if the data is equal to items value
            if (!(item < ptr->getData()) && !(ptr->getData() < item)) {
                return false;
            }
            // if item is smaller than current node's data
            if (item < ptr->getData()) {
                ptr = ptr->left;
            }
            // if item is larger than current node's data
            else {
                ptr = ptr->right;
            }
        }
        if (!(item < prev_ptr->getData()) && !(prev_ptr->getData() < item)) {
            return false;
        }
        if (item < prev_ptr->getData()) {
            prev_ptr->left = item_ptr;
        } else {
            prev_ptr->right = item_ptr;
        }
        return true;
    }

    /** TODO */
    iterator find(const Data& item) const {
        BSTNode<Data>* find_ptr = root;
        while (find_ptr != nullptr) {
            // checking if the data is equal to items value
            if (!(item < find_ptr->getData() &&
                  !(find_ptr->getData() < item))) {
                break;
            }
            // if item is smaller than current node's data
            if (item < find_ptr->getData()) {
                find_ptr = find_ptr->left;
            }
            // if item is larger than current node's data
            else {
                find_ptr = find_ptr->right;
            }
        }
        return typename BST<Data>::iterator(find_ptr);
    }

    /** TODO */
    bool deleteNode(const Data& item) { return false; }

    /** TODO */
    unsigned int size() const { return 0; }

    /** TODO */
    int height() const { return 0; }

    /** TODO */
    bool empty() const { return false; }

    /** TODO */
    iterator begin() const { return 0; }

    /** Return an iterator pointing past the last item in the BST. */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /** TODO */
    vector<Data> inorder() const {}

    /**
     * DO NOT CHANGE THIS METHOD
     * Prints a tree, including its structure to an
     * output stream to help with grading and debugging.
     */
    void print(ostream* out) {
        if (empty()) {
            *out << "(Empty tree)" << endl;
            return;
        }

        // Using a queue to traverse a tree is otherwise
        // known as a breadth first traversal of the tree.
        // It's useful here to show which nodes are on which
        // level.
        queue<BSTNode<Data>*> toVisit;
        toVisit.push(root);
        int nodesPerLevel = 1;
        int totalSpacing = 1 << iheight;

        for (int i = 0; i <= iheight; i++) {
            for (int j = 0; j < nodesPerLevel; j++) {
                BSTNode<Data>* curr = toVisit.front();
                toVisit.pop();
                if (curr == nullptr) {
                    *out << "X";
                    // If we have an entire missing subtree, we
                    // would like to print X's in place of all
                    // nodes because it avoids ambiguity
                    toVisit.push(nullptr);
                    toVisit.push(nullptr);
                } else {
                    *out << curr->getData();
                    toVisit.push(curr->left);
                    toVisit.push(curr->right);
                }
                for (int k = 0; k < totalSpacing / nodesPerLevel; k++) {
                    *out << "\t";
                }
            }
            *out << endl;
            nodesPerLevel *= 2;
        }
    }

  private:
    /** TODO Helper function for begin() */
    static BSTNode<Data>* first(BSTNode<Data>* root) { return 0; }

    /** TODO */
    static void deleteAll(BSTNode<Data>* n) {
        /* Pseudocode:
           if current node is null: return;
           recursively delete left sub-tree
           recursively delete right sub-tree
           delete current node
        */
    }

    /** TODO */
    BSTNode<Data>* buildSubtree(vector<Data>& data, int start, int end,
                                int depth) {
        return 0;
    }

    // Add more helper functions below
};

#endif  // BST_HPP
