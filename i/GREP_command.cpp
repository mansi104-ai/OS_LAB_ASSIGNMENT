#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    // Step 4: Check if argc != 3, then print error
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <pattern> <filename>" << std::endl;
        return 1;
    }

    // Step 5: Copy the pattern and filename from argv[1] and argv[2] respectively
    std::string pattern = argv[1];
    std::string filename = argv[2];

    // Step 6: Open the file in read mode
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Unable to open file '" << filename << "'" << std::endl;
        return 1;
    }

    // Step 7: Read the content from file one by one and store it in an array
    std::string line;
    while (std::getline(file, line)) {
        // Step 8: Compare the pattern with the array elements, if it matches, print the result
        if (line.find(pattern) != std::string::npos) {
            std::cout << line << std::endl;
        }
    }

    // Step 9: Print file not found if pattern is not found in the file
    if (file.eof() && !file.fail()) {
        std::cerr << "Pattern '" << pattern << "' not found in file '" << filename << "'" << std::endl;
        return 1;
    } 
    return 0;
}