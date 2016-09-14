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
    struct dataHeader *read;
    struct dataString *dS;
    char *nameReturn;

    dH = buildHeader();
    setName(dH, "This is the Name");
    nameReturn = getName(dH);

    printf("%s\n\n", nameReturn);

    addString(dH, "string");
    addString(dH, "another");
    addString(dH, "Test");

    printString(dH);

    printf("\n");
    addString(dH, "HELLO it is me");
    printString(dH);

    freeStructure(dH);

    printf("\nprocess string\n");
    dH = buildHeader();
    setName(dH, "name");
    nameReturn = getName(dH);
    addString(dH, "test\nend");
    processStrings(dH);
    freeStructure(dH);

    printf("\nfile io\n");
    dH = buildHeader();
    setName(dH, "name");
    addString(dH, "file test");
    addString(dH, "test 2.0");
    writeStrings("test.bin", dH);
    read = readStrings("test.bin");
    printString(read);


    freeStructure(dH);
    freeStructure(read);

    return(0); 
} 