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
        cout << "item value: " << item_ptr->getData() << endl;
        cout << "root: " << root->getData() << endl;
        // if there is no root
        if (root == 0) {
            cout << "no root" << endl;
            root = item_ptr;
            return true;
        }
        BSTNode<Data>* ptr = root;
        BSTNode<Data>* next_ptr = nullptr;
        int count = 0;
        while (ptr != nullptr) {
            // checking if the data is equal to items value
            if (item < ptr->getData() && !(item < ptr->getData())) {
                cout << "shd do the false" << endl;
                return false;
            }
            count++;
            cout << "run #" << count << "ptr's data value " << ptr->getData()
                 << endl;
            next_ptr = ptr;
            // if item is smaller than current node's data
            if (item < ptr->getData()) {
                cout << "item smaller on run " << count << endl;
                ptr = ptr->left;
            }
            // if item is larger than current node's data
            else if (!(item < ptr->getData())) {
                cout << "item larger on run " << count << endl;
                ptr = ptr->right;
            }
        }
        if (item < next_ptr->getData()) {
            next_ptr->left = item_ptr;
        } else if (!(item < next_ptr->getData())) {
            next_ptr->right = item_ptr;
        } else {
            return false;
        }
        return true;
    }

    /** TODO */
    iterator find(const Data& item) const { return 0; }

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
