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