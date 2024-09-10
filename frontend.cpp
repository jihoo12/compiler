#include <iostream>
#include <string>
#include <fstream>
#include <vector>
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
    std::ifstream inFile(argv[2]);
    std::string line;
    std::vector<std::string> lines;

    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            lines.push_back(line);
        }
        inFile.close();
    } else {
        std::cerr << "can't open file" << std::endl;
        return 1;
    }
    return 0;
}