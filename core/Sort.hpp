#pragma once

#include <vector>
#include <algorithm>
#include <functional>
#include "List.hpp"

// ============================================================
//  Sorting utilities for List<T>
//  Member A - Sorting Functions
// ============================================================

namespace Sort {

    // --------------------------------------------------------
    // 1. Default sort using operator<
    // --------------------------------------------------------
    template <typename T>
    void sort_list(List<T>& list) {
        // Extract contents
        std::vector<T> temp;
        temp.reserve(list.size());

        for (std::size_t i = 0; i < list.size(); ++i) {
            temp.push_back(list.at(i));
        }

        // Sort using default comparator
        std::sort(temp.begin(), temp.end());

        // Write back
        for (std::size_t i = 0; i < temp.size(); ++i) {
            list.at(i) = temp[i];
        }
    }


    // --------------------------------------------------------
    // 2. Custom comparator sort
    //    cmp(a, b) should return true if a < b
    // --------------------------------------------------------
    template <typename T, typename Compare>
    void sort_list(List<T>& list, Compare cmp) {
        std::vector<T> temp;
        temp.reserve(list.size());

        for (std::size_t i = 0; i < list.size(); ++i) {
            temp.push_back(list.at(i));
        }

        std::sort(temp.begin(), temp.end(), cmp);

        for (std::size_t i = 0; i < temp.size(); ++i) {
            list.at(i) = temp[i];
        }
    }


    // --------------------------------------------------------
    // 3. Stable sort
    // --------------------------------------------------------
    template <typename T>
    void stable_sort_list(List<T>& list) {
        std::vector<T> temp;
        temp.reserve(list.size());

        for (std::size_t i = 0; i < list.size(); ++i) {
            temp.push_back(list.at(i));
        }

        std::stable_sort(temp.begin(), temp.end());

        for (std::size_t i = 0; i < temp.size(); ++i) {
            list.at(i) = temp[i];
        }
    }

}  // namespace Sort
