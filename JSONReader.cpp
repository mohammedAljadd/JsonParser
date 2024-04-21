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
bool JSONReader::load(std::string filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) 
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    else
    {
        // to store lines
        std::string line;  


        bool skipFirstLine = true;

        // Retreive the key from the line, if the line contains a key
        std::string currentKey;

        // Concatenate lines that are located between current key's line and next key's line
        std::string currentValue = "";
        

        // A line contains a key if all previous brakets are closed, this apply also for first key
        int count_open_braket = 0;


        while (std::getline(file, line)) 
        {
            if (skipFirstLine) 
            {
                skipFirstLine = false;
                continue; // skip the first line that contains the {
            }

            // Key is fonund
            if (containsDoubleQuotedWords(line) && count_open_braket == 0) 
            {
                currentKey = extractWordInQuotes(line);
                currentValue = ""; // reset the current value
                if (containsBraket(line) == 0) {
                    count_open_braket += 1;
                }

                else if (containsBraket(line) == -1) {
                    keyValueStore[currentKey] = extractValueKeyNoBraket(line);
                }
            }

            // Key not found yet --> add the current line to currentValue
            else {
                

                if (containsBraket(line) == 0) 
                {
                    count_open_braket += 1;
                }
                
                else if (containsBraket(line) == 1) 
                {
                    count_open_braket -= 1;
                }
                if (count_open_braket == 0) { // if we've reached the end of the value
                    keyValueStore[currentKey] = currentValue;
                    currentValue = ""; // reset the current value
                }
                else {
                    currentValue += line ; // concatenate the trimmed line to the current value
                }
            }
            
        } 
        

        

        file.close();
        std::cout << "The file is read successfully" << std::endl;

        return true;
    }
}


// Get keys
std::set<std::string> JSONReader::get_keys() const
{
    std::set<std::string> keys_set;
    std::cout << "The keys are : " << std::endl;
    for (const auto& pair : keyValueStore){
        keys_set.insert(pair.first);
        std::cout << pair.first << " " << pair.second << std::endl;
    }
    
    return keys_set;
}




// Operator [] overloading to access elements
JSONReader JSONReader::operator[](std::string key_) const {
    auto it = std::find(keys.begin(), keys.end(), key_);
    if (it != keys.end()) {
        size_t index = std::distance(keys.begin(), it);
        int nextIndex = -1;
        auto it2 = keyWord_keyIndex.find(key_);
        if (it2 != keyWord_keyIndex.end()) {
            ++it2; // Move to the next element
            if (it2 != keyWord_keyIndex.end()) {
                nextIndex = it2->second;
            }
        }

        JSONReader new_reader;
        for (auto i = index + 1; i < nextIndex; i++) {
            new_reader.jsonLines.emplace_back(this->jsonLines[i]);
        }

        // Update keys, keys_indexes, and keyWord_keyIndex members
        new_reader.keys.clear();
        new_reader.keys_indexes.clear();
        new_reader.keyWord_keyIndex.clear();

        int count_open_braket = 0;
        for (int i = 0; i < new_reader.jsonLines.size(); ++i) {
            auto& line = new_reader.jsonLines[i];
            if (containsDoubleQuotedWords(line) && count_open_braket == 0) {
                new_reader.keys.emplace_back(extractWordInQuotes(line));
                new_reader.keys_indexes.emplace_back(i);
                new_reader.keyWord_keyIndex[extractWordInQuotes(line)] = i;
            }

            if (containsBraket(line) == 0) {
                count_open_braket += 1;
            }
            else if (containsBraket(line) == 1) {
                count_open_braket -= 1;
            }
        }

        return new_reader;
    }
    else {
        return *this;
    }
}