#include <cassert>
#include <iostream>
#include "../core/FunctionalOps.hpp"

int main() {
    List<std::string> tokens;
    tokens.push_back("hello");
    tokens.push_back("world");
    tokens.push_back("hello");
    tokens.push_back("lambda");

    auto transformed = FunctionalOps::from(tokens)
        .filter([](const std::string& s) { return s.size() > 4; })
        .map([](const std::string& s) { return s + "_x"; })
        .collect();

    assert(transformed.size() == 4);
    assert(transformed.at(0) == "hello_x");
    assert(transformed.at(1) == "world_x");
    assert(transformed.at(3) == "lambda_x");

    List<std::string> keywords;
    keywords.push_back("hello");
    keywords.push_back("lambda");

    auto freq = FunctionalOps::keyword_frequencies(tokens, keywords);
    assert(freq.size() == 2);
    assert(freq.at(0).keyword == "hello");
    assert(freq.at(0).count == 2);
    assert(freq.at(1).keyword == "lambda");

    std::cout << "All functional pipeline tests passed.\n";
    return 0;
}

