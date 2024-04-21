#pragma once
#include <string>
#include <cctype>

std::string trim(const std::string& str);

// Check if a line contains double quotes
bool containsDoubleQuotedWords(const std::string& line);

// return 0 if line contains {, 1 for }, otherwise -1
int containsBraket(const std::string& line);


// Extract key from a line
std::string extractWordInQuotes(const std::string& line);


// Extract value from a line that contains a key but no brakets, like : "MyKey": 15
std::string extractValueKeyNoBraket(const std::string& input);