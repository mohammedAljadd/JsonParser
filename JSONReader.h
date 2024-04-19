#pragma once


#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


class JSONReader 
{

public:

    // Lines in the json file
    std::vector<std::string> jsonLines;

    // Keys
    mutable std::vector<std::string> keys;

    // Constructor
    JSONReader(const std::string& filename);

    
    // Check if a line contains double quotes
    bool containsDoubleQuotedWords(const std::string& line) const;

    // return 0 if line contains {, 1 for }, otherwise -1
    int containsBraket(const std::string& line) const;


    // Reading the json file
    bool ReadFile();

    // Extract key from a line
    std::string extractWordInQuotes(const std::string& line) const;

    // Print hierarchy
    void PrintHierarchy(int& level) const;

    // Operator to access elements by index
    std::string operator[](std::string key_) const ;


private:
    // Path to the json file
    std::string filename;
};