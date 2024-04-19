#include <iostream>
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
    JSONReader(const std::string& filename) : filename(filename) {}

    
    // Check if a line contains double quotes
    bool containsDoubleQuotedWords(const std::string& line) const{
        bool inQuotes = false;

        for (char c : line) {
            if (c == '"') {
                inQuotes = !inQuotes;
            } else if (!inQuotes && std::isspace(c)) {
                // If not inside quotes and encountered whitespace, reset inQuotes flag
                inQuotes = false;
            } else if (!inQuotes && !std::isspace(c)) {
                // If not inside quotes and encountered non-whitespace, return true
                return true;
            }
        }

        return false;
    }

    // return 0 if line contains {, 1 for }, otherwise -1
    int containsBraket(const std::string& line) const {
        for (char c : line) {
            if (c == '{') {
                return 0; // Return 0 if an opening curly brace is found
            } else if (c == '}') {
                return 1; // Return 1 if a closing curly brace is found
            }
        }
        return -1; // Return -1 if neither brace is found
    }


    // Reading the json file
    bool ReadFile() 
    {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return false;
        }

        std::string line;
        bool isFirstLine = true;
        while (std::getline(file, line)) {
            if (!isFirstLine && !file.eof()) {
                // Exclude the first and last lines
                jsonLines.emplace_back(line);
            }
            isFirstLine = false;
        }

        file.close();
        return true;
    }

    // Extract key from a line
    std::string extractWordInQuotes(const std::string& line) const{
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

    // Print hierarchy
    void PrintHierarchy(int& level) const{
        if(level == 1){
            int count_open_braket = 0;
            for(auto& line : jsonLines){
                // Check if the first level key is in line

                // The line contains first level key only if there are "" + all previous opening brakets were closed
                if(containsDoubleQuotedWords(line) && count_open_braket == 0){
                    keys.emplace_back(extractWordInQuotes(line));
                    std::cout << extractWordInQuotes(line) << std::endl;   
                }

                if(containsBraket(line) == 0){
                    count_open_braket += 1;
                }
                else if(containsBraket(line) == 1){
                    count_open_braket -= 1;
                }

            }
        }
    }

    // Operator to access elements by index
    std::string operator[](std::string key_) const {
        
        // Check if the passing key exists
        if (std::find(keys.begin(), keys.end(), key_) != keys.end())
        {
            std::cout << "The key " << key_ << " exists!" << std::endl;
        }
        else
        {
            std::cout << "The key doesn't exits! " << std::endl;
        }
        return key_;
    }


private:
    // Path to the json file
    std::string filename;
};

int main() {
    // Example usage
    JSONReader reader("example.json");
    if (reader.ReadFile()) {
        std::cout << "File read successfully." << std::endl;
   
    }
    int level = 1;
    reader.PrintHierarchy(level);


    reader["two"];

}