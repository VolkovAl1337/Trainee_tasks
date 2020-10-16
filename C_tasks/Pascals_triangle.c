#define TRIANGLE_LAST_EL 1
#include <stdio.h>

void printPascal(int numOfLines);
int pascalElCalc(int row, int col);

int main(int argc, char* argv[])
{
    int numOfLines;

    scanf("%d", &numOfLines);

    printPascal(numOfLines);

    return 0;
}

void printPascal(int numOfLines)
{
    int row, col;

    for (row = 0; row < numOfLines; row++) {
        for (col = 0; col < row; col++) {
            printf("%d ", pascalElCalc(row, col));
        }
        printf("%i\n", TRIANGLE_LAST_EL);
    }
}

int pascalElCalc(int row, int col)
{
    if ((col == 0) || (col == row)) {
        return 1;
    }

    return pascalElCalc(row - 1, col - 1) + pascalElCalc(row - 1, col);
}
