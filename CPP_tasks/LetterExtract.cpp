#include <iostream>
#include <fstream>
#include <set>
#include <cctype>

int main()
{
    std::ifstream inFile;
    std::ofstream outFile;
    std::set<char> letters;
    char fileChar;

    inFile.open("task.in", std::fstream::in);
    outFile.open("task.out", std::ofstream::out);

    while (inFile.get(fileChar)) {
        if (std::isalpha(fileChar)) {
            fileChar = std::tolower(fileChar);
            letters.insert(fileChar);
        }
    }

    for (auto letter : letters) {
        outFile << letter;
    }
    outFile << std::endl;

    inFile.close();
    outFile.close();

    return 0;
}

