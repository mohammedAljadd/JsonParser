#include <iostream>
#include <string>
#include "Utils.h"

// Check if a line contains double quotes
bool containsDoubleQuotedWords(const std::string& line) {
    bool inQuotes = false;

    for (char c : line) {
        if (c == '"') {
            inQuotes = !inQuotes;
        }
        else if (!inQuotes && std::isspace(c)) {
            // If not inside quotes and encountered whitespace, reset inQuotes flag
            inQuotes = false;
        }
        else if (!inQuotes && !std::isspace(c)) {
            // If not inside quotes and encountered non-whitespace, return true
            return true;
        }
    }

    return false;
}

// return 0 if line contains {, 1 for }, otherwise -1
int containsBraket(const std::string& line) {
    for (char c : line) {
        if (c == '{') {
            return 0; // Return 0 if an opening curly brace is found
        }
        else if (c == '}') {
            return 1; // Return 1 if a closing curly brace is found
        }
    }
    return -1; // Return -1 if neither brace is found
}

// Extract key from a line
std::string extractWordInQuotes(const std::string& line) {
    size_t startPos = line.find('"');
    if (startPos == std::string::npos) {
        // No opening quote found
        return "";
    }

    size_t endPos = line.find('"', startPos + 1);
    if (endPos == std::string::npos) {
        // No closing quote found
        return "";
    }

    return line.substr(startPos + 1, endPos - startPos - 1);
}