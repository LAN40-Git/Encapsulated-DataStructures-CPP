#include "Deque.h"

int main() {
    Deque<int> deque;
    deque.push_front(1);
    deque.push_front(2);
    deque.push_front(3);
    deque.push_front(4);
    deque.push_front(5);
    if (!deque.empty()) {
        std::cout << "Deque size: " << deque.size() << std::endl;
        std::cout << "Deque front: " << deque.front() << std::endl;
        std::cout << "Deque back: " << deque.back() << std::endl;
    }
    return 0;
}
