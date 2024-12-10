/*NB: test x=0*/

#include <stdio.h>
#include <stdlib.h>

// #define EVAL //UNCOMMENT for testing but REMOVE from submission

int main()
{
    unsigned int x;
    unsigned int res1 = 0, res2 = 0, res3 = 0;

    // INPUT: x must be the input value, do not overwrite it
    printf("Enter a positive integer: ");
    scanf("%u", &x);
    // calculate here

    // do NOT add code after this point
    // OUTPUT
    printf("Actual result:\n");
    printf("%u %u %u\n", res1, res2, res3);

// DON'T REMOVE from submittion
#ifdef EVAL
    eval(x, res1, res2, res3);
#endif
    return 0;
}