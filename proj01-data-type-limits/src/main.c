#include <stdio.h>
#include <limits.h>
#include <float.h>

/* Used to avoid magic numbers in the code, represents the minimum of unsigned types */
#define UNS_MIN 0

int main()
{
    /*
        Declare each type of variable
        Print the information for each variable type
    */
    char a = 'A';
    signed char b = 'B';
    unsigned char c = 'C';
    short int d = 26621;
    unsigned short int e = 53242;
    int f = -1947483647;
    unsigned int g = 3894967294;
    long int h = -2058594758;
    unsigned long int i = 4117189516;
    float j = 3.141592;
    double k = 1.414213;
    long double l = 2.718281;

    printf("TYPE: %-18s NAME: %s VALUE: %-11c MIN: %-20d MAX: %-20d BYTE: %lu\n", "char", "a", a, CHAR_MIN, CHAR_MAX, sizeof a);
    printf("TYPE: %-18s NAME: %s VALUE: %-11c MIN: %-20d MAX: %-20d BYTE: %lu\n", "signed char", "b", b, SCHAR_MIN, SCHAR_MAX, sizeof b);
    printf("TYPE: %-18s NAME: %s VALUE: %-11c MIN: %-20u MAX: %-20u BYTE: %lu\n", "unsigned char", "c", c, UNS_MIN, UCHAR_MAX, sizeof c);

    printf("TYPE: %-18s NAME: %s VALUE: %-11d MIN: %-20d MAX: %-20d BYTE: %lu\n", "short int", "d", d, SHRT_MIN, SHRT_MAX, sizeof d);
    printf("TYPE: %-18s NAME: %s VALUE: %-11d MIN: %-20u MAX: %-20u BYTE: %lu\n", "unsigned short int", "e", e, UNS_MIN, USHRT_MAX, sizeof e);

    printf("TYPE: %-18s NAME: %s VALUE: %-11d MIN: %-20d MAX: %-20d BYTE: %lu\n", "int", "f", f, INT_MIN, INT_MAX, sizeof f);
    printf("TYPE: %-18s NAME: %s VALUE: %-11u MIN: %-20u MAX: %-20u BYTE: %lu\n", "unsigned int", "g", g, UNS_MIN, UINT_MAX, sizeof g);

    printf("TYPE: %-18s NAME: %s VALUE: %-11ld MIN: %-20ld MAX: %-20ld BYTE: %lu\n", "long int", "h", h, LONG_MIN, LONG_MAX, sizeof h);
    printf("TYPE: %-18s NAME: %s VALUE: %-11ld MIN: %-20u MAX: %-20lu BYTE: %lu\n", "unsigned long int", "i", i, UNS_MIN, ULONG_MAX, sizeof i);

    printf("TYPE: %-18s NAME: %s VALUE: %-11f MIN: %-20e MAX: %-20e BYTE: %lu\n", "float", "j", j, FLT_MIN, FLT_MAX, sizeof j);
    printf("TYPE: %-18s NAME: %s VALUE: %-11f MIN: %-20e MAX: %-20e BYTE: %lu\n", "double", "k", k, DBL_MIN, DBL_MIN, sizeof k);
    printf("TYPE: %-18s NAME: %s VALUE: %-11Lf MIN: %-20Le MAX: %-20Le BYTE: %lu\n", "long double", "l", l, LDBL_MIN, LDBL_MAX, sizeof l);

    return 0;
}
