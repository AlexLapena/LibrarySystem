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

struct dataHeader * buildHeader() 
{
    struct dataHeader *head = (struct dataHeader *) malloc(sizeof(struct dataHeader));

    if (head != NULL) {
        head->name = NULL;
        head->length = 0;
        head->next = NULL;
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
    return(header->length);
}

void addString(struct dataHeader *header, char *str)
{
    struct dataString *dS = (struct dataString *) malloc(sizeof(struct dataString));
    struct dataString *current = header->next;

    dS->string = malloc(sizeof(char) * strlen(str));
    strcpy(dS->string, str);

    // If first string
    if (header->next == NULL) {
        header->next = dS;
        return;
    }
        
    // If not first string
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = dS;
    // FixMe
    dS->next = NULL;
}

void printString(struct dataHeader *header)
{
    struct dataString *dS = header->next;

    while (dS != NULL) {
        printf("%s\n", dS->string);
    }
}

void processStrings(struct dataHeader *header)
{

}

void freeStructure(struct dataHeader *header)
{
    // Test & fix me
    struct dataString * current = header->next;
    struct dataString * next;

    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    free(header);
    header = NULL;
}

void writeStrings(char *filename, struct dataHeader *header)
{

}

struct dataHeader *readStrings(char *filename)
{

}