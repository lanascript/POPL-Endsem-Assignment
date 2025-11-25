#include <iostream>
#include "../core/Aggregation.hpp"

int main() {
    List<int> L;
    L.push_back(3);
    L.push_back(1);
    L.push_back(2);

    std::cout << "Inversions: " 
              << Aggregation::count_inversions(L) << "\n";

    std::cout << "Average: "
              << Aggregation::average(L) << "\n";

    auto doubled = Aggregation::map_list<int, int>(L, [](int x){ return x*2; });
    doubled.print("Doubled list");

    auto filtered = Aggregation::filter_list<int>(L, [](int x){ return x > 1; });
    filtered.print("Filtered >1");

    auto sum = Aggregation::reduce_list<int, int>(L, 0, [](int acc, int x){
        return acc + x;
    });

    std::cout << "Sum via reduce: " << sum << "\n";

    return 0;
}
