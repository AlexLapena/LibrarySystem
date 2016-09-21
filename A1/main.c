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
    printf(" - Header Built\n");
    setName(dH, "Header Name");
    printf(" - Name Set\n");
    addString(dH, "string\n\r\r\r\nhi  yo\negg");
    addString(dH, "another fd");
    addString(dH, "hey hi  what\n\n");
    addString(dH, "This is a story");
    addString(dH, "Loooooooooonnnggggg  String\t\twith tab");
    addString(dH, "Looooong string\t    with one tab and spaces");
    addString(dH, "Looooong string\twith one tab and spaces");
    addString(dH, "More\n Test    Strings hello :D:D:D:D");
    addString(dH, "tab\t\ttest");
    addString(dH, "\r\r");
    printf(" - Strings added\n");
    printString(dH);
    printf(" - Strings Processed\n");
    processStrings(dH);
    writeStrings("test.bin", dH);
    printf(" - Strings written\n");
    freeStructure(dH);
    printf(" - Structure freed\n");
    read = readStrings("test.bin");
    printf("\n** String reading **\n\n");
    printString(read);
    freeStructure(read);

    return(0); 
} 