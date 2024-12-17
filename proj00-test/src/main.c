#include <stdio.h>
#include <stdlib.h>

int main()
{
    /*
        store the first name
        store the last name
        store the student ID number

        print information
    */
    char name[] = "Alessandro";
    char surname[] = "Rebosio";
    int mat = 1130557;

    printf("NAME: %-10s COGNOME: %-10s MATRICOLA: %010d", name, surname, mat);

    return EXIT_SUCCESS;
}