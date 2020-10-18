#define CAP_ABC_START 'A'
#define CAP_ABC_END 'Z'
#define LOW_ABC_START 'a'
#define LOW_ABC_END 'z'
#define ABC_NUM_DIFF (LOW_ABC_START - CAP_ABC_START)
#include <iostream>
#include <fstream>
#include <list>

int main()
{
    std::ifstream inFile;
    std::ofstream outFile;
    std::list<char> letters;
    char fileChar;
    bool uniqueCharFlag;

    inFile.open("task.in", std::fstream::in);
    outFile.open("task.out", std::ofstream::out);

    while (inFile.get(fileChar)) {
        if (fileChar >= CAP_ABC_START && fileChar <= CAP_ABC_END || fileChar >= LOW_ABC_START && fileChar <= LOW_ABC_END) {
            if (fileChar < LOW_ABC_START) {
                fileChar += ABC_NUM_DIFF;
            }

            uniqueCharFlag = true;

            for (char listLetter: letters) {
                if (listLetter == fileChar) {
                    uniqueCharFlag = false;
                    break;
                }
            }

            if (uniqueCharFlag) {
                letters.push_back(fileChar);
                outFile << fileChar;
            }
        }
    }

    letters.clear();
    inFile.close();
    outFile.close();

    return 0;
}
