/*
 * Alexander Lapena 
 * 0844071
 * CIS* 2750 - A1
 *
 * functions.h
 * 
 * 12 September 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dataHeader {
    char *name;
    int length;
    struct dataString *next;
};

struct dataString {
    char *string;
    struct dataString *next;
};

/*
 * Returns a pointer to a struct of type dataHeader. It must dynamically allocate
 * the structure and set the initial values of the variables.
 */
struct dataHeader * buildHeader();

/*
 * Allocates and sets the name string in a dataHeader structure.
 */
void setName(struct dataHeader *header, char *name);

/*
 * Returns a pointer to the name string in the dataHeader structure.
 */
char * getName(struct dataHeader *header);

/*
 * Returns the integer value stored in the length variable in the dataHeader
 * structure.
 */
int getLength(struct dataHeader *header);

/*
 * Strings are stored in the order which they are added to the list. The first
 * string should be stored in the first structure linked to the dataHeader.
 * Each later string is stored in a dataString structure which is added to
 * the end of the list.
 */
void addString(struct dataHeader *header, char *str);

/*
 * This function prints out all of the strings stored in the list.
 */
void printString(struct dataHeader *header);

/*
 * This function modifies the characters space, tab, newline, carriage
 * return contained within the strings. You should probably look at the
 * ASCII tables to learn how to identify these characters
 */
void processStrings(struct dataHeader *header);

/* 
 * Free() all of the dataString structures and the dataHeader structure.
*/
void freeStructure(struct dataHeader *header);

/*
 * File I/O
 *
 * These functions are used to store and retrieve all of the contents
 * of the linked structures to and from a binary disk file.
 */

/*
 * Writes all of the contents of the dataHeader and linked structure to a
 * binary file.
 */
void writeStrings(char *filename, struct dataHeader *header);

/*
 * This function reads the linked structure from a file created using the 
 * writeStrings() function and rebuilds the linked structure that is stored
 * in the file.
 */
struct dataHeader *readStrings(char *filename);