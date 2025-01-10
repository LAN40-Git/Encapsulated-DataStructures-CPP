#ifndef DATASTRUCTURES_BINARYSEARCHTREE_H
#define DATASTRUCTURES_BINARYSEARCHTREE_H
#include <vector>
#include <iostream>
#include <stdexcept>

template <typename T>
struct TreeNode {
    T key;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    explicit TreeNode(const T& val) : key(val), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename T>
class BinarySearchTree {
public:
    BinarySearchTree() :m_height(0), nodeNumber(0), root(nullptr) {}
    ~BinarySearchTree() { clear(); }
    bool insert(const T& key) { return insert(key, root, 1); }
    bool erase(const T& key) { return erase(key, root); }
    bool search(const T& key) { return search(key, root); }
    void clear() {
        clear(root);
        root = nullptr;
        nodeNumber = 0;
        m_height = 0;
    }
    void preOrder() { preOrder(root); }
    void inOrder() { inOrder(root); }
    void postOrder() { postOrder(root); }
    [[nodiscard]] size_t count() const { return nodeNumber; }
    [[nodiscard]] int getHeight() const { return m_height; }
    TreeNode<T> *getNode(const T& key) { return getNode(key, root); }
    TreeNode<T>* getPredecessor(const T& key) {
        TreeNode<T> *node = getNode(key);
        if (node == nullptr) {
            return nullptr;
        }
        // 如果有左子树，前驱是左子树中的最大节点
        if (node->left != nullptr) {
            return findMax(node->left);
        }
        // 否则，前驱是其祖先节点中，最后一个左分支上的节点
        TreeNode<T>* ancestor = node->parent;
        while (ancestor != nullptr && node == ancestor->left) {
            node = ancestor;
            ancestor = ancestor->parent;
        }
        return ancestor;
    }
    TreeNode<T>* getSuccessor(const T& key) {
        TreeNode<T> *node = getNode(key);
        if (node == nullptr) {
            return nullptr;
        }
        // 如果有右子树，后继是右子树中的最小节点
        if (node->right != nullptr) {
            return findMin(node->right);
        }
        // 否则，后继是其祖先节点中，最后一个右分支上的节点
        TreeNode<T>* ancestor = node->parent;
        while (ancestor != nullptr && node == ancestor->right) {
            node = ancestor;
            ancestor = ancestor->parent;
        }
        return ancestor;
    }

private:
    int m_height;
    int nodeNumber;
    TreeNode<T> *root;

    void updateHeight(int height) {
        if (height > m_height)
            m_height = height;
    }

    bool insert(const T& key, TreeNode<T> *node, int height) {
        if (node == nullptr) {
            root = new TreeNode<T>(key);
            updateHeight(height);
            return true;
        }
        if (key < node->key) {
            if (node->left == nullptr) {
                node->left = new TreeNode<T>(key);
                node->left->parent = node;
                updateHeight(height+1);
                return true;
            } else {
                return insert(key, node->left, height+1);
            }
        } else if (key > node->key) {
            if (node->right == nullptr) {
                node->right = new TreeNode<T>(key);
                node->right->parent = node;
                updateHeight(height+1);
                return true;
            } else {
                return insert(key, node->right, height+1);
            }
        } else {
            return false;
        }
    }

    bool erase(const T& key, TreeNode<T> *node) {
        if (node == nullptr) {
            return false;
        }
        if (key < node->key) {
            return erase(key,node->left);
        } else if (key > node->key) {
            return erase(key,node->right);
        } else { // 找到需要被删除的节点时
            if (node->left == nullptr && node->right == nullptr) { // 节点无子树时
                if (node->parent == nullptr) { // 根节点
                    root = nullptr;
                } else {
                    if (node->parent->left == node) {
                        node->parent->left = nullptr;
                    } else {
                        node->parent->right = nullptr;
                    }
                }
                delete node;
            } else if (node->left == nullptr) { // 只有右子树时
                if (node->parent == nullptr) { // 根节点
                    // 将右子树的第一个节点作为根节点
                    root = node->right;
                    root->parent = nullptr;
                } else {
                    if (node->parent->left == node) {
                        node->parent->left = node->right;
                    } else {
                        node->parent->right = node->right;
                    }
                    node->right->parent = node->parent;
                }
                delete node;
            } else if (node->right == nullptr) { // 只有左子树时
                if (node->parent == nullptr) {
                    root = node->left;
                    root->parent = nullptr;
                } else {
                    if (node->parent->left == node) {
                        node->parent->left = node->left;
                    } else {
                        node->parent->right = node->right;
                    }
                    node->left->parent = node->parent;
                }
                delete node;
            } else { // 左右子树都存在时
                // 找出右子树中键值最小的节点，然后替换当前节点键值
                TreeNode<T> *minNode = findMin(node->right);
                node->key = minNode->key;
                erase(minNode->key,minNode);
            }
            nodeNumber--;
            return true;
        }
    }

    bool search(const T& key, TreeNode<T> *node) {
        if (node == nullptr) {
            return false;
        }
        if (key < node->key) {
            search(key,node->right);
        } else if (key > node->key) {
            search(key,node->left);
        } else {
            return true;
        }
        return false;
    }

    TreeNode<T> *getNode(const T& key, TreeNode<T> *node) {
        if (node == nullptr) {
            return nullptr;
        }
        if (key < node->key) {
            return getNode(key,node->left);
        } else if (key > node->key) {
            return getNode(key,node->right);
        } else {
            return node;
        }
        return nullptr;
    }

    void clear(TreeNode<T> *node) {
        if (node == nullptr)
            return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    void preOrder(TreeNode<T> *node) {
        if (node == nullptr) {
            return;
        }
        std::cout << node->key << " ";
        preOrder(node->left);
        preOrder(node->right);
    }
    void inOrder(TreeNode<T> *node) {
        if (node == nullptr) {
            return;
        }
        inOrder(node->left);
        std::cout << node->key << " ";
        inOrder(node->right);
    }
    void postOrder(TreeNode<T> *node) {
        if (node == nullptr) {
            return;
        }
        postOrder(node->left);
        postOrder(node->right);
        std::cout << node->key << " ";
    }
    TreeNode<T> *findMin(TreeNode<T> *node) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->left == nullptr) {
            return node;
        } else {
            return findMin(node->left);
        }
    }
    TreeNode<T> *findMax(TreeNode<T> *node) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->right == nullptr) {
            return node;
        } else {
            return findMax(node->right);
        }
    }
};

#endif //DATASTRUCTURES_BINARYSEARCHTREE_H