#include <iostream>
#include "core/FileReader.hpp"
#include "core/Search.hpp"
#include "core/Sort.hpp"
#include "core/Aggregation.hpp"

int main() {
    std::cout << "=== POPL Endsem Demo ===\n";

    // Read tokens from file
    auto tokens = FileReader::read_tokens("tests/sample.txt");
    tokens.print("Tokens");

    // Search
    std::cout << "\nIndex of 'hello': " 
              << Search::linear_search(tokens, std::string("hello")) << "\n";

    // Sort
    Sort::sort_list(tokens);
    tokens.print("Sorted tokens");

    // Aggregation
    auto filtered = Aggregation::filter_list(tokens, [](const std::string& s) {
        return s.size() > 3;
    });
    filtered.print("Filtered tokens (len > 3)");

    std::cout << "\nDemo complete.\n";
    return 0;
}
