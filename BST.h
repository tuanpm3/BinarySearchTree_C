/**
* @file        BST.h
* @author    TuanPM3
* @date        12/Nov/2018
* @brief    Binary Search Tree template header
*/

#ifndef  _BST_H_
#define _BST_H_

#include <stdlib.h>
#include <algorithm>
#include <stack>
#include <vector>

using namespace std;

/*
* TreeNode
*/
template<typename T>
struct TreeNode
{
    T key;
    struct TreeNode *left, *right;
};

/**
* Binary Search Tree
*/
template<typename T>
class Bst {
private:
    TreeNode<T>* mRootNode;

    TreeNode<T>* addInternal(TreeNode<T> *node, T key) {
        /* If the tree is empty, return a new node */
        if (node == NULL) return newNode(key);

        /* Otherwise, recursive down the tree */
        if (key < node->key)
            node->left = addInternal(node->left, key);
        else if (key > node->key)
            node->right = addInternal(node->right, key);

        /* return current node pointer */
        return node;
    }

    static TreeNode<T>* newNode(T key) {
        TreeNode<T> *node = new TreeNode<T>;
        node->key = key;
        node->left = NULL;
        node->right = NULL;
        return node;
    }

public:
    class BstIteratorBase : public std::iterator<std::bidirectional_iterator_tag, T> {
    public:
        friend class Bst;
        BstIteratorBase() {};

        bool operator== (const BstIteratorBase& rhs) const { return mCurrNode == rhs.mCurrNode; };
        bool operator!= (const BstIteratorBase& rhs) const { return mCurrNode != rhs.mCurrNode; };
        const T& operator* () const { return mCurrNode->key; };

        // preincrement. move forward to next larger value
        BstIteratorBase& operator++ () {
            if (mCurrIndex < mTreeNodeArray.size()) mCurrNode = mTreeNodeArray[++mCurrIndex];
            return *this;
        }

        // preincrement. move forward to next larger value
        BstIteratorBase& operator++ (int) {
            if (mCurrIndex < mTreeNodeArray.size()) mCurrNode = mTreeNodeArray[++mCurrIndex];
            return *this;
        }

        // predecrement. move backward to largest value < current value
        BstIteratorBase& operator-- () {
            if (mCurrIndex > 0) mCurrNode = mTreeNodeArray[--mCurrIndex];
            return *this;
        }

        // predecrement. move backward to largest value < current value
        BstIteratorBase& operator-- (int) {
            if (mCurrIndex > 0) mCurrNode = mTreeNodeArray[--mCurrIndex];
            return *this;
        }

    protected:
        vector<TreeNode<T>*> mTreeNodeArray;
        int mCurrIndex;
        TreeNode<T> *mCurrNode;
        virtual void traversing(TreeNode<T> *node) {}

        void setRoot(TreeNode<T> *root) {
            if (root == NULL) return;
            traversing(root);
            mTreeNodeArray.push_back(NULL);
            mCurrIndex = 0;
            mCurrNode = mTreeNodeArray[mCurrIndex];
        }
    };

    /**
    * Preorder iterator
    */
    class BstPreorderIterator : public BstIteratorBase {
    public:
        BstPreorderIterator() {};

    private:
        friend class Bst;

        /**
        * Traverse in pre-order
        */
        void traversing(TreeNode<T> *root) {
            // Create an empty stack and push root to it 
            stack<TreeNode<T>*> nodeStack;
            nodeStack.push(root);

            while (!nodeStack.empty())
            {
                // Pop the top item from stack and print it 
                struct TreeNode<T> *node = nodeStack.top();
                mTreeNodeArray.push_back(node);
                nodeStack.pop();

                // Push right and left children of the popped node to stack 
                if (node->right)
                    nodeStack.push(node->right);
                if (node->left)
                    nodeStack.push(node->left);
            }
        }
    };

    /**
    * Inorder iterator
    */
    class BstInorderIterator : public BstIteratorBase {
    public:
        BstInorderIterator() {};

    private:
        friend class Bst;

        /**
        * Traverse in in-order
        */
        void traversing(TreeNode<T> *node) {
            if (node != NULL) {
                if (node->left) traversing(node->left);
                mTreeNodeArray.push_back(node);
                if (node->right) traversing(node->right);
            }
        }
    };

    /*
    * Postorder iterator
    */
    class BstPostorderIterator : public BstIteratorBase {
    public:
        BstPostorderIterator() {};

    private:
        friend class Bst;

        /**
        * Traverse in post-order
        */
        void traversing(TreeNode<T> *node) {
            if (node != NULL) {
                if (node->left) traversing(node->left);
                if (node->right) traversing(node->right);
                mTreeNodeArray.push_back(node);
            }
        }
    };

    Bst() : mRootNode(NULL) {}
    ~Bst() {
        auto itIn = this->beginInorder();
        for (; itIn != this->endInorder(); itIn++) {
            delete itIn.mCurrNode;
        }
    }

    /**
    *  Inserts a new element into the tree (preserving the binary search tree's invariant) 
    */
    void add(T key) {
        if (mRootNode == NULL) {
            mRootNode = newNode(key);
        }
        else {
            addInternal(mRootNode, key);
        }
    }

    /**
    *  Search element by key in the tree
    */
    TreeNode<T>* search(T key) {
        if (NULL == mRootNode) return NULL;

        TreeNode<T>* currentNode = mRootNode;

        while (currentNode) {
            if (key < currentNode->key)
                currentNode = currentNode->left;
            else if (key > currentNode->key)
                currentNode = currentNode->right;
            else
                return currentNode;
        }

        return NULL;
    }

    /**
    * Returns an iterator referring to the first element in the BST container in pre-order.
    */
    BstPreorderIterator beginPreorder() {
        BstPreorderIterator it;
        it.setRoot(mRootNode);
        return it;
    };

    /**
    * Returns an iterator referring to the past-the-end element in the BST container.
    */
    BstPreorderIterator endPreorder() {
        BstPreorderIterator it;
        it.mCurrNode = NULL;
        return it;
    }

    /**
    * Returns an iterator referring to the first element in the BST container in in-order.
    */
    BstInorderIterator beginInorder() {
        BstInorderIterator it;
        it.setRoot(mRootNode);
        return it;
    };

    /**
    * Returns an iterator referring to the past-the-end element in the BST container.
    */
    BstInorderIterator endInorder() {
        BstInorderIterator it;
        it.mCurrNode = NULL;
        return it;
    }

    /**
    * Returns an iterator referring to the first element in the BST container in post-order.
    */    
    BstPostorderIterator beginPostorder() {
        BstPostorderIterator it;
        it.setRoot(mRootNode);
        return it;
    };

    /**
    * Returns an iterator referring to the past-the-end element in the BST container.
    */
    BstPostorderIterator endPostorder() {
        BstPostorderIterator it;
        it.mCurrNode = NULL;
        return it;
    }

    TreeNode<T>* getroot() {
        return mRootNode;
    }
};

#endif // _BST_H_
