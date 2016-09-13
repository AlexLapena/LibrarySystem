/*
 * Alexander Lapena 
 * 0844071
 * CIS* 2750 - A1
 *
 * main.c
 * 
 * 12 September 2016
 */

#include "src/listio.h"

int main(int argc, char **argv)
{
    struct dataHeader *dH;
    struct dataString *dS;
    char *nameReturn;

    dH = buildHeader();
    setName(dH, "This is the Name");
    nameReturn = getName(dH);

    printf("%s\n", nameReturn);

    addString(dH, "string");
    addString(dH, "another");
    addString(dH, "Test");

    printString(dH);

    printf("\n");
    addString(dH, "HELLO it is me");
    printString(dH);

    freeStructure(dH);

    dH = buildHeader();
    setName(dH, "This is the Name");
    nameReturn = getName(dH);
    addString(dH, "Free");
    printString(dH);

    return(0); 
} 