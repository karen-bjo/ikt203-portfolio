#pragma once
#include "TEmployee.h"

class TBST
{
private:
    struct TNode
    {
        int key;
        TEmployee* data;
        TNode* left;
        TNode* right;

        TNode(int k, TEmployee* d);
    };

    TNode* root;

    TNode* insertRecursive(TNode* node, int key, TEmployee* data);
    TNode* searchRecursive(TNode* node, int key) const;
    TNode* deleteRecursive(TNode* node, int key);
    TNode* findMin(TNode* node);

    void inorderRecursive(TNode* node) const;
    void preorderRecursive(TNode* node) const;
    void postorderRecursive(TNode* node) const;

    void printEmployee(const TEmployee* e) const;
    void destroyRecursive(TNode* node);

public:
    TBST();
    ~TBST();

    void insert(int key, TEmployee* data);
    void deleteKey(int key);
    TEmployee* search(int key) const;

    void inorder() const;
    void preorder() const;
    void postorder() const;
    void levelOrder() const;
};