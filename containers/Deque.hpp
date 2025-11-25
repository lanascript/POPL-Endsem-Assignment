#pragma once
#include "../storage/IStorage.hpp"
#include <memory>

template<typename T>
class Deque {
    std::unique_ptr<IStorage<T>> storage;

public:
    explicit Deque(std::unique_ptr<IStorage<T>> s) : storage(std::move(s)) {}

    void push_front(const T& v) { storage->push_front(v); }
    void push_back (const T& v) { storage->push_back(v); }
    T pop_front() { return storage->pop_front(); }
    T pop_back()  { return storage->pop_back(); }

    const T& front() const { return storage->front(); }
    const T& back()  const { return storage->back(); }

    std::size_t size() const { return storage->size(); }
    bool empty() const { return storage->empty(); }
};
