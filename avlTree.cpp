#include "avlTree.h"
#include <iostream>
using namespace std;

template <typename T>
avlTree<T>::avlTree() : root(nullptr) {}

template <typename T>
avlTree<T>::~avlTree() {
    if (root != nullptr) {
        deleteSubtree(root);
    }
}

template <typename T>
int avlTree<T>::height(avlNode<T>* node) {
    if (node == nullptr) return 0;
    return node->height;
}

template <typename T>
int avlTree<T>::balanceFactor(avlNode<T>* node) {
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}

template <typename T>
avlNode<T>* avlTree<T>::rotateRight(avlNode<T>* y) {
    avlNode<T>* x = y->left;
    avlNode<T>* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    return x;
}

template <typename T>
avlNode<T>* avlTree<T>::rotateLeft(avlNode<T>* x) {
    avlNode<T>* y = x->right;
    avlNode<T>* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    return y;
}

template <typename T>
avlNode<T>* avlTree<T>::insertUtil(avlNode<T>* node, T key) {
    if (node == nullptr) return new avlNode<T>(key);
    if (key < node->data)
        node->left = insertUtil(node->left, key);
    else if (key > node->data)
        node->right = insertUtil(node->right, key);
    else
        return node;

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = balanceFactor(node);

    // Left Left Case
    if (balance > 1 && key < node->left->data)
        return rotateRight(node);

    // Right Right Case
    if (balance < -1 && key > node->right->data)
        return rotateLeft(node);

    // Left Right Case
    if (balance > 1 && key > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

template <typename T>
void avlTree<T>::insert(T key) {
    root = insertUtil(root, key);
}

template <typename T>
avlNode<T>* avlTree<T>::minValueNode(avlNode<T>* node) {
    avlNode<T>* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

template <typename T>
avlNode<T>* avlTree<T>::removeUtil(avlNode<T>* root, T key) {
    if (root == nullptr) return root;

    if (key < root->data)
        root->left = removeUtil(root->left, key);
    else if (key > root->data)
        root->right = removeUtil(root->right, key);
    else {
        if (root->left == nullptr || root->right == nullptr) {
            avlNode<T>* temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else
                *root = *temp;

            delete temp;
        }
        else {
            avlNode<T>* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = removeUtil(root->right, temp->data);
        }
    }

    if (root == nullptr) return root;

    root->height = 1 + std::max(height(root->left), height(root->right));

    int balance = balanceFactor(root);

    // Left Left Case
    if (balance > 1 && balanceFactor(root->left) >= 0)
        return rotateRight(root);

    // Left Right Case
    if (balance > 1 && balanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right Right Case
    if (balance < -1 && balanceFactor(root->right) <= 0)
        return rotateLeft(root);

    // Right Left Case
    if (balance < -1 && balanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

template <typename T>
void avlTree<T>::remove(T key) {
    root = removeUtil(root, key);
}

template <typename T>
bool avlTree<T>::search(T key) {
    avlNode<T>* current = root;
    while (current != nullptr) {
        if (key == current->data)
            return true;
        else if (key < current->data)
            current = current->left;
        else
            current = current->right;
    }
    return false;
}
