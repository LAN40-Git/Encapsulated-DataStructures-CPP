#ifndef DATASTRUCTURES_BTREE_H
#define DATASTRUCTURES_BTREE_H
#include "BTreeNode.h"
#include <iostream>

template <typename T>
class BTree {
public:
    explicit BTree(double m) : _m(m),root(new BTreeNode<T>(true,m)) {}
    void insert(const T& key) { insert(key,root); }
    void erase(const T& key) { erase(key,root); }
    bool search(const T& key) { return search(key,root); }
    void preOrder() { preOrder(root); }
    void inOrder() { inOrder(root); }
    void postOrder() { postOrder(root); }
    BTreeNode<T>* getRoot() { return root; }
    BTreeNode<T>* getNode(const T& key) { return getNode(key,root); }

private:
    BTreeNode<T>* root;
    double _m;
    void insert(const T& key, BTreeNode<T>* node) {
        /**思路
         * 1. 检查_keys是否为空，为空则直接push_back(key)，不为空则进行比较
         * 2. 找到_keys中比自己大的数时，如果当前结点(整体)是叶子结点，则进行插入，否则走分支或者创建分支
         * 3. 重复直到找到叶子结点(整体)执行插入
         * 4. 检查_keys.size()是否大于阶数-1
         * 5. 如果大于，则进行分裂；否则结束插入操作
         */
        if (node->_size == 0) {
            // 为空必为叶子结点(整体)
            node->_keys[0] = key;
            node->_size++;
        } else {
            for (int i = 0; i < node->_size; i++) {
                if (key < node->_keys[i]) { // 找到第一个大于自己的元素
                    if (node->_isLeaf) { // 是叶子结点(整体)则插入
                        node->_keys.insert(node->_keys.begin()+i,key);
                        node->_size++;
                        split(node);
                        return;
                    } else {
                        if (node->_children[i] != nullptr) {
                            insert(key, node->_children[i]);
                            return;
                        }
                    }
                } else if (key > node->_keys[i]) {
                    // 如果大于且为最后一个结点
                    if (i == node->_size-1) {
                        if (node->_isLeaf) {
                            node->_keys.insert(node->_keys.begin()+i+1,key);
                            node->_size++;
                            split(node);
                            return;
                        } else {
                            if (node->_children[i+1] != nullptr) {
                                insert(key, node->_children[i+1]);
                                return;
                            }
                        }
                    }
                } else {
                    return;
                }
            }
        }
    }

    void erase(const T& key, BTreeNode<T>* node) {
        if (node == nullptr)
            return;
        for (int i = 0; i < node->_size; i++) {
            if (key < node->_keys[i]) {
                // 找到node键值中第一个比key大的，则走对应左分支
                erase(key,node->_children[i]);
                return;
            } else if (key > node->_keys[i]) {
                // 找到node键值中比key大的，如果是最后一个键值，就找最后一个孩子
                if (i == node->_size-1) {
                    erase(key,node->_children[node->_size]);
                    return;
                }
            } else {// 找到键值
                /**删除思路
                 * 对于非叶子结点元素，找到前驱或后继元素替换
                 * 对前驱或后继元素所在的结点进行维护
                 * 对于叶子结点元素
                 * 如果删除后结点的元素数量小于ceil(_m/2)-1，则需要与左兄弟或者右兄弟合并
                 */
                 // 非叶子结点元素
                 if (!node->_isLeaf) {
                     // 找到后继元素所在的结点
                     BTreeNode<T>* minNode = findMin(node->_children[i+1]);
                     if (minNode) {
                         T minElement = minNode->_keys[0]; // 第一个元素最小
                         minNode->_keys.erase(minNode->_keys.begin()); // 将右边的元素左移
                         minNode->_size--; // 元素数量-1
                         node->_keys[i] = minElement; // 替换元素
                         // 此时只需要维护后继元素所在的结点
                         if (minNode->_size < ceil(_m/2)-1) { // 如果元素低于下限
                             /**合并
                              * 传入后继元素所在结点在父亲的孩子容器中的下标和对应的后继结点
                              *
                              */
                              // 找到后继元素所在结点在父亲的孩子容器的下标
                              int index = -1;
                              index = minNode->_parent->findChild(minNode);
                              if (index != -1) {
                                  merge(index,minNode);
                              }
                         }
                     }
                 } else {
                     node->_keys.erase(node->_keys.begin()+i);
                     node->_size--;
                     if (node->_size < ceil(_m/2)-1) {
                         int index = -1;
                         index = node->_parent->findChild(node);
                         if (index != -1) {
                             merge(index,node);
                         }
                     }
                 }
                 return;
            }
        }
    }

    void merge(int index, BTreeNode<T>* node) {
        /**
         * 不合并根结点和空结点
         * 对于需要合并的结点
         * 根据下标index确认兄弟结点
         */
         // 不合并根结点和空结点
         if (node == nullptr || node == root)
             return;
         // 检查是否需要合并
         if (node->_size < ceil(_m/2)-1) {
             // 根据下标确认兄弟结点
             if (index == 0) { // 如果是第一个孩子
                 // 取父结点_keys中对应index的元素添加到自己的元素最右边
                 T parElement = node->_parent->_keys[index];
                 node->_parent->_keys.erase(node->_parent->_keys.begin()+index);
                 node->_parent->_size--;
                 node->_keys[node->_size] = parElement;
                 node->_size++;
                 // 与右兄弟合并
                 BTreeNode<T>* right = node->_parent->_children[index+1];
                 for (int i = 0; i < right->_size; i++) {
                     node->_keys[node->_size] = right->_keys[i];
                     node->_size++;
                 }
                 // 移除父亲孩子集合中的右孩子
                 node->_parent->_children.erase(node->_parent->_children.begin()+index+1);
                 // 删除右兄弟
                 delete right;
                 // 对合并后的结点，如果元素数量超出上限，则需要分裂
                 BTreeNode<T>* parent = node->_parent; // 防止分裂导致node无法被访问
                 if (node->_size >= _m) {
                     split(node);
                 }
                 // 如果造成父结点的元素低于下限
                 if (parent->_size < ceil(_m/2)-1) {
                     if (parent->_parent == nullptr) { // 如果是根节点
                         if (root->_size == 0) { // 如果根元素容器为空，说明合并后的结点是新结点
                             root = node;
                         }
                         // 否则不需要执行操作
                     } else { // 如果不是根结点
                         int index2 = -1;
                         index2 = parent->_parent->findChild(parent);
                         if (index2 != -1) {
                             merge(index2,parent);
                             return;
                         }
                     }
                 }
             } else { // 如果不是第一个孩子
                 // 取父结点_keys中对应index-1的元素添加到自己的元素最左边
                 T parElement = node->_parent->_keys[index-1];
                 node->_parent->_keys.erase(node->_parent->_keys.begin()+index-1);
                 node->_parent->_size--;
                 node->_keys.insert(node->_keys.begin(),parElement);
                 node->_size++;
                 // 与左兄弟合并
                 BTreeNode<T>* left = node->_parent->_children[index-1];
                 for (int i = left->_size-1; i > 0; i--) {
                     node->_keys.insert(node->_keys.begin(),left->_keys[i]);
                     node->_size++;
                 }
                 // 移除父亲孩子集合中的左孩子
                 node->_parent->_children.erase(node->_parent->_children.begin()+index-1);
                 // 删除左兄弟
                 delete left;
                 BTreeNode<T>* parent = node->_parent; // 防止分裂导致node无法被访问
                 // 对合并后的结点，如果元素数量超出上限，则需要分裂
                 if (node->_size >= _m) {
                     split(node);
                 }
                 // 如果造成父结点的元素低于下限
                 if (parent->_size < ceil(_m/2)-1) {
                     if (parent->_parent == nullptr) { // 如果是根节点
                         if (root->_size == 0) { // 如果根元素容器为空，说明合并后的结点是新结点
                             root = node;
                         }
                         // 否则不需要执行操作
                     } else { // 如果不是根结点
                         int index2 = -1;
                         index2 = parent->_parent->findChild(parent);
                         if (index2 != -1) {
                             merge(index2,parent);
                             return;
                         }
                     }
                 }
             }
         }
    }

    bool search(const T& key, BTreeNode<T>* node) {
        if (node == nullptr)
            return false;
        for (int i = 0; i < node->_size; i++) {
            if (key < node->_keys[i]) {
                return search(key,node->_children[i]);
            } else if (key > node->_keys[i]) {
                if (i == node->_size-1) {
                    return search(key,node->_children[i+1]);
                }
            } else {
                return true;
            }
        }
        return false;
    }

    void split(BTreeNode<T>* node) {
        if (node == nullptr)
            return;
        if (node->_size >= _m) {
            int mid = ceil(_m/2)-1;
            T temp = node->_keys[mid]; // 需要上提的元素
            // 分裂左右两个结点(可为空)
            bool isLeaf = node->_isLeaf; // 判断分裂后的结点是否为叶子结点
            BTreeNode<T>* left = new BTreeNode<T>(isLeaf,_m);
            BTreeNode<T>* right = new BTreeNode<T>(isLeaf,_m);
            // 给分裂后的结点插入键值
            // 左结点
            for (int i = 0; i < mid; i++) {
                left->_keys[i] = node->_keys[i];
                left->_children[i] = node->_children[i];
                // 如果拥有孩子结点，需要设置孩子的父亲结点
                if (left->_children[i])
                    left->_children[i]->_parent = left;
                left->_size++;
            }
            left->_children[mid] = node->_children[mid];
            if (left->_children[mid])
                left->_children[mid]->_parent = left;
            // 右结点
            int j = 0;
            for (int i = mid+1; i < _m; i++) {
                right->_keys[j] = node->_keys[i];
                right->_children[j] = node->_children[i];
                if(right->_children[j])
                    right->_children[j]->_parent = right;
                right->_size++;
                j++;
            }
            right->_children[j] = node->_children[_m];
            if (right->_children[j])
                right->_children[j]->_parent = right;
            if (node->_parent == nullptr) { // 如果是根节点，则创建一个结点作为新的根节点，并插入上提元素
                root = new BTreeNode<T>(false,_m); // 创建一个新结点作为根节点
                root->_keys[0] = temp; // 插入上提元素
                root->_size++;
                // node->_parent = root; 该结点被分裂后变为left和right以及上提的结点，故需要删除，不需要设置父亲
                // 设置根节点的第1，2个孩子
                root->_children[0] = left;
                root->_children[1] = right;
                left->_parent = root;
                right->_parent = root;
                // 删除被分裂的结点
                delete node;
                return;
            } else {
                int index = -1;
                if (node->_parent != nullptr) {
                    index = node->_parent->findChild(node);
                }
                if (index != -1) {
                    // 在对应位置插入需要上提的元素
                    auto it = node->_parent->_keys.begin();
                    auto it2 = node->_parent->_children.begin();
                    node->_parent->_keys.insert(it+index,temp);
                    node->_parent->_size++;
                    node->_parent->_children[index] = right;
                    node->_parent->_children.insert(it2+index,left);
                    left->_parent = node->_parent;
                    right->_parent = node->_parent;
                    split(left->_parent); // 检查上提后父节点是否溢出，并进行相应的操作
                    delete node;
                    return;
                }
            }
        }
    }



    BTreeNode<T>* getNode(const T& key, BTreeNode<T>* node) {
        if (node == nullptr)
            return nullptr;
        for (int i = 0; i < node->_size; i++) {
            if (key < node->_keys[i]) {
                return getNode(key,node->_children[i]);
            } else if (key > node->_keys[i]) {
                if (i == node->_size-1) {
                    return getNode(key,node->_children[i+1]);
                }
            } else {
                return node;
            }
        }
        return nullptr;
    }

    BTreeNode<T>* findMin(BTreeNode<T>* node) {
        if (node == nullptr)
            return nullptr;
        if (node->_children[0] == nullptr) {
            return node;
        } else {
            return findMin(node->_children[0]);
        }
    }

    BTreeNode<T>* findMax(BTreeNode<T>* node) {
        if (node == nullptr)
            return nullptr;
        if (node->_children[node->_size] == nullptr) {
            return node;
        } else {
            return findMin(node->_children[node->_size]);
        }
    }

    void preOrder(BTreeNode<T>* node) {
        if (node == nullptr)
            return;
        for (int i = 0; i < node->_size; i++) {
            std::cout << node->_keys[i] << " ";
            preOrder(node->_children[i]);
        }
        preOrder(node->_children[node->_size]);
    }

    void inOrder(BTreeNode<T>* node) {
        if (node == nullptr)
            return;
        for (int i = 0; i < node->_size; i++) {
            inOrder(node->_children[i]);
            std::cout << node->_keys[i] << " ";
        }
        inOrder(node->_children[node->_size]);
    }

    void postOrder(BTreeNode<T>* node) {
        if (node == nullptr)
            return;
        for (int i = 0; i <= node->_size; i++) {
            preOrder(node->_children[i]);
        }
        for (int i = 0; i < node->_size; i++) {
            std::cout << node->_keys[i] << " ";
        }
    }

};

#endif //DATASTRUCTURES_BTREE_H
