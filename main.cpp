#include <iostream>
#include "JSONReader.h"

int main() {

   
    JSONReader reader = JSONReader();

    // Load lines
    reader.load("example.json");

    

    JSONReader new_reader = reader["one"];
       
    std::cout << "New reader : \n\n" << std::endl;
    new_reader.get_keys();


    std::cin.get();


}