// LinearContainer.h — Abstract intermediate class with indexed + rearrange API
#pragma once
#include "AbstractContainer.h"
#include <cstddef>

template<typename T>
class LinearContainer : public AbstractContainer<T> {
public:
    using size_type = std::size_t;

    virtual void insert_at(size_type pos, const T& value) = 0;
    virtual T    erase_at (size_type pos)                 = 0;
    virtual void update_at(size_type pos, const T& value) = 0;
    virtual void rearrange()                              = 0;

    ~LinearContainer() override = default;
};
