#include <iostream>
#include "../core/FileReader.hpp"

int main() {
    try {
        auto lines = FileReader::read_lines("tests/sample.txt");
        lines.print("Lines");

        auto tokens = FileReader::read_tokens("tests/sample.txt");
        tokens.print("Tokens");

        std::string all = FileReader::read_all("tests/sample.txt");
        std::cout << "\nWhole File:\n" << all << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
    }
}
