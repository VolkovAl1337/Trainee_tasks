#include <stdio.h>

int main()
{
    char buffer[255];
    int sequenceLen = 0;
    FILE* filePtr;
    int endOfFileCheck;

    filePtr = fopen("task.in", "r");

    if (filePtr) {
        while (fscanf(filePtr, "%s", buffer) != EOF) {
            sequenceLen++;
        }
    }

    fclose(filePtr);
    filePtr = fopen("task.out", "w");

    fprintf(filePtr, "%d",sequenceLen);

    return 0;
}
