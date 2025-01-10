#include <iostream>
#include "Stack.h"
int main() {
    Stack<int> stack;

    // 在栈顶插入元素
    stack.push(1);
    stack.push(2);
    stack.push(3);

    // 遍历栈
    while (!stack.empty()) {
        std::cout << stack.top() << " ";
        stack.pop();
    }
    std::cout << std::endl;

    // 再次插入元素
    stack.push(4);
    stack.push(5);

    // 检查栈是否为空
    if (!stack.empty()) {
        std::cout << "Stack is not empty, size: " << stack.size() << std::endl;
    }

    // 获取栈顶元素
    std::cout << "Top element: " << stack.top() << std::endl;

    return 0;
}