#include "Queue.h"
#include <iostream>

int main() {
    Queue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);
    queue.push(5);
    if (!queue.empty()) {
        std::cout << "Queue size: " << queue.size() << std::endl;
        std::cout << "Queue front: " << queue.front() << std::endl;
        std::cout << "Queue back: " << queue.back() << std::endl;
    }
}