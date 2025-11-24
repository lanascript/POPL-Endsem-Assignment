#pragma once
#include <cstddef>

template<typename T>
class IStorage {
public:
    virtual ~IStorage() = default;

    // basic deque-like operations (covering stack/queue/deque needs)
    virtual void push_back(const T& v) = 0;
    virtual void push_front(const T& v) = 0;

    virtual T pop_back() = 0;
    virtual T pop_front() = 0;

    virtual const T& front() const = 0;
    virtual const T& back()  const = 0;

    virtual std::size_t size() const = 0;
    virtual bool empty() const = 0;

    // random-access helpers (for LinearContainer/algorithms)
    virtual T& at(std::size_t i) = 0;
    virtual const T& at(std::size_t i) const = 0;
};
