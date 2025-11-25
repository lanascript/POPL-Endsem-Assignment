#pragma once

#include <memory>
#include <iostream>
#include <functional>
#include "../storage/IStorage.hpp"
#include "../storage/VectorStorage.hpp"   // default storage backend

template <typename T>
class List {
private:
    std::unique_ptr<IStorage<T>> storage;

public:

    // --------------------------------------------------------
    // Constructors
    // --------------------------------------------------------

    // Default: use vector storage
    List() : storage(std::make_unique<VectorStorage<T>>()) {}

    // User-specified storage
    explicit List(std::unique_ptr<IStorage<T>> s)
        : storage(std::move(s)) {}

    // --------------------------------------------------------
    // Core list ops
    // --------------------------------------------------------

    void push_back(const T& v) {
        storage->push_back(v);
    }

    void push_front(const T& v) {
        storage->push_front(v);
    }

    T pop_back() {
        return storage->pop_back();
    }

    T pop_front() {
        return storage->pop_front();
    }

    const T& front() const {
        return storage->front();
    }

    const T& back() const {
        return storage->back();
    }

    std::size_t size() const {
        return storage->size();
    }

    bool empty() const {
        return storage->empty();
    }

    T& at(std::size_t i) {
        return storage->at(i);
    }

    const T& at(std::size_t i) const {
        return storage->at(i);
    }

    // --------------------------------------------------------
    // Utility
    // --------------------------------------------------------

    void print(const std::string& label = "") const {
        if (!label.empty()) std::cout << label << ": ";
        for (std::size_t i = 0; i < size(); ++i) {
            std::cout << at(i) << " ";
        }
        std::cout << "\n";
    }

    // --------------------------------------------------------
    // Clone / copy to a new List
    // --------------------------------------------------------

    List<T> clone() const {
        List<T> newList;  // uses default VectorStorage
        for (std::size_t i = 0; i < size(); ++i) {
            newList.push_back(at(i));
        }
        return newList;
    }

    // --------------------------------------------------------
    // Append another list to this one
    // --------------------------------------------------------

    void append(const List<T>& other) {
        for (std::size_t i = 0; i < other.size(); ++i) {
            push_back(other.at(i));
        }
    }

    // --------------------------------------------------------
    // Iterator-like access (optional future work)
    // --------------------------------------------------------

};
