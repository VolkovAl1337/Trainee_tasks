#define NUM_CHAR_BEGIN '0'
#define MAX_DECIMAL_NUM 10
#define CAPITAL_ABC_CHAR_BEGIN ('A' - MAX_DECIMAL_NUM)
#include <stdio.h>
#include <stdlib.h>

void newBaseElOut (int);

int main()
{
    int numToConvert, base;
    int newNumLentgh = 0;

    scanf("%i %i", &numToConvert, &base);

    if (numToConvert == 0) {
        printf("%c\n", NUM_CHAR_BEGIN);
        return 0;
    } else if (numToConvert < 0) {
        printf("-");
        numToConvert = -numToConvert;
    }

    int tempNum = numToConvert;
    int baseMaxPow = 1;

    while (tempNum > 0) {
        newNumLentgh++;
        tempNum /= base;
        baseMaxPow *= base;
    }

    for (int i = 0; i < newNumLentgh; i++) {
        baseMaxPow /= base;
        newBaseElOut((numToConvert / baseMaxPow) % base);
    }

    printf("\n");
    return 0;
}

void newBaseElOut(int newBaseNumEl)
{
    if (newBaseNumEl >= MAX_DECIMAL_NUM) {
        printf("%c", newBaseNumEl + CAPITAL_ABC_CHAR_BEGIN);
    } else {
        printf("%c", newBaseNumEl + NUM_CHAR_BEGIN);
    }
}
