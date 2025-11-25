#pragma once

#include <functional>
#include <stdexcept>
#include "List.hpp"

// ================================================================
// Aggregation tools for List<T>
// Member A - Inversions, Average, Map, Filter, Reduce
// ================================================================

namespace Aggregation {

    // ------------------------------------------------------------
    // 1. Count inversions — only for numeric-like lists
    // ------------------------------------------------------------
    long long count_inversions(const List<int>& list) {
        long long inv_count = 0;

        for (std::size_t i = 0; i < list.size(); ++i) {
            for (std::size_t j = i + 1; j < list.size(); ++j) {
                if (list.at(i) > list.at(j)) {
                    inv_count++;
                }
            }
        }

        return inv_count;
    }

    // ------------------------------------------------------------
    // 2. Compute average — numeric list
    // ------------------------------------------------------------
    double average(const List<int>& list) {
        if (list.empty())
            throw std::runtime_error("Cannot compute average of empty list");

        long long sum = 0;
        for (std::size_t i = 0; i < list.size(); ++i) {
            sum += list.at(i);
        }

        return static_cast<double>(sum) / list.size();
    }

    // ------------------------------------------------------------
    // 3. Map — apply function to each element and create new List<U>
    // ------------------------------------------------------------
    template <typename T, typename U, typename Func>
    List<U> map_list(const List<T>& list, Func f) {
        List<U> result;

        for (std::size_t i = 0; i < list.size(); ++i) {
            result.push_back(f(list.at(i)));
        }

        return result;
    }

    // ------------------------------------------------------------
    // 4. Filter — return all elements satisfying predicate
    // ------------------------------------------------------------
    template <typename T, typename Pred>
    List<T> filter_list(const List<T>& list, Pred p) {
        List<T> result;

        for (std::size_t i = 0; i < list.size(); ++i) {
            if (p(list.at(i))) {
                result.push_back(list.at(i));
            }
        }

        return result;
    }

    // ------------------------------------------------------------
    // 5. Reduce — fold elements with a function
    // ------------------------------------------------------------
    template <typename T, typename Acc, typename Func>
    Acc reduce_list(const List<T>& list, Acc init, Func f) {
        Acc acc = init;

        for (std::size_t i = 0; i < list.size(); ++i) {
            acc = f(acc, list.at(i));
        }

        return acc;
    }

} // namespace Aggregation
