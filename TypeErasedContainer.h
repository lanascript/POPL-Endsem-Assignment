// =============================================================================
// TypeErasedContainer.h - Your heterogeneous container
// =============================================================================

#ifndef TYPE_ERASED_CONTAINER_H
#define TYPE_ERASED_CONTAINER_H

#include <vector>
#include <any>
#include <stdexcept>

class TypeErasedContainer {
private:
    std::vector<std::any> storage;

public:
    void add(const std::any& element) {
        storage.push_back(element);
    }
    
    std::any remove() {
        if (isEmpty()) {
            throw std::runtime_error("TypeErasedContainer is empty - cannot remove");
        }
        std::any element = storage.front();
        storage.erase(storage.begin());
        return element;
    }
    
    const std::any& peek() const {
        if (isEmpty()) {
            throw std::runtime_error("TypeErasedContainer is empty - cannot peek");
        }
        return storage.front();
    }
    
    const std::any& at(std::size_t index) const {
        if (index >= storage.size()) {
            throw std::out_of_range("Index out of bounds");
        }
        return storage[index];
    }
    
    std::size_t size() const { return storage.size(); }
    bool isEmpty() const { return storage.empty(); }
    void clear() { storage.clear(); }
    
    template<typename T>
    T get(std::size_t index) const {
        if (index >= storage.size()) {
            throw std::out_of_range("Index out of bounds");
        }
        try {
            return std::any_cast<T>(storage[index]);
        } catch (const std::bad_any_cast& e) {
            throw std::runtime_error("Type mismatch when extracting value");
        }
    }
    
    template<typename T>
    T getFront() const {
        if (isEmpty()) {
            throw std::runtime_error("Container is empty");
        }
        try {
            return std::any_cast<T>(storage.front());
        } catch (const std::bad_any_cast& e) {
            throw std::runtime_error("Type mismatch when extracting front value");
        }
    }
};

#endif // TYPE_ERASED_CONTAINER_H