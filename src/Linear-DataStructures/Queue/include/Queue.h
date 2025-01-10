#ifndef DATASTRUCTURES_QUEUE_H
#define DATASTRUCTURES_QUEUE_H
#include <vector>
#include <stdexcept>

template <typename T>
class Queue {
public:
    Queue() = default;
    ~Queue() = default;
    void push(const T &value);
    void pop();
    T front() const;
    T back() const;
    [[nodiscard]] bool empty() const;
    [[nodiscard]] size_t size() const;
private:
    std::vector<T> data;
};

template<typename T>
size_t Queue<T>::size() const {
    return data.size();
}

template<typename T>
bool Queue<T>::empty() const {
    return data.empty();
}

template<typename T>
T Queue<T>::back() const {
    if (empty())
        throw std::out_of_range("Queue<>::back(): empty queue");
    return data.back();
}

template<typename T>
T Queue<T>::front() const {
    if (empty())
        throw std::out_of_range("Queue<>::front(): empty queue");
    return data.front();
}

template<typename T>
void Queue<T>::pop() {
    if (empty())
        throw std::out_of_range("Queue<>::pop(): empty queue");
    data.erase(data.begin());

}

template<typename T>
void Queue<T>::push(const T &value) {
    data.push_back(value);
}
#endif //DATASTRUCTURES_QUEUE_H
