//
// Created by ginmaru on 9/16/22.
//

#pragma once

#include <forward_list>
#include <stdexcept>
#include <utility>

using
        std::size_t;

template <typename T>
class Stack_l {
    std::forward_list<T> data;
    size_t count;

public:

    void push(const T& elem);
    void push(T&& elem);
    void pop();
    T& top();
    const T& top() const;
    [[nodiscard]] size_t size() const;
};

template<typename T>
void Stack_l<T>::push(const T &elem) {
    data.push_front(elem);
    ++count;
}

template<typename T>
void Stack_l<T>::push(T &&elem) {
    data.push_front(std::move(elem));
    ++count;
}

template<typename T>
void Stack_l<T>::pop() {
    if (count > 0) {
        data.pop_front();
        --count;
    }
}

template<typename T>
T &Stack_l<T>::top() noexcept(false) {
    if (count > 0) {
        return data.front();
    }
    else throw std::out_of_range("Stack is empty");
}

template<typename T>
const T &Stack_l<T>::top() const noexcept(false) {
    if (count > 0) {
        return data.front();
    }
    else throw std::out_of_range("Stack is empty");
}

template<typename T>
size_t Stack_l<T>::size() const {
    return count;
}
