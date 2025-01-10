#ifndef DATASTRUCTURES_AVLTREE_H
#define DATASTRUCTURES_AVLTREE_H
#include <iostream>
#include <algorithm>

template<typename T>
struct TreeNode {
    T key;
    int height;
    TreeNode<T> *left;
    TreeNode<T> *right;
    TreeNode<T> *parent;
    explicit TreeNode(const T &k) : key(k), height(1), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename T>
class AVLTree {
public:
    AVLTree() : _size(0), root(nullptr) {}
    ~AVLTree() { clear(); }
    void insert(const T &key) { root = insert(key,root); }
    void erase(const T &key) { root = erase(key,root); }
    bool search(const T &key) { return search(key,root); }
    void clear() {
        clear(root);
        root = nullptr;
        _size = 0;
    }
    TreeNode<T> *getNode(const T& key) { return getNode(key,root); }
    void preOrder() { preOrder(root); }
    void inOrder() { inOrder(root); }
    void postOrder() { postOrder(root); }
    [[nodiscard]] size_t size() const { return _size; }
    int getHeight() { return getHeight(root); }

private:
    int _size;
    TreeNode<T> *root;
    TreeNode<T> * insert(const T &key, TreeNode<T> *node) {
        if (node == nullptr) {
            _size++;
            return(new TreeNode<T>(key));
        }

        if (key < node->key)
            node->left = insert(key, node->left);
        else if (key > node->key)
            node->right = insert(key, node->right);
        else
            return node;

        // 更新高度
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        // 获取节点的平衡因子
        int balance = getBalanceFactor(node);

        // 如果节点不平衡，可能会出现以下四种情况

        // LL
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // RR
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

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

        // 未平衡则返回原来的节点
        return node;
    }

    TreeNode<T> *erase(const T &key, TreeNode<T> *node) {
        if (node == nullptr) {
            return nullptr;
        }
        TreeNode<T> *retNode = node; // 经过删除并旋转之后得到的节点
        if (key < node->key) {
            node->left = erase(key,node->left);
        } else if (key > node->key) {
            node->right = erase(key,node->right);
        } else {
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
                retNode = nullptr;
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
                // 只有右子树时，返回右节点
                retNode = node->right;
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
                // 只有左子树时，返回左节点
                retNode = node->left;
                delete node;
            } else { // 左右子树都存在时
                // 找出右子树中键值最小的节点，然后替换当前节点键值
                TreeNode<T> *minNode = findMin(node->right);
                if (minNode == node->right && minNode->right) {
                    node->right = minNode->right;
                    minNode->right->parent = node;
                }
                node->key = minNode->key;
                retNode = node;
                delete minNode;
            }
            _size--;
        }

        if (retNode == nullptr) // 如果节点被删除，则返回空
            return nullptr;

        // 更新高度
        retNode->height = 1 + std::max(getHeight(retNode->left), getHeight(retNode->right));

        // 获取平衡因子
        int balance = getBalanceFactor(retNode);

        // 如果节点不平衡，可能会出现以下四种情况

        // LL
        if (balance > 1 && key < retNode->left->key)
            return rightRotate(retNode);

        // RR
        if (balance < -1 && key > retNode->right->key)
            return leftRotate(retNode);

        // LR
        if (balance > 1 && key > retNode->left->key) {
            retNode->left = leftRotate(retNode->left);
            return rightRotate(retNode);
        }

        // RL
        if (balance < -1 && key < retNode->right->key) {
            retNode->right = rightRotate(retNode->right);
            return leftRotate(retNode);
        }

        // 返回原来的或者经过删除或旋转的节点
        return retNode;
    }

    bool search(const T &key, TreeNode<T> *node) {
        if (node == nullptr)
            return false;
        if (key < node->key) {
            return search(key,node->left);
        } else if (key > node->key) {
            return search(key,node->right);
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

    // 获取节点高度
    int getHeight(TreeNode<T> *node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    // 更新高度
    void updateHeight(TreeNode<T> *node) {
        if (node == nullptr)
            return;
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    // 获取平衡因子
    int getBalanceFactor(TreeNode<T> *node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
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

    /* @https://www.cnblogs.com/hello-shf/p/11352071.html*/
    TreeNode<T>* rightRotate(TreeNode<T>* y) {
        if (y == nullptr)
            return nullptr;
        ///////////////////////////////////////////////////
        // LL T1<Z<T2< X <T3<Y<T4                        //
        //        y                              x       //
        //       / \                           /   \     //
        //      x   T4     向右旋转 (y)        z     y     //
        //     / \       - - - - - - - ->    / \   / \   //
        //    z   T3                        T1 T2 T3 T4  //
        //   / \                                         //
        // T1   T2                                       //
        ///////////////////////////////////////////////////
        TreeNode<T>* x = y->left;
        TreeNode<T>* T3 = x->right;

        // 旋转
        x->right = y;
        y->left = T3;

        // 更新父节点
        x->parent = y->parent;
        if (T3) {
            T3->parent = x;
        }
        y->parent = x;

        // 更新高度(只有x和y的高度变化了，由下而上更新)
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        // 返回旋转后的节点
        return x;
    }

    TreeNode<T>* leftRotate(TreeNode<T>* x) {
        if (x == nullptr)
            return nullptr;
        ////////////////////////////////////////////////
        // RR T1<Y<T2< X <T3<Z<T4                     //
        //    x                             y         //
        //  /  \                          /   \       //
        // T1   y      向左旋转 (x)       x     z       //
        //     / \   - - - - - - - ->   / \   / \     //
        //    T2  z                    T1 T2 T3 T4    //
        //       / \                                  //
        //      T3 T4                                 //
        ////////////////////////////////////////////////
        TreeNode<T>* y = x->right;
        TreeNode<T>* T2 = y->left;

        // 旋转
        y->left = x; // x to y->left
        x->right = T2; // y->left to x->right

        // 更新父节点
        y->parent = x->parent;
        if (T2) {
            T2->parent = x;
        }
        x->parent = y;

        // 更新高度(只有x和y的高度变化了，由下而上更新)
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        // 返回旋转后的节点
        return y;
    }
};

#endif //DATASTRUCTURES_AVLTREE_H
