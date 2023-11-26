#pragma once
#ifndef AVL_TREE_H
#define AVL_TREE_H

template <typename Key, typename Value>
class avlTree {
private:
    struct Node {
        Key key;
        Value value;
        Node* left;
        Node* right;
        int height;

        Node(const Key& k, const Value& v)
            : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    // Helper functions
    int height(Node* node);
    int balanceFactor(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* balance(Node* node);
    Node* insert(Node* node, const Key& key, const Value& value);
    Node* findMin(Node* node);
    Node* removeMin(Node* node);
    Node* remove(Node* node, const Key& key);
    void destroy(Node* node);
    void inOrderTraversal(Node* node, void (*visit)(const Key&, const Value&));

public:
    // Constructor and Destructor
    avlTree();
    ~avlTree();

    // Public functions
    void insert(const Key& key, const Value& value);
    void remove(const Key& key);
    bool search(const Key& key, Value& value);
    void printInOrder();
};
#endif // AVL_TREE_H
