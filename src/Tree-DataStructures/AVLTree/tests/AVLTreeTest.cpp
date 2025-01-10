#include "AVLTree.h"

int main() {
    AVLTree<int> avlTree;
    avlTree.insert(10);
    avlTree.insert(5);
    avlTree.insert(11);
    avlTree.insert(4);
    avlTree.insert(6);
    avlTree.insert(12);
    avlTree.insert(3);
    std::cout << "Height：" << avlTree.getHeight() << std::endl;
    std::cout << "Size：" << avlTree.size() << std::endl;
    std::cout << "InOrder：";
    avlTree.inOrder();
    std::cout << std::endl;
    TreeNode<int> *node1 = avlTree.getNode(3);
    if (node1) {
        std::cout << "Get the node which has the key：3 !" << std::endl;
        std::cout << "Height：" << node1->height << std::endl;
    }
    std::cout << "----------------------------------" << std::endl;
    avlTree.erase(10);
    std::cout << "InOrder：";
    avlTree.inOrder();
    std::cout << std::endl;
    avlTree.clear();
    std::cout << "Size：" << avlTree.size() << std::endl;
    return 0;
}
