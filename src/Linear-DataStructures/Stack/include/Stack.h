#ifndef DATASTRUCTURES_STACK_H
#define DATASTRUCTURES_STACK_H

#include <vector>
#include <stdexcept>

template <typename T>
class Stack {
public:
    Stack() = default;
    ~Stack() = default;

    void push(const T &value) {
        data.push_back(value);
    }

    void pop() {
        if (empty())
            throw std::out_of_range("Stack<>::pop(): empty stack");
        data.pop_back();
    }

    T top() const {
        if (empty())
            throw std::out_of_range("Stack<>::top(): empty stack");
        return data.back();
    }

    [[nodiscard]] bool empty() const {
        return data.empty();
    }

    [[nodiscard]] size_t size() const {
        return data.size();
    }

private:
    std::vector<T> data;
};

#endif //DATASTRUCTURES_STACK_H
