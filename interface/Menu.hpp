#pragma once

#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <string>
#include "../core/FileReader.hpp"
#include "../core/FunctionalOps.hpp"
#include "../core/List.hpp"
#include "../core/Search.hpp"
#include "../core/Sort.hpp"

class MenuApp {
public:
    void run();

private:
    List<std::string> tokens;
    List<std::string> keywords;
    bool tokens_loaded = false;
    bool keywords_loaded = false;

    void show_menu() const;
    int read_choice() const;

    void load_tokens();
    void load_keywords();
    void display_tokens() const;
    void search_keyword() const;
    void sort_tokens();
    void show_keyword_frequency() const;
    void run_transform_pipeline() const;

    static std::string prompt_path(const std::string& label);
    static bool ensure_loaded(bool state, const std::string& resource);
    static std::string prompt(const std::string& label);
};

inline void MenuApp::run() {
    std::cout << "=== Functional-OO List Toolkit ===\n";
    bool running = true;
    while (running) {
        show_menu();
        int choice = read_choice();
        switch (choice) {
            case 1: load_tokens(); break;
            case 2: load_keywords(); break;
            case 3: display_tokens(); break;
            case 4: search_keyword(); break;
            case 5: sort_tokens(); break;
            case 6: show_keyword_frequency(); break;
            case 7: run_transform_pipeline(); break;
            case 0:
                running = false;
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Unknown choice. Try again.\n";
        }
    }
}

inline void MenuApp::show_menu() const {
    std::cout << "\n--------------------------------------------------\n";
    std::cout << "1) Load tokens from file\n";
    std::cout << "2) Load keywords file\n";
    std::cout << "3) Show loaded tokens (preview)\n";
    std::cout << "4) Search keyword (case-insensitive)\n";
    std::cout << "5) Sort tokens alphabetically\n";
    std::cout << "6) Keyword frequency table\n";
    std::cout << "7) Transformation pipeline demo\n";
    std::cout << "0) Exit\n";
    std::cout << "Choice: ";
}

inline int MenuApp::read_choice() const {
    int choice = -1;
    std::cin >> choice;
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    return choice;
}

inline std::string MenuApp::prompt_path(const std::string& label) {
    std::cout << label << ": ";
    std::string path;
    std::cin >> path;
    return path;
}

inline std::string MenuApp::prompt(const std::string& label) {
    std::cout << label << ": ";
    std::string value;
    std::cin >> value;
    return value;
}

inline bool MenuApp::ensure_loaded(bool state, const std::string& resource) {
    if (!state) {
        std::cout << "Please load " << resource << " first.\n";
    }
    return state;
}

inline void MenuApp::load_tokens() {
    try {
        const auto path = prompt_path("Enter token file path");
        tokens = FileReader::read_tokens(path);
        tokens_loaded = true;
        std::cout << "Loaded " << tokens.size() << " tokens.\n";
    } catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << "\n";
    }
}

inline void MenuApp::load_keywords() {
    try {
        const auto path = prompt_path("Enter keyword file path");
        keywords = FileReader::read_tokens(path);
        keywords_loaded = true;
        std::cout << "Loaded " << keywords.size() << " keywords.\n";
    } catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << "\n";
    }
}

inline void MenuApp::display_tokens() const {
    if (!ensure_loaded(tokens_loaded, "tokens")) return;
    const auto preview = std::min<std::size_t>(tokens.size(), 20);
    std::cout << "First " << preview << " tokens: ";
    for (std::size_t i = 0; i < preview; ++i) {
        std::cout << tokens.at(i) << " ";
    }
    std::cout << "\nTotal tokens: " << tokens.size() << "\n";
}

inline void MenuApp::search_keyword() const {
    if (!ensure_loaded(tokens_loaded, "tokens")) return;
    auto keyword = prompt("Enter keyword to search");
    auto matches = Search::search_substring_ci(tokens, keyword);
    if (matches.empty()) {
        std::cout << "No matches found for \"" << keyword << "\".\n";
        return;
    }

    std::cout << "Found " << matches.size() << " matches at indices: ";
    for (std::size_t i = 0; i < matches.size(); ++i) {
        std::cout << matches.at(i) << " ";
    }
    std::cout << "\n";
}

inline void MenuApp::sort_tokens() {
    if (!ensure_loaded(tokens_loaded, "tokens")) return;
    Sort::sort_list(tokens);
    std::cout << "Tokens sorted alphabetically.\n";
}

inline void MenuApp::show_keyword_frequency() const {
    if (!ensure_loaded(tokens_loaded, "tokens")) return;
    if (!ensure_loaded(keywords_loaded, "keywords")) return;

    auto freq = FunctionalOps::keyword_frequencies(tokens, keywords, false);
    std::cout << "\nKeyword Frequency (descending):\n";
    freq.print("keyword -> count");
}

inline void MenuApp::run_transform_pipeline() const {
    if (!ensure_loaded(tokens_loaded, "tokens")) return;

    auto pipeline = FunctionalOps::from(tokens)
        .filter([](const std::string& s) { return s.size() > 3; })
        .map([](const std::string& s) {
            std::string out = s;
            for (char& c : out) c = static_cast<char>(std::toupper(c));
            return out;
        })
        .take(10);

    auto result = pipeline.collect();
    result.print("Top 10 transformed tokens (len > 3, upper-case)");
}

