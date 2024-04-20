#pragma once
#include <string>

// Check if a line contains double quotes
bool containsDoubleQuotedWords(const std::string& line);

// return 0 if line contains {, 1 for }, otherwise -1
int containsBraket(const std::string& line);


// Extract key from a line
std::string extractWordInQuotes(const std::string& line);