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
   // printf(" - Header Built\n");
    setName(dH, "Name of Title");
   // printf(" - Name Set\n");
    addString(dH, "string\n\ntester");
    addString(dH, "another fd");
    addString(dH, "hey hi");
    addString(dH, "This is a story");
   // printf(" - Strings added\n");
    printString(dH);

    printf(" - Strings Processed\n");
    processStrings(dH);

    /*printf("\n** Expected **\n\n");
    writeStrings("test.bin", dH);
    printf("\n - Strings written\n");
    freeStructure(dH);
    printf(" - Structure freed\n");
    read = readStrings("test.bin");
    printf("\n** String reading **\n\n");
    printString(read);*/
    freeStructure(read);

    return(0); 
} 