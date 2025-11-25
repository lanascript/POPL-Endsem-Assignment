#pragma once

#include <string>
#include <vector>
#include "List.hpp"

// ============================================================
//  Basic Search Utilities for List<T>
//  Member A - Searching Functions
// ============================================================

namespace Search {

    // --------------------------------------------------------
    // 1. Linear search (exact match)
    //    Returns index or -1
    // --------------------------------------------------------
    template <typename T>
    int linear_search(const List<T>& list, const T& target) {
        for (std::size_t i = 0; i < list.size(); ++i) {
            if (list.at(i) == target) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    // --------------------------------------------------------
    // 2. Contains (boolean search)
    // --------------------------------------------------------
    template <typename T>
    bool contains(const List<T>& list, const T& target) {
        return linear_search(list, target) != -1;
    }

    // --------------------------------------------------------
    // 3. Find all matching indices
    // --------------------------------------------------------
    template <typename T>
    List<int> find_all(const List<T>& list, const T& target) {
        List<int> indices;
        for (std::size_t i = 0; i < list.size(); ++i) {
            if (list.at(i) == target) {
                indices.push_back(static_cast<int>(i));
            }
        }
        return indices;
    }

    // --------------------------------------------------------
    // 4. String-specific: substring search in each element
    //    e.g. keyword search in file lines or tokens
    // --------------------------------------------------------
    List<int> search_substring(const List<std::string>& list,
                               const std::string& pattern) 
    {
        List<int> matches;
        for (std::size_t i = 0; i < list.size(); ++i) {
            if (list.at(i).find(pattern) != std::string::npos) {
                matches.push_back(static_cast<int>(i));
            }
        }
        return matches;
    }

    // --------------------------------------------------------
    // 5. String-specific: case-insensitive contains
    // --------------------------------------------------------
    std::string to_lower(const std::string& s) {
        std::string out = s;
        for (char& c : out) c = std::tolower(c);
        return out;
    }

    List<int> search_substring_ci(const List<std::string>& list,
                                  const std::string& pattern) 
    {
        List<int> matches;

        std::string p = to_lower(pattern);

        for (std::size_t i = 0; i < list.size(); ++i) {
            if (to_lower(list.at(i)).find(p) != std::string::npos) {
                matches.push_back(static_cast<int>(i));
            }
        }
        return matches;
    }

} // namespace Search
