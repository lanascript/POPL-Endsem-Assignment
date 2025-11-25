#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include "List.hpp"   // List<T> abstraction

class FileReader {
public:

    // ---------------------------------------------------------
    // Read file line by line → List<std::string>
    // ---------------------------------------------------------
    static List<std::string> read_lines(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("FileReader: Cannot open file " + filepath);
        }

        List<std::string> lines;
        std::string line;

        while (std::getline(file, line)) {
            lines.push_back(line);
        }

        return lines;
    }

    // ---------------------------------------------------------
    // Read file and split by whitespace → List<std::string>
    // ---------------------------------------------------------
    static List<std::string> read_tokens(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("FileReader: Cannot open file " + filepath);
        }

        List<std::string> tokens;
        std::string word;

        while (file >> word) {
            tokens.push_back(word);
        }

        return tokens;
    }

    // ---------------------------------------------------------
    // Read entire file as a single string
    // ---------------------------------------------------------
    static std::string read_all(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("FileReader: Cannot open file " + filepath);
        }

        std::ostringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
};
