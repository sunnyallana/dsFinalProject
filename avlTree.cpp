#include "avlTree.h"

template <typename Key, typename Value>
avlTree<Key, Value>::avlTree() : root(nullptr) {}

// Destructor
template <typename Key, typename Value>
avlTree<Key, Value>::~avlTree() {
    destroy(root);
}

template <typename Key, typename Value>
int avlTree<Key, Value>::height(Node* node) {
    return (node == nullptr) ? 0 : node->height;
}

template <typename Key, typename Value>
int avlTree<Key, Value>::balanceFactor(Node* node) {
    return (node == nullptr) ? 0 : height(node->left) - height(node->right);
}

template <typename Key, typename Value>
typename avlTree<Key, Value>::Node* avlTree<Key, Value>::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

template <typename Key, typename Value>
typename avlTree<Key, Value>::Node* avlTree<Key, Value>::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

template <typename Key, typename Value>
typename avlTree<Key, Value>::Node* avlTree<Key, Value>::balance(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }

    node->height = std::max(height(node->left), height(node->right)) + 1;

    int balanceFactor = balanceFactor(node);

    // Left-Left Case
    if (balanceFactor > 1 && balanceFactor(node->left) >= 0) {
        return rotateRight(node);
    }

    // Left-Right Case
    if (balanceFactor > 1 && balanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right-Right Case
    if (balanceFactor < -1 && balanceFactor(node->right) <= 0) {
        return rotateLeft(node);
    }

    // Right-Left Case
    if (balanceFactor < -1 && balanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

template <typename Key, typename Value>
typename avlTree<Key, Value>::Node* avlTree<Key, Value>::findMin(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

template <typename Key, typename Value>
typename avlTree<Key, Value>::Node* avlTree<Key, Value>::removeMin(Node* node) {
    if (node->left == nullptr) {
        return node->right;
    }

    node->left = removeMin(node->left);
    return balance(node);
}

template <typename Key, typename Value>
typename avlTree<Key, Value>::Node* avlTree<Key, Value>::insert(Node* node, const Key& key, const Value& value) {
    if (node == nullptr) {
        return new Node(key, value);
    }

    if (key < node->key) {
        node->left = insert(node->left, key, value);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key, value);
    }
    else {
        // Duplicate key, update the value if needed
        node->value = value;
        return node;
    }

    return balance(node);
}

template <typename Key, typename Value>
typename avlTree<Key, Value>::Node* avlTree<Key, Value>::remove(Node* node, const Key& key) {
    if (node == nullptr) {
        return nullptr;
    }

    if (key < node->key) {
        node->left = remove(node->left, key);
    }
    else if (key > node->key) {
        node->right = remove(node->right, key);
    }
    else {
        // Node with the key found

        // Node with only one child or no child
        if (node->left == nullptr || node->right == nullptr) {
            Node* temp = (node->left != nullptr) ? node->left : node->right;

            // No child case
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            }
            else {
                // One child case
                *node = *temp;
            }

            delete temp;
        }
        else {
            // Node with two children
            Node* temp = findMin(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = remove(node->right, temp->key);
        }
    }

    if (node == nullptr) {
        return nullptr;
    }

    return balance(node);
}

template <typename Key, typename Value>
void avlTree<Key, Value>::destroy(Node* node) {
    if (node == nullptr) {
        return;
    }
    destroy(node->left);
    destroy(node->right);

    delete node;
}

template <typename Key, typename Value>
void avlTree<Key, Value>::inOrderTraversal(Node* node, void (*visit)(const Key&, const Value&)) {
    if (node == nullptr) {
        return;
    }

    inOrderTraversal(node->left, visit);
    visit(node->key, node->value);
    inOrderTraversal(node->right, visit);
}

template <typename Key, typename Value>
bool avlTree<Key, Value>::search(const Key& key, Value& value) {
    Node* current = root;
    while (current != nullptr) {
        if (key == current->key) {
            value = current->value;
            return true; // Key found
        }
        else if (key < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return false; // Key not found
}

template <typename Key, typename Value>
void avlTree<Key, Value>::insert(const Key& key, const Value& value) {
    root = insert(root, key, value);
}

template <typename Key, typename Value>
void avlTree<Key, Value>::remove(const Key& key) {
    root = remove(root, key);
}

template <typename Key, typename Value>
bool avlTree<Key, Value>::search(const Key& key, Value& value) {
    return search(root, key, value);
}

template <typename Key, typename Value>
void avlTree<Key, Value>::printInOrder() {
    inOrderTraversal(root, [](const Key& k, const Value& v) {
        std::cout << "Key: " << k << ", Value: " << v << std::endl;
        });
}