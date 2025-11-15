#pragma once
#include "TEmployee.h"

class TAVLTree {
private:
    struct TNode {
        int key;
        TEmployee* data;
        TNode* left;
        TNode* right;
        int height;

        TNode(int k, TEmployee* d);
    };

    TNode* root;

    int getHeight(TNode* node) const;
    int getBalanceFactor(TNode* node) const;
    void updateHeight(TNode* node);

    TNode* leftRotate(TNode* x);
    TNode* rightRotate(TNode* y);

    TNode* insertRecursive(TNode* node, int key, TEmployee* data);
    TNode* searchRecursive(TNode* node, int key) const;

    void inorderRecursive(TNode* node) const;
    void preorderRecursive(TNode* node) const;
    void postorderRecursive(TNode* node) const;

    void printEmployee(const TEmployee* e) const;
    void destroyRecursive(TNode* node);

public:
    TAVLTree();
    ~TAVLTree();

    void insert(int key, TEmployee* data);
    TEmployee* search(int key) const;

    void inorder() const;
    void preorder() const;
    void postorder() const;
    void levelOrder() const;
};