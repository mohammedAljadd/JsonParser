#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

class JSONReader 
{

    private:

        mutable std::vector<std::string> keys;
        std::vector <int> keys_indexes;
        std::map<std::string, std::string> data;
        std::vector<std::string> jsonLines;
        std::map<std::string, int> keyWord_keyIndex;
        std::map<std::string, std::string> keyValueStore;
    

    public:

        // constructor
        JSONReader();
           
        // Load lines and find first level keys
        bool load(std::string);

        // Get keys
        std::set<std::string> get_keys() const;

        // Operator to access data via keys
        JSONReader operator[](std::string key) const;


    private:
        // Path to the json file
        std::string filename;
};