#include "AVLTree.h"
#include <iostream>
#include <queue>

TAVLTree::TNode::TNode(int k, TEmployee* d)
    : key(k), data(d), left(nullptr), right(nullptr), height(1) {}

TAVLTree::TAVLTree()
    : root(nullptr) {}

TAVLTree::~TAVLTree() {
    destroyRecursive(root);
}

void TAVLTree::destroyRecursive(TNode* node) {
    if (!node) return;
    destroyRecursive(node->left);
    destroyRecursive(node->right);
    delete node;
}

int TAVLTree::getHeight(TNode* node) const {
    return node ? node->height : 0;
}

int TAVLTree::getBalanceFactor(TNode* node) const {
    if (!node) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void TAVLTree::updateHeight(TNode* node) {
    if (!node) return;
    int lh = getHeight(node->left);
    int rh = getHeight(node->right);
    node->height = (lh > rh ? lh : rh) + 1;
}

TAVLTree::TNode* TAVLTree::rightRotate(TNode* y) {
    TNode* x = y->left;
    TNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

TAVLTree::TNode* TAVLTree::leftRotate(TNode* x) {
    TNode* y = x->right;
    TNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

TAVLTree::TNode* TAVLTree::insertRecursive(TNode* node, int key, TEmployee* data) {
    if (!node) {
        return new TNode(key, data);
    }

    if (key < node->key) {
        node->left = insertRecursive(node->left, key, data);
    } else if (key > node->key) {
        node->right = insertRecursive(node->right, key, data);
    } else {
        // duplicate key, ignore
        return node;
    }

    updateHeight(node);

    int balance = getBalanceFactor(node);

    // LL
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }
    // RR
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }
    // LR
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // RL
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

TAVLTree::TNode* TAVLTree::searchRecursive(TNode* node, int key) const {
    if (!node || node->key == key) {
        return node;
    }
    if (key < node->key) {
        return searchRecursive(node->left, key);
    }
    return searchRecursive(node->right, key);
}

void TAVLTree::printEmployee(const TEmployee* e) const {
    if (!e) return;
    std::cout << "ID: " << e->employeeId
              << " | " << e->firstName << " " << e->lastName << "\n";
}

void TAVLTree::inorderRecursive(TNode* node) const {
    if (!node) return;
    inorderRecursive(node->left);
    printEmployee(node->data);
    inorderRecursive(node->right);
}

void TAVLTree::preorderRecursive(TNode* node) const {
    if (!node) return;
    printEmployee(node->data);
    preorderRecursive(node->left);
    preorderRecursive(node->right);
}

void TAVLTree::postorderRecursive(TNode* node) const {
    if (!node) return;
    postorderRecursive(node->left);
    postorderRecursive(node->right);
    printEmployee(node->data);
}

void TAVLTree::insert(int key, TEmployee* data) {
    root = insertRecursive(root, key, data);
}

TEmployee* TAVLTree::search(int key) const {
    TNode* node = searchRecursive(root, key);
    return node ? node->data : nullptr;
}

void TAVLTree::inorder() const {
    inorderRecursive(root);
}

void TAVLTree::preorder() const {
    preorderRecursive(root);
}

void TAVLTree::postorder() const {
    postorderRecursive(root);
}

void TAVLTree::levelOrder() const {
    if (!root) return;

    std::queue<TNode*> q;
    q.push(root);

    while (!q.empty()) {
        TNode* current = q.front();
        q.pop();

        printEmployee(current->data);

        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
}