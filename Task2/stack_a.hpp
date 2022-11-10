//
// Created by ginmaru on 9/2/22.
//
#pragma once

#include <stdexcept>
#include <utility>

using
    std::size_t;

template <typename T>
class Stack_a {
    T* data;
    size_t capacity, count;
    bool fixed_size;
    static const size_t min_capacity;

    bool isFool();
    bool needShrink();
    void resize(size_t new_size);

public:

    explicit Stack_a(size_t capacity = 50'000, bool fixed_size = false);
    ~Stack_a();
    void push(const T& elem);
    void push(T&& elem);
    void pop();
    T& top();
    const T& top() const;
    [[nodiscard]] size_t size() const;
};

template<typename T>
const size_t Stack_a<T>::min_capacity = 10;

template <typename T>
bool Stack_a<T>::isFool() {
    return capacity == count;
}

template <typename T>
bool Stack_a<T>::needShrink() {
    return count < capacity / 3;
}

template <typename T>
void Stack_a<T>::resize(size_t new_size) {
    if (fixed_size) return;
    T* new_data = new T[new_size];
    count = std::min(count, new_size);
    for (size_t i = 0; i < count; ++i) {
        new_data[i] = std::move(data[i]);
    }
    delete[] data;
    capacity = new_size;
    data = new_data;
}

template<typename T>
Stack_a<T>::Stack_a(size_t capacity, bool fixed_size) :
        capacity(std::max(capacity, min_capacity)), count(0),
        data(new T[std::max(capacity, min_capacity)]), fixed_size(fixed_size) {
}

template<typename T>
Stack_a<T>::~Stack_a() {
    delete[] data;
}

template<typename T>
void Stack_a<T>::push(const T& elem) {
    if (isFool()) {
        if (fixed_size) {
            throw std::out_of_range("Stack has fixed size and doesn't have free space.");
        }
        else {
            resize(capacity * 2);
        }
    }
    data[count++] = elem;
}

template<typename T>
void Stack_a<T>::push(T&& elem) {
    if (isFool()) {
        if (fixed_size) {
            throw std::out_of_range("Stack has fixed size and doesn't have free space.");
        }
        else {
            resize(std::max(capacity / 2 * 3, min_capacity));
        }
    }
    data[count++] = std::move(elem);
}

template<typename T>
void Stack_a<T>::pop() {
    if (count > 0)
        --count;
    if (not fixed_size and needShrink()) {
        resize(std::max(capacity / 3 * 2, min_capacity));
    }
}

template<typename T>
T& Stack_a<T>::top() noexcept(false) {
    if (count > 0) {
        return data[count - 1];
    }
    else throw std::out_of_range("Stack is empty");
}

template<typename T>
const T& Stack_a<T>::top() const noexcept(false) {
    if (count > 0) {
        return data[count - 1];
    }
    else throw std::out_of_range("Stack is empty");
}

template<typename T>
size_t Stack_a<T>::size() const {
    return count;
}
