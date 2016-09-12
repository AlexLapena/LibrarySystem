/*
 * Alexander Lapena 
 * 0844071
 * CIS* 2750 - A1
 *
 * main.c
 * 
 * 12 September 2016
 */

#include "src/functions.h"

int main(int argc, char **argv)
{
    struct dataHeader *dH;
    char *nameReturn;

    dH = buildHeader();
    setName(dH, "Spaghetti Egg");
    nameReturn = getName(dH);

    printf("%s\n", nameReturn);

    return(0); 
} 