/**
 * Names: David Youn A15452585
 *        Jonathun Yun A15431969
 * Emails: dayoun@ucsd.edu
 *         j3yun@ucsd.edu
 * Sources: Stepik textbook
 *
 * This file contains the class and properties of the whole Binary Search Tree.
 * It uses the other files BSTNode.hpp as well as BSTIterator.hpp in order to
 * create a BST that can balance, insert values, delete values, find values,
 * return its properties, and print.
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
 * This class contains the variables and functions used by the BST object
 * which includes functions that balance, insert values, delete values,
 * find values, return properties, and print. The instance variables include
 * the root of the tree, the size, the height, and the iterator.
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

    /**
     * Copy constructor that creates a balanced BST using the given BST.
     * Parameter(s): bst - the BST to copy and reconstruct into a balanced BST.
     */
    BST(const BST<Data>& bst) : root(0), isize(0), iheight(-1) {
        vector<Data> vect = bst.inorder();
        root = buildSubtree(vect, 0, vect.size() - 1, -1);
        isize = bst.size();
    }

    /**
     * Destructor that deletes the whole BST.
     * Parameter(s): none
     * Resets the variables of the BST to the default values.
     */
    ~BST() {
        // calls helper function to delete every node in the BST.
        deleteAll(root);
        root = 0;
        isize = 0;
        iheight = -1;
    }

    /**
     * Inserts a new BSTNode which contains the given data into the proper
     * space in the BST. Does not allow duplicate insertion.
     * Parameter(s): item - the data for the new BSTNode to insert into the BST
     * Return: boolean whether or not the item was successfully added into
     * the BST
     */
    bool insert(const Data& item) {
        BSTNode<Data>* item_ptr = new BSTNode<Data>(item);
        // if there is no root create one
        if (root == 0 || root == nullptr) {
            root = item_ptr;
            isize = isize + 1;
            iheight = iheight + 1;
            return true;
        }
        BSTNode<Data>* ptr = root;
        BSTNode<Data>* prev_ptr = nullptr;

        int edgeCount = 0;
        // iterates down the BST into the proper place to insert the data
        while (ptr != nullptr) {
            prev_ptr = ptr;
            // checking if the data already exists within the BST
            if (!(item < ptr->getData()) && !(ptr->getData() < item)) {
                delete (item_ptr);
                return false;
            }
            // if item is smaller than current node's data
            if (item < ptr->getData()) {
                // iterate to the left of the BST
                ptr = ptr->left;
                edgeCount++;
            }
            // if item is larger than current node's data
            else {
                // iterate to the right of the BST
                ptr = ptr->right;
                edgeCount++;
            }
        }

        if (item < prev_ptr->getData()) {
            prev_ptr->left = item_ptr;
            item_ptr->parent = prev_ptr;
            isize = isize + 1;
            // updates height if height increased by insertion
            if (iheight < edgeCount) {
                iheight = edgeCount;
            }

        } else {
            prev_ptr->right = item_ptr;
            item_ptr->parent = prev_ptr;
            isize = isize + 1;
            // updates height if increased by insertion
            if (iheight < edgeCount) {
                iheight = edgeCount;
            }
        }
        return true;
    }

    /**
     * Finds the given data within the BST.
     * Parameter(s): item - the data needed to find within the BST
     * Return: BSTIterator pointing to the found item, or if not found,
     * pointing to past the last node in the BST
     */
    iterator find(const Data& item) const {
        BSTNode<Data>* find_ptr = root;
        // checks to see if BST exists
        if (isize == 0) {
            return typename BST<Data>::iterator(find_ptr);
        }
        // iterates through the BST as long as we have not reached the item
        // to find yet
        while (
            !(!(find_ptr->getData() < item) && !(item < find_ptr->getData()))) {
            // iterate down left of BST if data to find is less than the current
            // node
            if (item < find_ptr->getData()) {
                find_ptr = find_ptr->left;
                // iterate down right of BST if data to find is greater than
                // current node
            } else if (find_ptr->getData() < item) {
                find_ptr = find_ptr->right;
            }
            // if we reach the end of the BST before finding data, return
            // iterator
            if (find_ptr == nullptr) {
                return typename BST<Data>::iterator(find_ptr);
            }
        }
        // return the found node as BSTIterator
        return typename BST<Data>::iterator(find_ptr);
    }

    /**
     * Delete a node in the BST containing the given data.
     * Parameter(s): item - the data to search for and delete
     * Return: boolean of whether the data was successfully deleted from the
     * BST or not; returns false if data did not exist within the BST
     */
    bool deleteNode(const Data& item) {
        // empty bst
        if (isize == 0) {
            return false;
        }
        BSTNode<Data>* delete_ptr = root;
        // finding the node with the data item
        while (!(!(delete_ptr->getData() < item) &&
                 !(item < delete_ptr->getData()))) {
            if (item < delete_ptr->getData()) {
                delete_ptr = delete_ptr->left;
            } else if (delete_ptr->getData() < item) {
                delete_ptr = delete_ptr->right;
            }
            // if data did not exist within the BST
            if (delete_ptr == nullptr) {
                return false;
            }
        }
        // checking if deleting a root node with no children
        if (delete_ptr->parent == nullptr && delete_ptr->left == nullptr &&
            delete_ptr->right == nullptr) {
            delete (delete_ptr);
            root = nullptr;
            isize = 0;
            iheight = -1;
            return true;
        }
        // check if the node has no children
        if (delete_ptr->left == nullptr && delete_ptr->right == nullptr) {
            // check if current node is only right child
            if (delete_ptr->parent->left == nullptr) {
                // disconnect parent and current node
                delete_ptr->parent->right = nullptr;
                // check if current node is only left child
            } else if (delete_ptr->parent->right == nullptr) {
                // disconnect parent and current node
                delete_ptr->parent->left = nullptr;
                // check if current node is left child with right sibling
            } else if (!(delete_ptr->parent->left->getData() < item) &&
                       !(item < delete_ptr->parent->left->getData())) {
                // disconnect parent and current node
                delete_ptr->parent->left = nullptr;
                // check if current node is right child with left sibling
            } else {
                // disconnect parent and current node
                delete_ptr->parent->right = nullptr;
            }
            // dleete node and adjust properties for BST
            delete (delete_ptr);
            isize--;
            iheight = findHeight(root) - 1;
            return true;
        }
        // check if node has two children
        else if (delete_ptr->left != nullptr && delete_ptr->right != nullptr) {
            // hold successor's data
            Data temp = (delete_ptr->successor()->getData());
            // recurively call deleteNode to delete successor to prevent
            // duplication
            deleteNode(temp);
            // current node data is replaced with successor's data
            delete_ptr->setData(temp);
            // isize--; because isize gets updated in deleteNode(temp)
            iheight = findHeight(root) - 1;
            return true;
        }
        // otherwise node has one child
        else {
            // pointers to hold current node's child and current node's parent
            BSTNode<Data>* child_ptr;
            BSTNode<Data>* parent_ptr = delete_ptr->parent;
            // checks if current node is the root node
            if (parent_ptr == nullptr) {
                // checks if root has right child
                if (delete_ptr->left == nullptr) {
                    root = delete_ptr->right;
                    root->parent = nullptr;
                    // checks if root has left child
                } else {
                    root = delete_ptr->left;
                    root->parent = nullptr;
                }
                // checks if current node is the left child
            } else if (delete_ptr->parent->left == delete_ptr) {
                if (delete_ptr->left != nullptr) {
                    child_ptr = delete_ptr->left;
                } else {
                    child_ptr = delete_ptr->right;
                }
                child_ptr->parent = parent_ptr;
                parent_ptr->left = child_ptr;
                // checks if current node is the right child
            } else {
                if (delete_ptr->left != nullptr) {
                    child_ptr = delete_ptr->left;
                } else {
                    child_ptr = delete_ptr->right;
                }
                child_ptr->parent = parent_ptr;
                parent_ptr->right = child_ptr;
            }
            delete (delete_ptr);
            isize--;
            iheight = findHeight(root) - 1;
            return true;
        }
    }

    /**
     * Returns the size of the BST
     * Parameter(s): none
     * Return: unsigned int of the number of BSTNodes in the BST
     */
    unsigned int size() const { return isize; }

    /**
     * Returns the height of the BST
     * Parameter(s): none
     * Return: int of the height of the BST (from root to lowest child)
     */
    int height() const { return iheight; }

    /**
     * Returns whether or not the BST is empty
     * Paramter(s): none
     * Return: boolean of whether the BST is empty
     */
    bool empty() const { return (isize == 0); }

    /**
     * Returns the lowest element within the BST
     * Parameter(s): none
     * Return: BSTIterator pointing to the lowest value data in BST
     */
    iterator begin() const { return typename BST<Data>::iterator(first(root)); }

    /** Return an iterator pointing past the last item in the BST. */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /**
     * Returns an ordered list of all the elements in BST in ascending order
     * Parameter(s): none
     * Return: vector of type Data that contains every element in BST ordered
     * from least to greatest
     */
    vector<Data> inorder() const {
        // creates a vector that is the same size as the BST
        std::vector<Data> ivector(isize);
        BSTNode<Data>* curr = first(root);
        Data* pos = ivector.data();
        // iterates throught the vector and goes through the BST starting from
        // the first element
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
    /**
     * Helper method for the method inorder() that returns the next element
     * to put within the vector in inorder()
     * Parameter(s): inode - the current node for which the next node needs to
     * be found
     * Return: BSTNode pointer that points to the next smallest greater element
     */
    static BSTNode<Data>* inorderHelper(BSTNode<Data>* inode) {
        // Referenced pseudocode from Stepik resource
        BSTNode<Data>* current = nullptr;
        // case 1: node has a right child
        if (inode->right != nullptr) {
            current = inode->right;
            // go down the left side of the BST until reached leaf node
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

    /**
     * Helper function for begin() that gets the lowest element in the BST
     * Parameter(s): root - the root of the node that we must find the lowest
     * element for
     * Return: BSTNode pointer that points to the lowest element in the BST
     * */
    static BSTNode<Data>* first(BSTNode<Data>* root) {
        BSTNode<Data>* first_ptr = root;
        BSTNode<Data>* pre_ptr = nullptr;
        // iterates down the left side of the BST until we reach a leaf node
        while (first_ptr != nullptr) {
            pre_ptr = first_ptr;
            first_ptr = first_ptr->left;
        }
        return pre_ptr;
    }

    /**
     * Helper method for default destructor ~BST(). Recursively iterates
     * through the BST and deletes every node.
     * Parameter(s): n - pointer to the root of the BST
     */
    static void deleteAll(BSTNode<Data>* n) {
        if (n == nullptr) {
            return;
        }
        // recursively goes through the left sub-tree of the BST
        deleteAll(n->left);
        // recursively goes through the right sub-tree of the BST
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

    /**
     * Helper method for copy constructor BST(bst) that builds a subtree of
     * the BST recursively
     * Parameter(s): data - a vector of the data to use in the BST
     *               start - the start index of the vector to include in the
     *                       subtree
     *               end - the end index (exclusive) of the vector to stop the
     *                      subtree
     *               depth - the depth of the recursion which helps update the
     *                     variable height
     * Return: BSTNode pointer that points to the root node of the BST
     */
    BSTNode<Data>* buildSubtree(vector<Data>& data, int start, int end,
                                int depth) {
        if (start > end) {
            return nullptr;
        }
        // depth used to be new iheight value
        int median = ((end - start + 1) / 2) + start;
        BSTNode<Data>* node = new BSTNode<Data>(data.at(median));
        // updates height throughout recursive calls
        depth = depth + 1;
        if (depth > iheight) {
            iheight = depth;
        }
        // recursively call method to build sub-tree of left side of BST
        node->left = buildSubtree(data, start, median - 1, depth);
        if (node->left != nullptr) {
            // connects node to parent node
            node->left->parent = node;
        }
        // recursively call method to build sub-tree of right side of BST
        node->right = buildSubtree(data, median + 1, end, depth);
        if (node->right != nullptr) {
            // connects node to parent node
            node->right->parent = node;
        }
        return node;
    }

    /**
     * Helper method for delete() to properly update height after deleting node
     * Parameter(s): node -
     *
     */
    int findHeight(BSTNode<Data>* node) {
        if (node == nullptr) {
            return 0;
        } else {
            int leftHeight = 1 + findHeight(node->left);
            int rightHeight = 1 + findHeight(node->right);
            if (leftHeight > rightHeight) {
                return leftHeight;
            } else {
                return rightHeight;
            }
        }
    }
};

#endif  // BST_HPP