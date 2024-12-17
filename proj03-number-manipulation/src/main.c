/*NB: test x=0*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// #define EVAL // UNCOMMENT for testing but REMOVE from submission

int main()
{
    unsigned int x, res1 = 0, res2 = 0, res3 = 0;

    // INPUT: x must be the input value, do not overwrite it
    printf("Enter a positive integer: ");
    scanf("%u", &x);
    // calculate here

    unsigned int temp = x; // variabile temporanea assegnata = x, valore di input
    do
    { // numero di 0
        if (temp % 10 == 0)
            res3++; // conto se ce uno 0
        temp /= 10; // divido temp per 10

        res2++; // numero di cifre
    } while (temp > 0); // ciclo fino a quando temp > 0

    for (temp = x; temp > 0; temp /= 10)
    { // ripristino il valore di temp, faccio ciclare fino a temp > 0, in fine ad ogni iterazione divido per 10
        res1 = res1 * 10 + temp % 10;
    }

    res2 = (int)pow(10, res2) - x; // calcolo del complemento a 10

    // do NOT add code after this point
    // OUTPUT
    printf("Actual result:\n");
    printf("%u %u %u\n", res1, res2, res3);

    // DON'T REMOVE from submittion
#ifdef EVAL
    eval(x, res1, res2, res3);
#endif
    return;
}
