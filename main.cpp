#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include "core/FileReader.hpp"
#include "core/Search.hpp"
#include "core/Sort.hpp"
#include "core/Aggregation.hpp"
#include "core/FunctionalOps.hpp"
#include "interface/Menu.hpp"

namespace {

    List<std::string> load_tokens_from_directory(const std::string& corpus_dir) {
        namespace fs = std::filesystem;

        if (!fs::exists(corpus_dir)) {
            throw std::runtime_error("Demo corpus directory missing: " + corpus_dir);
        }

        List<std::string> aggregated;
        std::size_t files_found = 0;

        std::cout << "Scanning " << corpus_dir << " for .txt files...\n";
        for (const auto& entry : fs::directory_iterator(corpus_dir)) {
            if (!entry.is_regular_file() || entry.path().extension() != ".txt") {
                continue;
            }
            std::cout << "   - " << entry.path().filename().string() << "\n";
            aggregated.append(FileReader::read_tokens(entry.path().string()));
            ++files_found;
        }

        if (files_found == 0) {
            throw std::runtime_error("No .txt files found in " + corpus_dir);
        }

        std::cout << "Collected " << aggregated.size() << " tokens from "
                  << files_found << " files.\n";
        return aggregated;
    }

    void run_scripted_demo() {
        std::cout << "=== POPL Endsem Functional Demo ===\n";

        const std::string corpus_dir = "demo_data/articles";
        const std::string keyword_file = "demo_data/keywords.txt";

        auto tokens = load_tokens_from_directory(corpus_dir);
        tokens.print("Aggregated tokens");

        std::cout << "\nIndex of 'functional': "
                  << Search::linear_search(tokens, std::string("functional")) << "\n";

        Sort::sort_list(tokens);
        tokens.print("Sorted tokens");

        auto filtered = Aggregation::filter_list(tokens, [](const std::string& s) {
            return s.size() > 3;
        });
        filtered.print("Filtered tokens (len > 3)");

        try {
            auto keywords = FileReader::read_tokens(keyword_file);
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
