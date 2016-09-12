/*
 * Alexander Lapena 
 * 0844071
 * CIS* 2750 - A1
 *
 * functions.c
 * 
 * 12 September 2016
 */

#include "functions.h"

struct dataHeader *buildHeader() 
{
    struct dataHeader *head = (struct dataHeader *) malloc(sizeof(struct dataHeader));
    struct dataString *dS = (struct dataString *) malloc(sizeof(struct dataString));

    if (head != NULL) {
        head->name = NULL;
        head->length = 0;
        dS->next = NULL;
    }

    return(head);
}

void setName(struct dataHeader *header, char *name)
{
    header->name = malloc(sizeof(char) * strlen(name));
    strcpy(header->name, name);
}

char * getName(struct dataHeader *header)
{
    return(header->name);
}

int getLength(struct dataHeader *header)
{

}

void addString(struct dataHeader *header, char *str)
{

}

void printString(struct dataHeader *header)
{

}

void processStrings(struct dataHeader *header)
{

}

void freeStructure(struct dataHeader *header)
{

}

void writeStrings(char *filename, struct dataHeader *header)
{

}

struct dataHeader *readStrings(char *filename)
{

}