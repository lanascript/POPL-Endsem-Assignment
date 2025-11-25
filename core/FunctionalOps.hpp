#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include "Aggregation.hpp"
#include "List.hpp"
#include "Search.hpp"
#include "Sort.hpp"

namespace FunctionalOps {

    // ------------------------------------------------------------
    // Helper data model for keyword frequency outputs
    // ------------------------------------------------------------
    struct KeywordFrequency {
        std::string keyword;
        std::size_t count{};
    };

    inline std::ostream& operator<<(std::ostream& os,
                                    const KeywordFrequency& freq) {
        os << freq.keyword << " -> " << freq.count;
        return os;
    }

    // ------------------------------------------------------------
    // Generic map/filter/fold helpers that wrap Aggregation module
    // ------------------------------------------------------------
    template <typename T, typename Func>
    auto map(const List<T>& list, Func func)
        -> List<std::decay_t<decltype(func(std::declval<T>()))>> {
        using U = std::decay_t<decltype(func(std::declval<T>()))>;
        return Aggregation::map_list<T, U>(list, func);
    }

    template <typename T, typename Pred>
    List<T> filter(const List<T>& list, Pred pred) {
        return Aggregation::filter_list(list, pred);
    }

    template <typename T, typename Acc, typename Func>
    Acc fold_left(const List<T>& list, Acc init, Func func) {
        return Aggregation::reduce_list(list, init, func);
    }

    template <typename T>
    List<T> take(const List<T>& list, std::size_t n) {
        List<T> out;
        const auto limit = std::min(n, list.size());
        for (std::size_t i = 0; i < limit; ++i) {
            out.push_back(list.at(i));
        }
        return out;
    }

    template <typename T>
    List<T> drop(const List<T>& list, std::size_t n) {
        List<T> out;
        if (n >= list.size()) return out;
        for (std::size_t i = n; i < list.size(); ++i) {
            out.push_back(list.at(i));
        }
        return out;
    }

    template <typename T>
    List<T> distinct(const List<T>& list) {
        std::unordered_set<T> seen;
        List<T> out;
        for (std::size_t i = 0; i < list.size(); ++i) {
            if (seen.insert(list.at(i)).second) {
                out.push_back(list.at(i));
            }
        }
        return out;
    }

    template <typename T, typename Compare = std::less<T>>
    List<T> sorted(const List<T>& list, Compare cmp = Compare{}) {
        auto copy = list.clone();
        Sort::sort_list(copy, cmp);
        return copy;
    }

    // ------------------------------------------------------------
    // Pipeline abstraction
    // ------------------------------------------------------------
    template <typename T>
    class Pipeline {
    public:
        explicit Pipeline(List<T>&& initial) : data(std::move(initial)) {}

        template <typename Func>
        auto map(Func func) const
            -> Pipeline<std::decay_t<decltype(func(std::declval<T>()))>> {
            using U = std::decay_t<decltype(func(std::declval<T>()))>;
            auto mapped = FunctionalOps::map(data, func);
            return Pipeline<U>(std::move(mapped));
        }

        template <typename Pred>
        Pipeline<T> filter(Pred pred) const {
            auto filtered = FunctionalOps::filter(data, pred);
            return Pipeline<T>(std::move(filtered));
        }

        template <typename Compare = std::less<T>>
        Pipeline<T> sort(Compare cmp = Compare{}) const {
            auto copy = data.clone();
            Sort::sort_list(copy, cmp);
            return Pipeline<T>(std::move(copy));
        }

        Pipeline<T> take(std::size_t n) const {
            auto taken = FunctionalOps::take(data, n);
            return Pipeline<T>(std::move(taken));
        }

        Pipeline<T> drop(std::size_t n) const {
            auto dropped = FunctionalOps::drop(data, n);
            return Pipeline<T>(std::move(dropped));
        }

        template <typename Func>
        Pipeline<T> tap(Func func) const {
            for (std::size_t i = 0; i < data.size(); ++i) {
                func(data.at(i));
            }
            auto cloned = data.clone();
            return Pipeline<T>(std::move(cloned));
        }

        template <typename Acc, typename Func>
        Acc fold(Acc init, Func func) const {
            return FunctionalOps::fold_left(data, init, func);
        }

        List<T> collect() const {
            return data.clone();
        }

    private:
        List<T> data;
    };

    template <typename T>
    Pipeline<T> from(List<T>&& list) {
        return Pipeline<T>(std::move(list));
    }

    template <typename T>
    Pipeline<T> from(const List<T>& list) {
        auto cloned = list.clone();
        return Pipeline<T>(std::move(cloned));
    }

    // ------------------------------------------------------------
    // Keyword frequency computation
    // ------------------------------------------------------------
    inline List<KeywordFrequency> keyword_frequencies(
        const List<std::string>& tokens,
        const List<std::string>& keywords,
        bool case_sensitive = false) {

        auto normalize = [&](const std::string& value) {
            return case_sensitive ? value : Search::to_lower(value);
        };

        std::unordered_map<std::string, KeywordFrequency> freq_map;
        for (std::size_t i = 0; i < keywords.size(); ++i) {
            const auto& keyword = keywords.at(i);
            freq_map.try_emplace(normalize(keyword),
                                 KeywordFrequency{keyword, 0});
        }

        for (std::size_t i = 0; i < tokens.size(); ++i) {
            auto normalized_token = normalize(tokens.at(i));
            auto it = freq_map.find(normalized_token);
            if (it != freq_map.end()) {
                it->second.count++;
            }
        }

        List<KeywordFrequency> result;
        for (auto& kv : freq_map) {
            result.push_back(kv.second);
        }

        Sort::sort_list(result, [](const KeywordFrequency& a,
                                   const KeywordFrequency& b) {
            if (a.count == b.count) {
                return a.keyword < b.keyword;
            }
            return a.count > b.count;
        });

        return result;
    }

} // namespace FunctionalOps


