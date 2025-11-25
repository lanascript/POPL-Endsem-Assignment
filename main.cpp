#include <iostream>
#include <string>
#include "core/FileReader.hpp"
#include "core/Search.hpp"
#include "core/Sort.hpp"
#include "core/Aggregation.hpp"
#include "core/FunctionalOps.hpp"
#include "interface/Menu.hpp"

namespace {
    void run_scripted_demo() {
        std::cout << "=== POPL Endsem Functional Demo ===\n";

        auto tokens = FileReader::read_tokens("tests/sample.txt");
        tokens.print("Tokens");

        std::cout << "\nIndex of 'hello': "
                  << Search::linear_search(tokens, std::string("hello")) << "\n";

        Sort::sort_list(tokens);
        tokens.print("Sorted tokens");

        auto filtered = Aggregation::filter_list(tokens, [](const std::string& s) {
            return s.size() > 3;
        });
        filtered.print("Filtered tokens (len > 3)");

        try {
            auto keywords = FileReader::read_tokens("tests/keywords.txt");
            auto freq = FunctionalOps::keyword_frequencies(tokens, keywords);
            freq.print("Keyword frequency");
        } catch (const std::exception& ex) {
            std::cout << "Keyword frequency demo skipped: " << ex.what() << "\n";
        }

        auto pipeline = FunctionalOps::from(tokens)
            .filter([](const std::string& s) { return s.size() > 3; })
            .map([](const std::string& s) { return s + "!"; })
            .take(5)
            .collect();

        pipeline.print("Pipeline demo (len>3, append '!')");

        std::cout << "\nDemo complete.\n";
    }
}

int main(int argc, char** argv) {
    if (argc > 1 && std::string(argv[1]) == "--menu") {
        MenuApp app;
        app.run();
        return 0;
    }

    run_scripted_demo();
    std::cout << "\nRun './demo --menu' for the interactive interface.\n";
    return 0;
}
