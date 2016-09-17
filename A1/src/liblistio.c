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
    int length, i, j, k;
    char * newString;

    while (dS != NULL) {
        length = strlen(dS->string);
        printf("STRING: %d %s\n", length, dS->string);

        // Traverse through each character string
        for (i = 0; i < length; i++) {

            // Processing carriage returns and new lines. Converts to HTML tags
            if (dS->string[i] == '\r' || dS->string[i] == '\n') {

                /*
                 * <p> tag -> multiple tabs/ carraige returns
                 */
                if (dS->string[i-1] == '\r' || dS->string[i-1] == '\n' || dS->string[i+1] == '\n'
                        || dS->string[i+1] == '\n') {
                    printf("here 1\n");
                    // If there are 2 left, remove last one for <p> tag
                    if (dS->string[i+1] != '\r' && dS->string[i+1] != '\n') { 
                        printf("here 2\n");
                        for (j = 0, k = 0; j < length; j++) {
                            if (j == i) {
                                newString[k] = '<';
                                printf("%c", newString[k]);
                                newString[k+1] = 'P';
                                printf("%c", newString[k+1]);
                                newString[k+2] = '>';
                                printf("%c", newString[k+2]);
                                k = k + 3;
                            }
                            else {
                                newString[k] = dS->string[j];
                                printf("%c", newString[k]);
                                k++;
                            }                         
                        }
                        printf("\n*: %s\n", newString);
                        dS->string = realloc(dS->string, sizeof(char) * strlen(newString));
                        printf("segfault\n");
                        strcpy(dS->string, newString);
                    }

                    // Removes multiple newlines and carriage returns
                    else {
                        printf("here 3\n");
                        printf("%s\n", dS->string);
                        for (j = 0, k = 0; j < length; j++) {
                            if (j == i) {
                                continue;
                            }
                            else {
                                newString[k] = dS->string[j];
                                k++;
                            }                        
                        }
                        printf("\n*: %s\n", newString);
                        dS->string = realloc(dS->string, sizeof(char) * strlen(newString));
                        printf("segfault\n");
                        strcpy(dS->string, newString);
                        processStrings(header);
                    }
                }

                /*
                 * <br> tag -> 1 tab/ carraige return
                 */
                else if ((dS->string[i+1] != '\r' && dS->string[i+1] != '\n') && (dS->string[i-1] != '\n'
                        && dS->string[i-1] != '\r')) {
                    printf("here 4\n");
                    // malloc more space for the html tag
                    for (j = 0, k = 0; j < length; j++) {
                        if (j == i) {
                            newString[k] = '<';
                            printf("%c", newString[k]);
                            newString[k+1] = 'B';
                            printf("%c", newString[k+1]);
                            newString[k+2] = 'R';
                            printf("%c", newString[k+2]);
                            newString[k+3] = '>';
                            printf("%c", newString[k+3]);
                            k = k + 4;
                        }
                        else {
                            newString[k] = dS->string[j];
                            printf("%c", newString[k]);
                            k++;
                        } 
                    }
                    printf("\n*: %s\n", newString);
                    dS->string = realloc(dS->string, sizeof(char) * strlen(newString));
                    printf("segfault\n");
                    strcpy(dS->string, newString);
                }
            }

            // Processes tabs. 
            else if (dS->string[i] == '\t') {
                if (dS->string[i+1] == '\t' || dS->string[i-1] == '\t') {
                    // remove tab
                    for (j = 0, k = 0; j < length; j++) {
                        if (j == i) {
                            continue;
                        }
                        else {
                            newString[k] = dS->string[j];
                            k++;
                        }
                    }
                    printf("\n");
                    dS->string = realloc(dS->string, sizeof(char) * strlen(newString));
                    printf("segfault\n");
                    strcpy(dS->string, newString);
                    processStrings(header);
                }
            }

            // Processes spaces
            else if (dS->string[i] == ' ') {
                if (dS->string[i+1] == ' ' || dS->string[i-1] == ' ') {
                    // remove space
                    for (j = 0, k = 0; j < length; j++) {
                        if (j == i) {
                            continue;
                        }
                        else {
                            newString[k] = dS->string[j];
                            k++;
                        }
                    }
                    printf("\n");
                    dS->string = realloc(dS->string, sizeof(char) * strlen(newString));
                    printf("segfault\n");
                    strcpy(dS->string, newString);
                    processStrings(header);
                }
            }
        }
        dS = dS->next;
    }
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
    free(header);
    header = NULL;
}

void writeStrings(char *filename, struct dataHeader *header)
{
    // fix length of string with null terminator *** strcat() \0
    struct dataString * dS = header->next;
    FILE *fp;
    int nameLength, strLength, totalLength;

    // Calculate the length
    while (dS != NULL) {
        totalLength = strlen(dS->string) + totalLength;
        dS = dS->next;
    }
    header->length = totalLength;

    fp = fopen(filename, "wb");

    nameLength = strlen(header->name);
    fwrite(&nameLength, sizeof(int), 1, fp);
    fwrite(header->name, sizeof(char), nameLength, fp);
    fwrite(&header->length, sizeof(int), 1, fp);
    printf("%d\n%s\n%d\n", nameLength, header->name, header->length);
    dS = header->next;

    while (dS != NULL) {
        strLength = strlen(dS->string);
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