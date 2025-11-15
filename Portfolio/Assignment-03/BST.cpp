#include "BST.h"
#include <iostream>
#include <queue>

TBST::TNode::TNode(int k, TEmployee* d)
    : key(k), data(d), left(nullptr), right(nullptr) {}

TBST::TBST()
    : root(nullptr) {}

TBST::~TBST() {
    destroyRecursive(root);
}

void TBST::destroyRecursive(TNode* node) {
    if (!node) return;
    destroyRecursive(node->left);
    destroyRecursive(node->right);
    delete node;
}

TBST::TNode* TBST::insertRecursive(TNode* node, int key, TEmployee* data) {
    if (!node) {
        return new TNode(key, data);
    }

    if (key < node->key) {
        node->left = insertRecursive(node->left, key, data);
    } else if (key > node->key) {
        node->right = insertRecursive(node->right, key, data);
    }
    // duplicate keys are ignored
    return node;
}

TBST::TNode* TBST::searchRecursive(TNode* node, int key) const {
    if (!node || node->key == key) {
        return node;
    }
    if (key < node->key) {
        return searchRecursive(node->left, key);
    }
    return searchRecursive(node->right, key);
}

TBST::TNode* TBST::findMin(TNode* node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

TBST::TNode* TBST::deleteRecursive(TNode* node, int key) {
    if (!node) return nullptr;

    if (key < node->key) {
        node->left = deleteRecursive(node->left, key);
    } else if (key > node->key) {
        node->right = deleteRecursive(node->right, key);
    } else {
        // found node to delete
        if (!node->left && !node->right) {
            delete node;
            return nullptr;
        } else if (!node->left) {
            TNode* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            TNode* temp = node->left;
            delete node;
            return temp;
        } else {
            TNode* succ = findMin(node->right);
            node->key = succ->key;
            node->data = succ->data;
            node->right = deleteRecursive(node->right, succ->key);
        }
    }
    return node;
}

void TBST::printEmployee(const TEmployee* e) const {
    if (!e) return;
    std::cout << "ID: " << e->employeeId
              << " | " << e->firstName << " " << e->lastName << "\n";
}

void TBST::inorderRecursive(TNode* node) const {
    if (!node) return;
    inorderRecursive(node->left);
    printEmployee(node->data);
    inorderRecursive(node->right);
}

void TBST::preorderRecursive(TNode* node) const {
    if (!node) return;
    printEmployee(node->data);
    preorderRecursive(node->left);
    preorderRecursive(node->right);
}

void TBST::postorderRecursive(TNode* node) const {
    if (!node) return;
    postorderRecursive(node->left);
    postorderRecursive(node->right);
    printEmployee(node->data);
}

void TBST::insert(int key, TEmployee* data) {
    root = insertRecursive(root, key, data);
}

void TBST::deleteKey(int key) {
    root = deleteRecursive(root, key);
}

TEmployee* TBST::search(int key) const {
    TNode* node = searchRecursive(root, key);
    return node ? node->data : nullptr;
}

void TBST::inorder() const {
    inorderRecursive(root);
}

void TBST::preorder() const {
    preorderRecursive(root);
}

void TBST::postorder() const {
    postorderRecursive(root);
}

void TBST::levelOrder() const {
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