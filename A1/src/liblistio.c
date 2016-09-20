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
    header->name = (char *) malloc(sizeof(char) * strlen(name));
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

    dS->string = (char *) malloc(sizeof(char) * strlen(str));
    strcpy(dS->string, str);

    // First string
    if (header->next == NULL) {
        header->next = dS;
        dS->next = NULL;
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

    printf("%s\n", getName(header));

    while (dS != NULL) {
        printf("%s\n", dS->string);
        dS = dS->next;
    }
}

void processStrings(struct dataHeader *header)
{
    struct dataString *dS = header->next;
    char * newString;
    int i, length;

    while (dS != NULL) {
        length = strlen(dS->string);
        for (i = 0; i < length; i++) {
            // Removes extra spaces and tabs
            if ((dS->string[i] == ' ' && dS->string[i+1] == ' ') || (dS->string[i] == '\t'
                    && dS->string[i+1] == '\t')) {
                newString = spaceAdjust(dS->string, i);
                dS->string = (char *) malloc(sizeof(char) * strlen(newString));
                strcpy(dS->string, newString);
                length = strlen(dS->string);
                i = 0;
            }
            // Removes extra newline and carriage returns. Replaces with HTML tags
            else if (dS->string[i] == '\n' || dS->string[i] == '\r') {
                newString = newLineAdjust(dS->string, i);
                dS->string = (char *) malloc(sizeof(char) * strlen(newString));
                strcpy(dS->string, newString);
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
            continue;
        }
        else {
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

    // <BR> tag
    if (string[index+1] != '\n' && string[index+1] != '\r') {

        newString = (char *) malloc(sizeof(char) * strlen(string) + 3);

        for (i = 0, j = 0; i < length; i++) {
            if (i == index) {
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

    // <P> tag
    else if (string[index+1] == '\n' || string[index+1] == '\r') {
        // If multiple New Lines or Carriage returns
        if (string[index+2] == '\n' || string[index+2] == '\r') {
            newString = (char *) malloc(sizeof(char) * strlen(string) - 1);

            for (i = 0, j = 0; i < length; i++) {
                if (i == index) {
                    continue;
                }
                else {
                    newString[j] = string[i];
                    j++;
                }
            }
        }
        // Replace with HTML tag
        else {
            newString = (char *) malloc(sizeof(char) * strlen(string) + 2);

            for (i = 0, j = 0; i < length; i++) {
                if (i == index) {
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

    printf(">%s\n", newString);

    return (newString);
}

void freeStructure(struct dataHeader *header)
{
    /* Change to free from back!!*/

    struct dataString * current = header->next;
    struct dataString * next;

    while(current != NULL){
        next = current->next;
        free(current->string);
        free(current);
        current = next;
    }
    free(header->name);
    header->length = 0;
    free(header);
    header = NULL;
}

void writeStrings(char *filename, struct dataHeader *header)
{
    struct dataString * dS = header->next;
    FILE *fp;
    int nameLength, strLength, totalLength;

    // Calculate the length
    while (dS != NULL) {
        totalLength = (strlen(dS->string) + 1) + totalLength;
        dS = dS->next;
    }
    header->length = totalLength;

    fp = fopen(filename, "wb");

    nameLength = strlen(header->name) + 1;
    fwrite(&nameLength, sizeof(int), 1, fp);
    fwrite(header->name, sizeof(char), nameLength, fp);
    fwrite(&header->length, sizeof(int), 1, fp);
    printf("%d\n%s\n%d\n", nameLength, header->name, header->length);
    dS = header->next;

    while (dS != NULL) {
        strLength = strlen(dS->string) + 1;
        fwrite(&strLength, sizeof(int), 1, fp);
        fwrite(dS->string, sizeof(char), strLength, fp);
        printf("%d\n%s\n", strLength, dS->string);
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

    fread(&tempBuff, sizeof(int), 1, fp);
    buffer = malloc(sizeof(char) * tempBuff);
    fread(buffer, sizeof(char), tempBuff, fp);
    setName(header, buffer);
    fread(&header->length, sizeof(int), 1, fp);

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

    return(header);
}