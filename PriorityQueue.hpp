#pragma once
#include "HeapStorage.hpp"
#include <memory>

template<typename T, typename Compare = std::less<T>>
class PriorityQueue {
    std::unique_ptr<HeapStorage<T, Compare>> heap;

public:
    explicit PriorityQueue(std::unique_ptr<HeapStorage<T,Compare>> h)
        : heap(std::move(h)) {}

    void push(const T& v) { heap->push_back(v); } // push_back uses heap push
    T pop() { return heap->pop_back(); }         // pop_back uses heap pop (top)
    const T& top() const { return heap->front(); }

    std::size_t size() const { return heap->size(); }
    bool empty() const { return heap->empty(); }
};
