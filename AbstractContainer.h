// =============================================================================
// AbstractContainer.h - The foundation header
// =============================================================================

#ifndef ABSTRACT_CONTAINER_H
#define ABSTRACT_CONTAINER_H

#include <cstddef>  
#include <memory>
#include <stdexcept>

template<typename T>
class AbstractContainer {
public:
    // Iterator interface (simplified for this project)
    class iterator {
    public:
        virtual ~iterator() = default;
        virtual iterator& operator++() = 0;
        virtual T& operator*() = 0;
        virtual bool operator!=(const iterator& other) const = 0;
        virtual std::unique_ptr<iterator> clone() const = 0;
    };

    // Virtual destructor for proper cleanup
    virtual ~AbstractContainer() = default;

    // Pure virtual methods that derived classes must implement
    virtual void add(const T& element) = 0;
    virtual T remove() = 0;
    virtual const T& peek() const = 0;
    virtual std::size_t size() const = 0;
    virtual bool isEmpty() const = 0;
    
    // Iterator methods
    virtual std::unique_ptr<iterator> begin() = 0;
    virtual std::unique_ptr<iterator> end() = 0;
};

#endif // ABSTRACT_CONTAINER_H