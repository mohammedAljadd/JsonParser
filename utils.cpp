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
    int value = -1;
    for (char c : line) {
        if (c == '{') {
            value = 0; // Return 0 if an opening curly brace is found
            break;
        }
        else if (c == '}') {
            value = 1; // Return 1 if a closing curly brace is found
            break;
        }
    }
    return value; // Return -1 if neither brace is found
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



std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}



std::string extractValueKeyNoBraket(const std::string& input) {
    size_t startPos = input.find('":'); // Find the first double quote
    if (startPos == std::string::npos)
        return ""; // Return empty string if opening quote not found

    size_t endPos = input.find(',', startPos + 1); // Find the next double quote
    if (endPos == std::string::npos)
        return ""; // Return empty string if closing quote not found

    return input.substr(startPos + 1, endPos - startPos - 1); // Extract substring between the quotes
}