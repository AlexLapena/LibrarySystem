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

    /* Creates the memory for the header node*/
    if (head != NULL) {
        head->name = NULL;
        head->length = 0;
        head->next = NULL;
    }

    return(head);
}

void setName(struct dataHeader *header, char *name)
{
    if (header == NULL) {
        return;
    }

    header->name = (char *) malloc(sizeof(char) * strlen(name));
    strcpy(header->name, name);
}

char * getName(struct dataHeader *header)
{
    if (header == NULL) {
        return NULL;
    }

    return(header->name);
}

int getLength(struct dataHeader *header)
{
    if (header == NULL) {
        return (0);
    }

    return(header->length);
}

void addString(struct dataHeader *header, char *str)
{
    struct dataString *dS = (struct dataString *) malloc(sizeof(struct dataString));
    struct dataString *current = header->next;

    /* Creates a new node to be placed into the list */
    dS->string = (char *) malloc(sizeof(char) * strlen(str));
    strcpy(dS->string, str);

    if (header == NULL) {
        return;
    }

    /* First string in the list */
    if (header->next == NULL) {
        header->next = dS;
        dS->next = NULL;
        return;
    }
        
    /* Used once the list has been created */
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = dS;
    dS->next = NULL;
}

void printString(struct dataHeader *header)
{
    struct dataString *current = header->next;
  
    if (header == NULL || header->next == NULL) {
        printf("ERROR: NULL DATA ENTERED.\n");
        return;
    }

    printf("%s\n", getName(header));

    while (current != NULL) {
        printf("%s\n", current->string);
        current = current->next;
    }
}

void processStrings(struct dataHeader *header)
{
    struct dataString *dS = header->next;
    char * newString;
    int i, length;

    if (header == NULL || header->next == NULL) {
        return;
    }

    while (dS != NULL) {
        length = strlen(dS->string);
        for (i = 0; i < length; i++) {
            /* Removes extra spaces and tabs */
            if ((dS->string[i] == ' ' && dS->string[i+1] == ' ') || (dS->string[i] == '\t'
                    && dS->string[i+1] == '\t')) {
                newString = spaceAdjust(dS->string, i);
                dS->string = (char *) malloc(sizeof(char) * strlen(newString));
                strcpy(dS->string, newString);
                /* Resets string until fully processed */
                length = strlen(dS->string);
                i = 0;
            }
            /* Removes extra newline and carriage returns. Replaces with HTML tags */
            else if (dS->string[i] == '\n' || dS->string[i] == '\r') {
                newString = newLineAdjust(dS->string, i);
                dS->string = (char *) malloc(sizeof(char) * strlen(newString));
                strcpy(dS->string, newString);
                /* Resets string until fully processed */
                length = strlen(dS->string);
                i = 0;
            }
        }
        dS = dS->next;
    }
}

char * spaceAdjust(char * string, int index)
{
    int i, j, length;
    char * newString = (char *) malloc(sizeof(char) * strlen(string) - 1);

    length = strlen(string);

    for (i = 0, j = 0; i < length; i++) {
        if (i == index) {
            /* Skips of extra tab or space */
            continue;
        }
        else {
            /* Copies string into a new string without extra spaces or tabs */
            newString[j] = string[i];
            j++;
        }
    }

    return (newString);
}

char * newLineAdjust(char * string, int index) 
{
    int i, j, length;
    char * newString;

    length = strlen(string);

    /* For single newlines and carriage returns, replace with the <BR> tag */
    if (string[index+1] != '\n' && string[index+1] != '\r') {

        newString = (char *) malloc(sizeof(char) * strlen(string) + 3);

        for (i = 0, j = 0; i < length; i++) {
            if (i == index) {
                /* Replacing characters */
                newString[j] = '<';
                newString[j+1] = 'B';
                newString[j+2] = 'R';
                newString[j+3] = '>';
                j = j + 4; 
            }
            else {
                newString[j] = string[i];
                j++;
            }
        }
    }

    /* For multiple newlines and carriage returns, replace with the <P> tag */
    else if (string[index+1] == '\n' || string[index+1] == '\r') {
        /* Removes excess newlines or Carriage returns */
        if (string[index+2] == '\n' || string[index+2] == '\r') {
            newString = (char *) malloc(sizeof(char) * strlen(string) - 1);

            for (i = 0, j = 0; i < length; i++) {
                if (i == index) {
                    /* Skips extra newlines and carriage returns */
                    continue;
                }
                else {
                    newString[j] = string[i];
                    j++;
                }
            }
        }
        /* If there are two newlines or carriage returns, replace with <P> tags */
        else {
            newString = (char *) malloc(sizeof(char) * strlen(string) + 2);

            for (i = 0, j = 0; i < length; i++) {
                if (i == index) {
                    /* Replacing characters */
                    newString[j] = '<';
                    newString[j+1] = 'P';
                    newString[j+2] = '>';
                    j = j + 3;
                    i = i + 1; 
                }
                else {
                    newString[j] = string[i];
                    j++;
                }
            }
        }
    }

    return (newString);
}

void freeStructure(struct dataHeader *header)
{
    struct dataString *dsHead = header->next;
    struct dataString *current, *next;

    /* If there is no data, returns from function */
    if (header == NULL || header->next == NULL) {
        return;
    }

    /* Reverses the list to be freed backwards */
    header->next = NULL;
    current = reverseList(dsHead);

    /* Free from tail to head */
    while (current != NULL) {
        next = current->next;
        free(current->string);
        free(current);
        current = next;
    }

    /* Frees header from list */
    free(header->name);
    header->length = 0;
    free(header);
    header = NULL;
}

struct dataString * reverseList(struct dataString *dsHead)
{
    struct dataString *current, *prev, *next;
    current = dsHead;
    prev = NULL;

    /* Reverses the list */
    while(current != NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    dsHead = prev;

    /* Returns reversed list */
    return (dsHead);
}

void writeStrings(char *filename, struct dataHeader *header)
{
    struct dataString * dS = header->next;
    FILE *fp;
    int nameLength, strLength, totalLength;

    if (header == NULL) {
        return;
    }

    /* Calculate the length of all strings */
    while (dS != NULL) {
        totalLength = (strlen(dS->string) + 1) + totalLength;
        dS = dS->next;
    }
    header->length = totalLength;

    fp = fopen(filename, "wb");

    /* Writes the header to the binary file */
    nameLength = strlen(header->name) + 1;
    fwrite(&nameLength, sizeof(int), 1, fp);
    fwrite(header->name, sizeof(char), nameLength, fp);
    fwrite(&header->length, sizeof(int), 1, fp);
    dS = header->next;

    /* Writes the rest of the nodes to the binary file */
    while (dS != NULL) {
        strLength = strlen(dS->string) + 1;
        fwrite(&strLength, sizeof(int), 1, fp);
        fwrite(dS->string, sizeof(char), strLength, fp);
        dS = dS->next;
    }
    fclose(fp);
}

struct dataHeader *readStrings(char *filename)
{   
    struct dataHeader *header = buildHeader();
    struct dataString *dS;
    FILE * fp;
    int tempBuff, skip = 0;
    char * buffer;

    fp = fopen(filename, "rb");

    /* Occupies the header information */
    fread(&tempBuff, sizeof(int), 1, fp);
    buffer = malloc(sizeof(char) * tempBuff);
    fread(buffer, sizeof(char), tempBuff, fp);
    setName(header, buffer);
    fread(&header->length, sizeof(int), 1, fp);

    /* Occupies the dataString information in until EOF */
    while (!feof(fp)) {
        if (skip != 0) {
            buffer = malloc(sizeof(char) * tempBuff);
            fread(buffer, sizeof(char), tempBuff, fp);
            addString(header, buffer);
            skip--;
        }
        else{
            fread(&tempBuff, sizeof(int), 1, fp);
            skip++;
        }
    }

    fclose(fp);

    /* Returns an occupied list */
    return(header);
}