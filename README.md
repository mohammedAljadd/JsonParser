# JsonParser (still in development)

JsonParser is a lightweight JSON parser library designed for simplicity and ease of use.

## TO-DO list:

- Write comprehensive unit tests to ensure robust parsing of various JSON file formats, including files with different indent levels, empty JSON files, etc.
- Optimize the library for performance and memory usage. Identify and fix any memory leaks and redundant code to ensure efficient operation.
- Package the project and write the documentation.

In the future, feel free to contribute to the development of JsonParser by submitting pull requests, reporting bugs, or suggesting new features!

## Completed Tasks:

- Read json file, get keys and values
- Get values from a key if exists by overloading operator []
- Save parsed JSON data as a JSON file

## To Do:

- Overload operators ==, =, +, and - for intuitive JSON manipulation.
  - Ensure these operators are implemented to perform actions such as comparison, assignment, merging, and removal of JSON elements.
- Write comprehensive unit tests to cover various JSON file formats and edge cases.
- Optimize the library for performance and memory usage, addressing any identified bottlenecks or memory leaks.
- Package the project for easy distribution and write clear documentation to guide users on usage and contribution.

## Usage Example

```cpp
#include <iostream>
#include "JSONReader.h"

// Initialize an object
JSONReader reader = JSONReader();

// Load lines from the file
reader.load("example.json");

// Get values from a key --> returns a new JSONReader
JSONReader new_reader = reader["one"];

// Save results
new_reader.save("results.json");
```

## Contributing
If you're interested in contributing to JsonParser, you can:

- Submit pull requests with new features or bug fixes.
- Report any bugs or issues you encounter.
- Suggest enhancements or new features to improve the library.

Your contributions are highly appreciated!