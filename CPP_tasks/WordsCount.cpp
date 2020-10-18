#include <iostream>
#include <fstream>
#include <map>
#include <string>

int main()
{
    std::ifstream inFile;
    std::ofstream outFile;
    std::map<std::string, int> words;
    std::string fileBuffer;
    int length;

    inFile.open("task.in", std::fstream::in);
    outFile.open("task.out", std::ofstream::out);

    while (inFile >> fileBuffer) {
        for (auto iter = fileBuffer.begin(); iter != fileBuffer.end();) {
            if (!isalnum(*iter)) {
                fileBuffer.erase(iter);
            } else {
                ++iter;
            }
        }

        if (words.count(fileBuffer)) {
            words[fileBuffer] += 1;
        } else {
            words[fileBuffer] = 1;
        }
    }

    auto word = words.begin();

    for (; word != std::prev(words.end());) {
        outFile << word->first << " " << word->second << std::endl;
        ++word;
    }

    outFile << word->first << " " << word->second;

    words.clear();
    inFile.close();
    outFile.close();

    return 0;
}
