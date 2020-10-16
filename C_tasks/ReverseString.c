#include <stdio.h>
#include <stdlib.h>

int main()
{
    char* strToReverse = NULL;
    char* tempCharPtr;
    char* tempCharPtrStart;
    char tempChar;
    size_t strSize = 0;
    ssize_t characters = 0;

    characters = getline(&strToReverse, &strSize, stdin);

    tempCharPtrStart = strToReverse;
    tempCharPtr = strToReverse + characters;

    while (tempCharPtrStart < tempCharPtr) {
        tempChar = *tempCharPtrStart;
        *tempCharPtrStart = *(--tempCharPtr);
        *tempCharPtr = tempChar;
        tempCharPtrStart++;
    }

    printf("%s\n", strToReverse);

    free(strToReverse);
    return 0;
}
