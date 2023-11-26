#ifndef AVL_TREE_H
#define AVL_TREE_H

template <typename T>
class avlNode {
public:
    T data;
    avlNode<T>* left;
    avlNode<T>* right;
    int height;

    avlNode(T val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

template <typename T>
class avlTree {
private:
    avlNode<T>* root;

    int height(avlNode<T>* node);
    int balanceFactor(avlNode<T>* node);
    avlNode<T>* rotateRight(avlNode<T>* y);
    avlNode<T>* rotateLeft(avlNode<T>* x);

public:
    avlTree();
    ~avlTree();

    void insert(T key);
    void remove(T key);
    bool search(T key);
    void printInorder();

private:
    avlNode<T>* insertUtil(avlNode<T>* node, T key);
    avlNode<T>* removeUtil(avlNode<T>* root, T key);
    avlNode<T>* minValueNode(avlNode<T>* node);
    void inorderUtil(avlNode<T>* root);
};

#endif // AVL_TREE_H


