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
                currentValue = "{\n"; // reset the current value
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
                    keyValueStore[currentKey] = currentValue+ "}\n";
                    currentValue = ""; // reset the current value
                }
                else {
                    currentValue = currentValue + line + "\n"; // concatenate the trimmed line to the current value
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
    for (const auto& pair : keyValueStore){
        keys_set.insert(pair.first);
        std::cout << "Key : " << pair.first << " : " << "\nValues:" << pair.second << std::endl;
    }
    
    return keys_set;
}




// Operator [] overloading to access elements
JSONReader JSONReader::operator[](std::string key_) const {
    if (keyValueStore.find(key_) != keyValueStore.end()) {
        std::string Values = keyValueStore.at(key_);

        JSONReader new_reader = JSONReader();
        std::vector<std::string> lines = splitStringIntoLines(Values);

        // Find keys and values and store them in new_reader.keyValueStore
        bool skipFirstLine = true;
        int count_open_braket = 0;
        std::string currentKey;
        std::string currentValue = "";

        for (std::string& line : lines) {
            std::cout << line << std::endl;
            if (skipFirstLine)
            {
                skipFirstLine = false;
                continue; // skip the first line that contains the {
            }
            

            // Key is fonund
            if (containsDoubleQuotedWords(line) && count_open_braket == 0)
            {
                
                currentKey = extractWordInQuotes(line);
                currentValue = "{\n"; // reset the current value
                if (containsBraket(line) == 0) {
                    count_open_braket += 1;
                }

                else if (containsBraket(line) == -1) {
                    new_reader.keyValueStore[currentKey] = extractValueKeyNoBraket(line);
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
                    new_reader.keyValueStore[currentKey] = currentValue + "}\n";
                    currentValue = ""; // reset the current value
                }
                else {
                    currentValue = currentValue + line + "\n"; // concatenate the trimmed line to the current value
                }
            }
        }



        return new_reader;

    }
    else {
        std::cout << "The key doesn't exists!" << std::endl;
        return *(this);
    }
}
