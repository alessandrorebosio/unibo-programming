#include "base_conversion.h"
#include <stdio.h>

void base_conversion_rc(unsigned int n, unsigned int b)
{
    if (n == 0)
        return;

    base_conversion_rc(n / b, b);

    if (n % b < 10)
        printf("%d", n % b);
    else
        printf("%c", 'A' + (n % b) - 10);
}

void base_conversion_it(unsigned int n, unsigned int b)
{
    unsigned int potenza = 1;

    while (n / potenza >= b)
        potenza *= b;

    while (potenza > 0)
    {
        if (n / potenza < 10)
            printf("%c", n / potenza + '0');
        else
            printf("%c", 'A' + n / potenza - 10);

        n %= potenza;
        potenza /= b;
    }
}
