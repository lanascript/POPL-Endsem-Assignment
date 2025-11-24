#pragma once
#include "IStorage.hpp"
#include <memory>

template<typename T>
class Queue {
    std::unique_ptr<IStorage<T>> storage;

public:
    explicit Queue(std::unique_ptr<IStorage<T>> s) : storage(std::move(s)) {}

    void enqueue(const T& v) { storage->push_back(v); }
    T dequeue()              { return storage->pop_front(); }
    const T& front() const   { return storage->front(); }

    bool isEmpty() const { return storage->empty(); }
    std::size_t size() const { return storage->size(); }
};
