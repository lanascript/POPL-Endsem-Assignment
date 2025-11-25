#include <iostream>
#include "../core/Search.hpp"
#include "../core/FileReader.hpp"

int main() {
    List<std::string> L;
    L.push_back("hello");
    L.push_back("world");
    L.push_back("HELLO");
    L.push_back("example");

    std::cout << "Index of 'world': "
              << Search::linear_search(L, std::string("world")) << "\n";

    std::cout << "Contains 'hello'? "
              << (Search::contains(L, std::string("hello")) ? "yes" : "no") << "\n";

    auto all = Search::find_all(L, std::string("hello"));
    all.print("All indices for 'hello'");

    auto ci = Search::search_substring_ci(L, "hello");
    ci.print("Case-insensitive match for 'hello'");

    return 0;
}
