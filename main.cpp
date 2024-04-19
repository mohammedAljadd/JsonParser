#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "JSONReader.h"

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