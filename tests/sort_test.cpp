#include <iostream>
#include "../core/Sort.hpp"

int main() {
    List<int> numbers;
    numbers.push_back(50);
    numbers.push_back(20);
    numbers.push_back(40);
    numbers.push_back(10);

    std::cout << "Before sort: ";
    numbers.print();

    Sort::sort_list(numbers);

    std::cout << "After default sort: ";
    numbers.print();

    // Custom comparator: descending order
    Sort::sort_list(numbers, [](int a, int b) {
        return a > b;
    });

    std::cout << "After custom descending sort: ";
    numbers.print();

    return 0;
}
