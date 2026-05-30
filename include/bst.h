// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <algorithm>
#include <vector>

template<typename T>
class BST {
 private:
    struct Node {
        T key;
        int freq;
        Node* left;
        Node* right;
        explicit Node(const T& value) {
            key = value;
            freq = 1;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    Node* insert(Node* node, const T& value) {
        if (!node)
            return new Node(value);
        if (value < node->key)
            node->left = insert(node->left, value);
        else if (value > node->key)
            node->right = insert(node->right, value);
        else
            node->freq++;
        return node;
    }

    int search(Node* node, const T& value) const {
        if (!node) return 0;
        if (value == node->key)
            return node->freq;
        if (value < node->key)
            return search(node->left, value);
        return search(node->right, value);
    }

    int depth(Node* node) const {
        if (!node) return -1;
        int l = depth(node->left);
        int r = depth(node->right);
        return 1 + std::max(l, r);
    }

    void collect(Node* node,
        std::vector<std::pair<T, int>>& data) const {
        if (!node) return;
        collect(node->left, data);
        data.push_back({ node->key, node->freq });
        collect(node->right, data);
    }

 public:
    BST() {
        root = nullptr;
    }

    ~BST() {
        clear(root);
    }

    void insert(const T& value) {
        root = insert(root, value);
    }

    int search(const T& value) const {
        return search(root, value);
    }

    int depth() const {
        return depth(root);
    }

    std::vector<std::pair<T, int>> getData() const {
        std::vector<std::pair<T, int>> data;
        collect(root, data);
        return data;
    }
};
#endif  // INCLUDE_BST_H_
