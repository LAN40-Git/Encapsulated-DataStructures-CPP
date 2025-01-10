#ifndef DATASTRUCTURES_DEQUE_H
#define DATASTRUCTURES_DEQUE_H
#include <iostream>
#include <vector>
#include <stdexcept> // std::runtime_error

template <typename T>
class Deque {
public:
    Deque() = default;
    ~Deque() = default;

    void push_front(const T& item) {
        data.insert(data.begin(), item);
    }

    void push_back(const T& item) {
        data.push_back(item);
    }

    void pop_front() {
        if (!data.empty()) {
            data.erase(data.begin());
        } else {
            throw std::runtime_error("Deque is empty");
        }
    }

    void pop_back() {
        if (!data.empty()) {
            data.pop_back();
        } else {
            throw std::runtime_error("Deque is empty");
        }
    }

    T front() const {
        if (!data.empty()) {
            return data.front();
        } else {
            throw std::runtime_error("Deque is empty");
        }
    }

    T back() const {
        if (!data.empty()) {
            return data.back();
        } else {
            throw std::runtime_error("Deque is empty");
        }
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

#endif //DATASTRUCTURES_DEQUE_H
