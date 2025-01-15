#include "BTree.h"
#include <iostream>

int main() {
    // 创建一个阶数为3的B树
    BTree<int> btree(3);

    // 插入元素
    btree.insert(10);
    btree.insert(20);
    btree.insert(30);
    btree.insert(40);
    btree.insert(50);
    btree.insert(60);
    btree.insert(70);
    btree.insert(80);
    btree.insert(90);
    btree.insert(100);

    // 前序遍历B树
    std::cout << "前序遍历B树：" << std::endl;
    btree.preOrder();
    std::cout << std::endl;

    // 中序遍历B树
    std::cout << "中序遍历B树：" << std::endl;
    btree.inOrder();
    std::cout << std::endl;

    // 后序遍历B树
    std::cout << "后序遍历B树：" << std::endl;
    btree.postOrder();
    std::cout << std::endl;

    // 搜索元素
    int searchKey = 50;
    if (btree.search(searchKey)) {
        std::cout << "找到元素：" << searchKey << std::endl;
    } else {
        std::cout << "未找到元素：" << searchKey << std::endl;
    }

    // 删除元素
    int eraseKey = 40;
    btree.erase(eraseKey);
    if (!btree.search(eraseKey)) {
        std::cout << "成功删除元素：" << eraseKey << std::endl;
    } else {
        std::cout << "删除元素失败：" << eraseKey << std::endl;
    }

    return 0;
}