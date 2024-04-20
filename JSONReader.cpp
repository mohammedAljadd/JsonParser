#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "JSONReader.h"
#include "Utils.h"
   
// Constructor
JSONReader::JSONReader() {}



// Reading the json file
bool JSONReader::load_lines(std::string filename)
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
    std::cout << "The file is read successfully" << std::endl;


    // Find first level keys
    int count_open_braket = 0;
    for (int i = 0; i < jsonLines.size(); ++i) {
        auto& line = jsonLines[i];


        // The line contains first level key only if there are "" + all previous opening brakets were closed
        if (containsDoubleQuotedWords(line) && count_open_braket == 0) {
            keys.emplace_back(extractWordInQuotes(line));
            keys_indexes.emplace_back(i);
            keyWord_keyIndex[extractWordInQuotes(line)] = i;
           // std::cout << extractWordInQuotes(line) << std::endl;
        }

        if (containsBraket(line) == 0) {
            count_open_braket += 1;
        }
        else if (containsBraket(line) == 1) {
            count_open_braket -= 1;
        }

    }

    return true;
}



// Get keys
std::set<std::string> JSONReader::get_keys() const
{
    std::set<std::string> keys_set;
    std::cout << "The keys are : " << std::endl;
    for (auto& key : keys) {
        std::cout << key << std::endl;
        keys_set.insert(key);
    }
    return keys_set;
}




// Operator [] overloading to access elements
JSONReader JSONReader::operator[](std::string key_) const {

    // Check if the passing key exists, keys contains strings
    auto it = std::find(keys.begin(), keys.end(), key_);

    if (it != keys.end())
    {

        // keyWord_keyIndex
        size_t index = std::distance(keys.begin(), it);
        auto it = keyWord_keyIndex.find(key_);
        int nextIndex = -1;
        if (it != keyWord_keyIndex.end()) {
            // Current key found
            ++it; // Move to the next element
            if (it != keyWord_keyIndex.end()) {
                // Next key found
                nextIndex = it->second;
            }
        }

        std::cout << nextIndex << std::endl;

        JSONReader new_reader = JSONReader();

        // Loop from index to next_index
        std::cout << "Hna : " << std::endl;
        for (auto i = index+1; i < nextIndex; i++) {
            std::cout << this->jsonLines[i] << "  ----  " << std::endl;
            new_reader.jsonLines.emplace_back(this->jsonLines[i]);
        }

        // Get new keys :

        int count_open_braket = 0;
        for (int i = 0; i < new_reader.jsonLines.size(); ++i) {
            auto& line = new_reader.jsonLines[i];


            // The line contains first level key only if there are "" + all previous opening brakets were closed
            if (containsDoubleQuotedWords(line) && count_open_braket == 0) {
                new_reader.keys.emplace_back(extractWordInQuotes(line));
                new_reader.keys_indexes.emplace_back(i);
                new_reader.keyWord_keyIndex[extractWordInQuotes(line)] = i;
                // std::cout << extractWordInQuotes(line) << std::endl;
            }

            if (containsBraket(line) == 0) {
                count_open_braket += 1;
            }
            else if (containsBraket(line) == 1) {
                count_open_braket -= 1;
            }

        }
     

        //std::cout << "The key " << key_ << " exists!" << std::endl;
        return new_reader;
    }
    else
    {
        //std::cout << "The key doesn't exits! " << std::endl;
        return *this;
    }

}