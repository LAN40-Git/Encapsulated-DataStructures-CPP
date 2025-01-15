#ifndef DATASTRUCTURES_BTREENODE_H
#define DATASTRUCTURES_BTREENODE_H
#include <vector>
#include <cmath>

template <typename T>
class BTreeNode {
public:
    std::vector<T> _keys;
    std::vector<BTreeNode<T>*> _children;
    BTreeNode<T>* _parent;
    bool _isLeaf;
    int _size;
    BTreeNode(bool isLeaf, int m) : _isLeaf(isLeaf),_keys(m+1),_children(m+1),_parent(nullptr),_size(0) {}
    int findChild(BTreeNode<T>* child) {
        for (int i = 0; i < _size+1; i++) {
            BTreeNode<T>* node = _children[i];
            if (node == child) {
                return i;
            }
        }
        return -1;
    }
};
#endif //DATASTRUCTURES_BTREENODE_H
