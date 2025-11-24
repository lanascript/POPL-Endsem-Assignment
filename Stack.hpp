#pragma once
#include "IStorage.hpp"
#include <memory>

template<typename T>
class Stack {
    // ownership model: we accept unique_ptr to storage (preferred), but also allow raw ptr
    std::unique_ptr<IStorage<T>> storage;

public:
    explicit Stack(std::unique_ptr<IStorage<T>> s) : storage(std::move(s)) {}
    // convenience constructor to create with VectorStorage by default
    Stack() : storage(std::make_unique<typename std::remove_reference<decltype(*storage)>::type>()) {}

    void push(const T& v) { storage->push_back(v); }
    T pop()             { return storage->pop_back(); }
    const T& top() const{ return storage->back(); }

    bool isEmpty() const { return storage->empty(); }
    std::size_t size() const { return storage->size(); }
};
