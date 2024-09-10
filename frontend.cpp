#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
    
    std::ifstream inFile(argv[1], std::ios::binary);
    if (!inFile) {
        std::cerr << "can't open file" << std::endl;
        return 1;
    }

    std::vector<char> chars;
    char ch;
    while (inFile.get(ch)) {
        chars.push_back(ch);
    }
    inFile.close();
    for (int i=0;i<chars.size()) {
        switch (chars[i]) {
           
        }
    }
    std::cout << std::endl;

    return 0;
}