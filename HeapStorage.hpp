#pragma once
#include "IStorage.hpp"
#include <vector>
#include <algorithm>
#include <functional>
#include <stdexcept>

template<typename T, typename Compare = std::less<T>>
class HeapStorage : public IStorage<T> {
    std::vector<T> data;
    Compare comp;

public:
    explicit HeapStorage(Compare c = Compare{}) : comp(c) {}

    // For heap, push_back/pop_back used; push_front/pop_front not meaningful
    void push_back(const T& v) override {
        data.push_back(v);
        std::push_heap(data.begin(), data.end(), comp);
    }
    void push_front(const T& /*v*/) override {
        // Not meaningful: push_front => treat as push_back
        throw std::runtime_error("HeapStorage::push_front not supported");
    }

    T pop_back() override {
        if (data.empty()) throw std::runtime_error("HeapStorage::pop_back empty");
        std::pop_heap(data.begin(), data.end(), comp);
        T v = std::move(data.back());
        data.pop_back();
        return v;
    }
    T pop_front() override {
        // Not meaningful; treat pop_front as pop_back for compatibility
        return pop_back();
    }

    const T& front() const override {
        if (data.empty()) throw std::runtime_error("HeapStorage::front empty");
        return data.front();
    }
    const T& back() const override {
        if (data.empty()) throw std::runtime_error("HeapStorage::back empty");
        return data.front(); // top element
    }

    std::size_t size() const override { return data.size(); }
    bool empty() const override { return data.empty(); }

    T& at(std::size_t i) override {
        if (i >= data.size()) throw std::out_of_range("HeapStorage::at");
        return data[i];
    }
    const T& at(std::size_t i) const override {
        if (i >= data.size()) throw std::out_of_range("HeapStorage::at const");
        return data[i];
    }
};
