#include <math.h>
#include <limits.h>
#include "../inc/prime.h"

unsigned short int is_prime(unsigned short int n)
{
    int i;
    for (i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return 0;
    return 1;
}

unsigned short int nth_prime(unsigned short int n)
{
    int i = 0, k = 2;
    while (i <= n)
    {
        if (is_prime(k))
        {
            if (i == n && k <= USHRT_MAX)
                return k;
            ++i;
        }
        ++k;
    }
    return 0;
}

unsigned short int succ_prime(int reset)
{
    static int n = 1;
    if (reset != 0 || n >= USHRT_MAX)
        n = 1;

    while (n < USHRT_MAX)
        if (is_prime(++n))
            return n;

    return 0;
}

unsigned short int co_prime(unsigned short int m, unsigned short int n)
{
    int min = m > n ? n : m, i = 0;

    for (i = 2; i <= min; i++)
    {
        if (n % i == 0 && m % i == 0)
            return 0;
    }

    return 1;
}
