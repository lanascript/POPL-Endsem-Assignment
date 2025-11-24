#pragma once
#include "IStorage.hpp"
#include <vector>
#include <stdexcept>

template<typename T>
class VectorStorage : public IStorage<T> {
    std::vector<T> data;

public:
    VectorStorage() = default;

    void push_back(const T& v) override { data.push_back(v); }
    void push_front(const T& v) override { data.insert(data.begin(), v); }

    T pop_back() override {
        if (data.empty()) throw std::runtime_error("VectorStorage::pop_back empty");
        T val = std::move(data.back());
        data.pop_back();
        return val;
    }
    T pop_front() override {
        if (data.empty()) throw std::runtime_error("VectorStorage::pop_front empty");
        T val = std::move(data.front());
        data.erase(data.begin());
        return val;
    }

    const T& front() const override {
        if (data.empty()) throw std::runtime_error("VectorStorage::front empty");
        return data.front();
    }
    const T& back() const override {
        if (data.empty()) throw std::runtime_error("VectorStorage::back empty");
        return data.back();
    }

    std::size_t size() const override { return data.size(); }
    bool empty() const override { return data.empty(); }

    T& at(std::size_t i) override {
        if (i >= data.size()) throw std::out_of_range("VectorStorage::at");
        return data[i];
    }
    const T& at(std::size_t i) const override {
        if (i >= data.size()) throw std::out_of_range("VectorStorage::at const");
        return data[i];
    }
};
