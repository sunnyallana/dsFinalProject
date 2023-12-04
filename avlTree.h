#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;

template <class dataType>
class avlNode {
public:
    dataType data;
    avlNode<dataType>* left;
    avlNode<dataType>* right;
    int height;

    avlNode(dataType receiveValue) : data(receiveValue), left(nullptr), right(nullptr), height(1) {}
};

template <class dataType>
class avlTree {
    avlNode<dataType>* root = nullptr;

    int height(avlNode<dataType>* node);
    int balanceFactor(avlNode<dataType>* node);
    avlNode<dataType>* rotateRight(avlNode<dataType>* y);
    avlNode<dataType>* rotateLeft(avlNode<dataType>* x);
    void deleteSubtree(avlNode<dataType>* node);

public:
    avlTree();
    ~avlTree();

    void insert(dataType key);
    void remove(dataType key);
    bool search(dataType key);
    void printInorder();
    bool isPasswordStrong(const dataType& password);
    void buildTreeFromDictionary(const string& dictionaryFileName);

private:
    avlNode<dataType>* insertUtil(avlNode<dataType>* node, dataType key);
    avlNode<dataType>* removeUtil(avlNode<dataType>* root, dataType key);
    avlNode<dataType>* minValueNode(avlNode<dataType>* node);
    void inorderUtil(avlNode<dataType>* node);
};

template <class dataType>
bool avlTree<dataType>::isPasswordStrong(const dataType& password) {
    return !search(password);
}

template <class dataType>
void avlTree<dataType>::buildTreeFromDictionary(const string& dictionaryFileName) {
    ifstream file(dictionaryFileName);
    if (!file.is_open()) {
        cerr << "Error: Unable to open dictionary file." << endl;
        return;
    }
    string word;
    while (getline(file, word, ',')) {
        word.erase(0, word.find_first_not_of(" \t\r\n"));
        word.erase(word.find_last_not_of(" \t\r\n") + 1);

        transform(word.begin(), word.end(), word.begin(),::tolower);
        insert(word);
    }
    file.close();
}


template <class dataType>
avlTree<dataType>::avlTree() : root(nullptr) {}

template <class dataType>
void avlTree<dataType>::printInorder() {
    inorderUtil(root);
}

template <class dataType>
void avlTree<dataType>::inorderUtil(avlNode<dataType>* root) {
    if (root != nullptr) {
        inorderUtil(root->left);
        cout << root->data << " ";
        inorderUtil(root->right);
    }
}

template <class dataType>
avlTree<dataType>::~avlTree() {
    if (root != nullptr) {
        deleteSubtree(root);
    }
}

template <class dataType>
void avlTree<dataType>::deleteSubtree(avlNode<dataType>* node) {
    if (node != nullptr) {
        deleteSubtree(node->left);
        deleteSubtree(node->right);
        delete node;
    }
}

template <class dataType>
int avlTree<dataType>::height(avlNode<dataType>* node) {
    if (node == nullptr) return 0;
    return node->height;
}

template <class dataType>
int avlTree<dataType>::balanceFactor(avlNode<dataType>* node) {
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}

template <class dataType>
avlNode<dataType>* avlTree<dataType>::rotateRight(avlNode<dataType>* y) {
    avlNode<dataType>* x = y->left;
    avlNode<dataType>* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

template <class dataType>
avlNode<dataType>* avlTree<dataType>::rotateLeft(avlNode<dataType>* x) {
    avlNode<dataType>* y = x->right;
    avlNode<dataType>* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

template <class dataType>
avlNode<dataType>* avlTree<dataType>::insertUtil(avlNode<dataType>* node, dataType key) {
    if (node == nullptr) return new avlNode<dataType>(key);
    if (key < node->data)
        node->left = insertUtil(node->left, key);
    else if (key > node->data)
        node->right = insertUtil(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

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

template <class dataType>
void avlTree<dataType>::insert(dataType key) {
    root = insertUtil(root, key);
}

template <class dataType>
avlNode<dataType>* avlTree<dataType>::minValueNode(avlNode<dataType>* node) {
    avlNode<dataType>* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

template <class dataType>
avlNode<dataType>* avlTree<dataType>::removeUtil(avlNode<dataType>* root, dataType key) {
    if (root == nullptr) return root;

    if (key < root->data)
        root->left = removeUtil(root->left, key);
    else if (key > root->data)
        root->right = removeUtil(root->right, key);
    else {
        if (root->left == nullptr || root->right == nullptr) {
            avlNode<dataType>* temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else
                *root = *temp;

            delete temp;
        }
        else {
            avlNode<dataType>* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = removeUtil(root->right, temp->data);
        }
    }
    if (root == nullptr) return root;
    root->height = 1 + max(height(root->left), height(root->right));
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
    if (balance < -1 && balanceFactor(root->right) > 0
        ) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

template <class dataType>
void avlTree<dataType>::remove(dataType key) {
    root = removeUtil(root, key);
}

template <class dataType>
bool avlTree<dataType>::search(dataType key) {
    avlNode<dataType>* current = root;
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
#endif