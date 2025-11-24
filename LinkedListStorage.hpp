#pragma once
#include "IStorage.hpp"
#include "LinkedList.h"   // uses your existing implementation
#include <stdexcept>

template<typename T>
class LinkedListStorage : public IStorage<T> {
    LinkedList<T> list;

public:
    LinkedListStorage() = default;

    void push_back(const T& v) override { list.push_back(v); }
    void push_front(const T& v) override { list.push_front(v); }

    T pop_back() override { return list.pop_back(); }
    T pop_front() override { return list.pop_front(); }

    const T& front() const override { return list.front(); }
    const T& back()  const override { return list.back();  }

    std::size_t size() const override { return list.size(); }
    bool empty() const override { return list.empty(); }

    // LinkedList supports indexed access via node traversal
    T& at(std::size_t pos) override {
        // LinkedList doesn't expose non-const reference easily; use update pattern
        // We'll use erase+insert strategy if necessary; but better: return const_cast
        // of const at to satisfy interface; safe because underlying storage owns it.
        return const_cast<T&>(static_cast<const LinkedList<T>&>(list).at(pos));
    }
    const T& at(std::size_t pos) const override {
        // We don't have at() const in LinkedList; implement by iterating
        if (pos >= list.size()) throw std::out_of_range("LinkedListStorage::at");
        auto it = list.begin();
        for (std::size_t i=0;i<pos;++i) ++it;
        return *it;
    }
};
