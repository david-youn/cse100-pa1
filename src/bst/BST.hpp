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
    BST(const BST<Data>& bst) : root(0), isize(0), iheight(-1) {
        vector<Data> vect = bst.inorder();
        root = buildSubtree(vect, 0, vect.size() - 1, -1);
        isize = bst.size();
    }

    /** TODO */
    ~BST() {
        deleteAll(root);
        root = 0;
        isize = 0;
        iheight = -1;
    }

    /** TODO */
    bool insert(const Data& item) {
        BSTNode<Data>* item_ptr = new BSTNode<Data>(item);
        // if there is no root
        if (root == 0 || root == nullptr) {
            root = item_ptr;
            isize = isize + 1;
            iheight = iheight + 1;
            return true;
        }
        BSTNode<Data>* ptr = root;
        BSTNode<Data>* prev_ptr = nullptr;

        int edgeCount = 0;
        while (ptr != nullptr) {
            prev_ptr = ptr;
            // checking if the data is equal to items value
            if (!(item < ptr->getData()) && !(ptr->getData() < item)) {
                delete (item_ptr);
                return false;
            }
            // if item is smaller than current node's data
            if (item < ptr->getData()) {
                ptr = ptr->left;
                edgeCount++;
            }
            // if item is larger than current node's data
            else {
                ptr = ptr->right;
                edgeCount++;
            }
        }
        if (!(item < prev_ptr->getData()) && !(prev_ptr->getData() < item)) {
            delete (item_ptr);
            return false;
        }
        if (item < prev_ptr->getData()) {
            prev_ptr->left = item_ptr;
            item_ptr->parent = prev_ptr;
            isize = isize + 1;
            if (iheight < edgeCount) {
                iheight = edgeCount;
            }

        } else {
            prev_ptr->right = item_ptr;
            item_ptr->parent = prev_ptr;
            isize = isize + 1;
            if (iheight < edgeCount) {
                iheight = edgeCount;
            }
        }
        return true;
    }

    /** TODO */
    iterator find(const Data& item) const {
        BSTNode<Data>* find_ptr = root;
        while (
            !(!(find_ptr->getData() < item) && !(item < find_ptr->getData()))) {
            if (item < find_ptr->getData()) {
                find_ptr = find_ptr->left;
            } else if (find_ptr->getData() < item) {
                find_ptr = find_ptr->right;
            }
            if (find_ptr == nullptr) {
                return typename BST<Data>::iterator(find_ptr);
            }
        }
        return typename BST<Data>::iterator(find_ptr);
    }

    /** TODO */
    bool deleteNode(const Data& item) { return false; }

    /** TODO */
    unsigned int size() const { return isize; }

    /** TODO */
    int height() const { return iheight; }

    /** TODO */
    bool empty() const { return (isize == 0); }

    /** TODO */
    iterator begin() const { return typename BST<Data>::iterator(first(root)); }

    /** Return an iterator pointing past the last item in the BST. */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /** TODO */
    vector<Data> inorder() const {
        std::vector<Data> ivector(isize);
        BSTNode<Data>* curr = first(root);
        Data* pos = ivector.data();
        while (curr != nullptr) {
            *pos = curr->getData();
            pos++;
            curr = inorderHelper(curr);
        }
        return ivector;
    }

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
    // Helper function for inorder()
    static BSTNode<Data>* inorderHelper(BSTNode<Data>* inode) {
        // Referenced pseudocode from Stepik resource
        BSTNode<Data>* current = nullptr;
        // case 1: node has a right child
        if (inode->right != nullptr) {
            current = inode->right;
            while (current->left != nullptr) {
                current = current->left;
            }
            return current;
        }
        // case 2: node does not have a right child
        else {
            current = inode;
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

    /** TODO Helper function for begin() */
    static BSTNode<Data>* first(BSTNode<Data>* root) {
        BSTNode<Data>* first_ptr = root;
        BSTNode<Data>* pre_ptr = nullptr;
        while (first_ptr != nullptr) {
            pre_ptr = first_ptr;
            first_ptr = first_ptr->left;
        }
        return pre_ptr;
    }

    /** TODO */
    static void deleteAll(BSTNode<Data>* n) {
        if (n == nullptr) {
            return;
        }
        deleteAll(n->left);
        deleteAll(n->right);
        delete (n);
        n = nullptr;

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
        if (start > end) {
            return nullptr;
        }

        // depth used to be new iheight value
        int median = ((end - start + 1) / 2) + start;
        BSTNode<Data>* node = new BSTNode<Data>(data.at(median));

        depth = depth + 1;
        if (depth > iheight) {
            iheight = depth;
        }
        node->left = buildSubtree(data, start, median - 1, depth);
        node->right = buildSubtree(data, median + 1, end, depth);
        return node;
    }

    // Add more helper functions below
};

#endif  // BST_HPP
