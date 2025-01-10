#include "BinarySearchTree.h"

int main() {
    BinarySearchTree<int> bst;
    bst.insert(1);
    bst.insert(2);
    bst.insert(3);
    bst.insert(4);
    bst.insert(5);
    bst.inOrder();
    std::cout << std::endl;
    std::cout << bst.getHeight() << std::endl;
    bst.erase(5);
    bst.inOrder();
    std::cout << std::endl;
    if (!bst.search(5)) {
        std::cout << "5 is deleted !" << std::endl;
    }
    TreeNode<int> *node1 = bst.getPredecessor(3);
    TreeNode<int> *node2 = bst.getSuccessor(3);
    if (node1) {
        std::cout << "The key of the predecessor of node1 is :" << node1->key << std::endl;
    }
    if (node2) {
        std::cout << "The key of the predecessor of node2 is :" << node2->key << std::endl;
    }
    if (!bst.insert(3)) {
        std::cout << "The key 3 is already exist !" << std::endl;
    }
    bst.insert(11);
    bst.insert(9);
    bst.insert(8);
    bst.insert(10);
    bst.insert(7);
    bst.erase(3);
    bst.preOrder();
    std::cout << std::endl;
    bst.postOrder();
    return 0;
}