/*
 * Alexander Lapena 
 * 0844071
 * CIS* 2750 - A1
 *
 * liblistio.c
 * 
 * 12 September 2016
 */

#include "listio.h"

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

    // First string 
    if (header->next == NULL) {
        header->next = dS;
        return;
    }
        
    // If not first string
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = dS;
    dS->next = NULL;
}

void printString(struct dataHeader *header)
{
    struct dataString *dS = header->next;

    printf("%s\n", header->name);

    while (dS != NULL) {
        printf("%s\n", dS->string);
        dS = dS->next;
    }
}

void processStrings(struct dataHeader *header)
{
    /* FIX ME */
    struct dataString *dS = header->next;
    int length = strlen(dS->string);
    int i;

    printf("%s\n",dS->string);
    for (i = 0; i <= length; i++) {
        if ((dS->string[i-1] == dS->string[i]) && (dS->string[i] == (char)32 || 
                dS->string[i] == '\n')) {
            
            printf("got here %d\n", i);
        }
    }
}

void freeStructure(struct dataHeader *header)
{
    struct dataString * current = header->next;
    struct dataString * next;

    while(current != NULL){
        next = current->next;
        free(current->string);
        free(current);
        current = next;
    }
    free(header->name);
    free(header);
    header = NULL;
}

void writeStrings(char *filename, struct dataHeader *header)
{
    // Test me
    struct dataString * dS = header->next;
    FILE *fp;
    int nameLength, strLength;

    fp = fopen(filename, "wb");

    nameLength = strlen(header->name);
    fwrite(&nameLength, 1, sizeof(int), fp);
    fwrite(header->name, 1, sizeof(header->name), fp);
    fwrite(&header->length, 1, sizeof(int), fp);

    while (dS != NULL) {
        strLength = strlen(dS->string);
        fwrite(&strLength, 1, sizeof(int), fp);
        fwrite(dS->string, 1, sizeof(dS->string), fp);
        dS = dS->next;
    }
    fclose(fp);
}

struct dataHeader *readStrings(char *filename)
{
    struct dataHeader *header;
    struct
    FILE * fp;

    fp = fopen(filename, "rb");

    fclose(fp);
}