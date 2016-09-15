> Assignment 1 - Develop a String Storage and Processing Library
> -------------------------------------------------------------
> Due date: Friday, September 23, 2016 by midnight
> 
> Build a system which stores strings in a linked structure. Write the
> function(s) necessary to process the string to remove redundant whitespace
> characters and format it using HTML tags. The strings can be stored
> and retrieved from binary files. 
> 
> 
> 1. String Storage and Manipulation Functions
> ---------------------------------------------
> 
> Structures
> ----------
> Your program will manipulate the following structures to store and process
> text strings. There will be one dataHeader struct which stores information
> about the strings. There can be one or more dataString structs which store
> the actual data. The only time that a dataHeader structure does not
> contain anything (the pointers are set equal to NUL and the length is zero)
> is when a no dataString structs have been linked to it.
> 
> struct dataHeader {
>    char *name;
>    int length;
>    struct dataString *next;
> };
> 
> *name is the name of the data stored in the strings. For instance if it
>    stores a book then the name of the book would be here.
> 
> length is the total length of all strings stored in the dataString structures
>    including the end of line markers for each string.
> 
> *next is the pointer to the first data string. If next equals NULL then
>    there are no more structures in the list. In this case it means there is no
>    data in the list.
> 
> 
> struct dataString {
>    char *string;
>    struct dataString *next;
> };
> 
> *string is the place where the data is stored for this struct.
> 
> *next points to the next data string. If next equals NULL then there are no
>   more structures after this.
> 
> 
> The list created with these structures would look something like this:
> 
> dataHeader 
>    name = "A Tail of Two Cities"
>    length = 54
>    next
>      |
>      |
>      V
> dataString 
>    string = "It was the best of times."
>    next
>      |
>      |
>      V
> dataString
>    string = "It was the blurst of times."
>    next = NULL
> 
> Notice the last next is equal to NULL because there are no more elements
> in the list. The length of the strings includes the end of line markers
> for the strings.
> 
> 
> 
> Functions
> ---------
> 
> struct dataHeader *buildHeader()
> 
> Returns a pointer to a struct of type dataHeader. It must dynamically allocate
> the structure and set the initial values of the variables.
> 
> 
> void setName(struct dataHeader *header, char *name)
> 
> Allocates and sets the name string in a dataHeader structure.
> 
> 
> char * getName(struct dataHeader *header)
> 
> Returns a pointer to the name string in the dataHeader structure.
> 
> 
> int getLength(struct dataHeader *header) 
> 
> Returns the integer value stored in the length variable in the dataHeader
> structure.
> 
> 
> void addString(struct dataHeader *header, char *str)
> 
> You must add a new dataString to the linked structure every time addString()
> is called. The new string must be stored in the string pointer within the
> dataString struct.
> 
> The *str character string contains the string to store in the dataString
> struct.
> 
> The first time this function is called with a new dataHeader structure
> (when the first *next pointer is equal to NULL) you can add the dataString
> struct directly to the next pointer in the header. After the first call to
> the function you must always traverse the linked list of dataString structures
> until you reach the end (when the next pointer is equal to NULL) and then you
> can allocate a new dataString structure and copy the string into that new
> structure.
> 
> Addstring() can be called any number of times. Each time it adds a new
> struct in the list. Make sure the *next pointer at the tail of the list
> is always set to NULL.
> 
> Strings are stored in the order which they are added to the list. The first
> string should be stored in the first structure linked to the dataHeader.
> Each later string is stored in a dataString structure which is added to
> the end of the list.
> 
> 
> void printString(struct dataHeader *header)
> 
> This function prints out all of the strings stored in the list.
> Start with the first string linked to the dataHeader and then traversing
> the list and printing out the string in each dataString structure.
> 
> This is mostly useful for debugging your list.
> 
> 
> 
> void processStrings(struct dataHeader *header)
> 
> This function modifies the characters space, tab, newline, carriage
> return contained within the strings. You should probably look at the
> ASCII tables to learn how to identify these characters.
> 
> Multiple spaces are reduced to a single space and the string is shortened
> by the number of spaces removed.
> 
> Multiple tabs are replaced with a single tab and the string is shortened
> by the number of tabs removed.
> 
> A single newline character or a single carriage return is replaced with the
> string <BR>.
> 
> Two or more newline characters are replaced with the string <P>.
> Two or more carriage return characters are replaced with the string <P>.
> Any combination of newlines and carriage returns is replaced
> by the string  <P>. Multiple carriage returns and newlines are replaced
> by a single <P>. 
> 
> <BR> is HTML line break tag. It means start a new line. <P> is the
> HTML new paragraph tag which starts a new paragraph.
> 
> If characters are removed from the strings then the overall length of
> the strings stored in the header should be updated to reflect this change.
> If characters are added to the strings then the overall length should
> be increased. Don't forget that the string cannot be made longer without
> being allocated to a larger size.
> 
> This function can be called at any time and can be called multiple times
> with the same list. Calling the function multiple times with the same
> list should not damage the data in the strings.
> 
> 
> 
> void freeStructure(struct dataHeader *header)
> 
> Free() all of the dataString structures and the dataHeader structure.
> Be sure to free() the dataString structures from the tail back to the
> head. Free the dataHeader structure last. You will need to free
> the character strings in each structure before the structure is freed.
> 
> 
> 2. File I/O
> -----------
> These functions are used to store and retrieve all of the contents
> of the linked structures to and from a binary disk file. 
> 
> 
> void writeStrings(char *filename, struct dataHeader * header)
> 
> Writes all of the contents of the dataHeader and linked structure to a
> binary file. Write the contents of the header first and then the contents
> of each dataString after. Do not store the pointers to the structures
> in the file. You will need to disassemble the structures and store
> the contents of each structure separately. Store the character strings
> and the length integer from the dataHeader. You will also need to calculate
> and store the length of each character string.
> 
> The format for the file is:
> -length of the *name string from the dataHeader struct (an int)
> -contents of the *name string from the dataHeader struct (a char string)
> -contents of the length variable from the dataHeader (an int)
> -length of the string in the first dataString struct (an int)
> -contents of the string in the first dataString struct (a char string)
> -length of the string in the second dataString struct (an int)
> -contents of the string in the second dataString struct (a char string)
> 
> The last two lines are repeated for each additional dataString struct.
> 
> Don't confuse the length variable in the dataHeader structure and the
> length of the strings in both structures. The variable in the dataHeader
> structure is simply written to disk. The lengths of the strings are
> calculated by you for each of the character strings.
> 
> Use the fwrite() function to write the integers and strings to the
> disk. Do not use any other functions to write to the disk file.
> Write all of the elements as either integers or characters.
> 
> Open the file at the start of the function and close the file at the
> end of the function. The name of the file which will be created is
> stored in the string *filename which is passed to the function.
> 
> From the above example the file would contain the following:
> 21
> A Tail of Two Cities'\0'
> 54
> 26
> It was the best of times.'\0'
> 28
> It was the blurst of times.'\0'
> 
> Where \0 represents to end of line character. This is a single character
> and counts as only one char in the string. Note that writing each
> value on a separate line in the above example is not how it would
> appear in the binary file. This is done to make it easier to read.
> In the file there would be no newline after each value, everything
> would appear as one long string, and the integer values would not appear as
> text but as binary numbers. You wont be able to read the binary files
> using a text editor. If you want to look into a binary file try using
> the Linux od command (e.g. something like od -c <filename> will show the
> contents of the file).
> 
> 
> struct dataHeader *readStrings(char *filename)
> 
> This function reads the linked structure from a file created using the 
> writeStrings() function and rebuilds the linked structure that is stored
> in the file. 
> 
> A pointer to the dataHeader structure is returned.
> 
> Use the fread() function to read the file. Do not use any other functions
> to read the file.
> 
> Open the file at the start of the function and close the file at the
> end of the function. The name of the file which will be created is
> stored in the string *filename which is passed to the function.
> 
> 
> 
> 3. Building a Library
> ---------------------
> 
> Include a makefile that creates a static library named liblistio.a from your
> code. It should include all of the functions from Parts 1 and 2 above.
> Use the ar command to create the library.
> 
> If you do not complete all of the functions in Parts 1 and 2 then it
> is very important that you include the empty functions. If you do not then
> your library will not compile and it will receive a low grade.
> 
> For instance, if you do not complete the printString() function then
> you should include the following in your program.
> 
> 	printString(struct dataHeader *header) {
> 	}
> This empty function will allow your program to compile and be tested.
> If your don't work perfectly then include your code in the function.
> Only include empty functions if you have no working at all for the function.
> 
> You should not include a main() in your library code. If you do then it
> will not compile with the testing code and your assignment cannot be
> marked.
> 
> 
> NOTES
> -----
> Don't worry about unspecified return types for this assignment. If a function
> has a void return type then you don't need to include a return value.
> 
> Do not try to port your code from a different operating system to the
> Linux distribution at the last minute. It can take a considerable amount
> of time to make a complicated program compile on a new platform. 
> 
> 
> Handin Notes
> ------------
> 
> Submit the assignment using the dropbox for Assignment 1 in Courselink.
> 
> Include a readme.txt which contains your name, student number, and a short
> description of any parts of the program which do not function correctly.
> If there are some circumstances where functions don't always work correctly
> or if they don't work at all then include this information in the readme.txt.
> This should be a plain text file and not a .doc, .docx, or .pdf file.
> 
> Your code must compile and run on the the Linux distribution used for
> the course.  If it does not then it will receive a grade of zero.
> 
> Submit your source files necessary to compile your code, a makefile that
> will compile the code, and any .c and .h  file necessary to build the project.
> The assignment will be compiled following these steps by:
>         -unpacking your submission (tar or zip)
>         -typing make
>         -linking your library to a sample main program to test it
> Any executables in the directory will be removed before make is run.
> Do not submit any compiled code.
 