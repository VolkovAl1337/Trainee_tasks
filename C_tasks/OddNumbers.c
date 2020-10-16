#define EVEN_CHECK 2
#define NUM_DIFFERENCE 2
#include <stdio.h>

int main()
{
    int numIterative, numBigger;
    scanf("%i%i", &numIterative, &numBigger);
    if (numIterative % EVEN_CHECK == 0) {
        numIterative += 1;

    }
    while(numIterative <= numBigger - NUM_DIFFERENCE) {
        printf("%i ", numIterative);
        numIterative += NUM_DIFFERENCE;
    }

    if (numIterative <= numBigger) {
        printf("%i\n",numIterative);
    }

    return 0;
}
