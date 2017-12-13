//
// Created by Qut on 29/10/2017.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../h/struct.h"
#include "../h/some_funct.h"
#include "../h/parser_SQL.h"
#include "../h/struct.h"

/* ----- GLOBALS ----- */
extern int FILE_LINE_COUNTER;



//fonction de base menu, init (procÃ©dure initialisation), ouverture fichiers


void requestSQL() {
    int counter;
    int len;
    counter = 1;
    char word[255];
    printf("\n%d : ", counter);
    while (scanf("%[^\n]%*c", word) == 1) {
        if (strstr(word, ";") != NULL) {
            len = strlen(word);
            word[len - 1] = '\0';
            parserSQL(word);
            break;
        }
        //traiter le multi-ligne
        printf("%d : ", ++counter);
    }

}


void menu() {
    //  verifFirstInit();
    //  showInfo();
    printf("WELCOME\ntype exit or blanck query for exit");

    while (1) {
        char requestsql[1024] = "";
        char word[255] = "";
        int counter;
        counter = 1;
        printf("\n%d>", counter);
        //si ; en fin
        while (scanf("%[^\n]%*c", word) == 1) {
            if (!strcmp(&word[strlen(word) - 1], ";")) {
                strcat(requestsql, word);
                parserSQL(requestsql);
                break;
            } else if (strcmp(&word[strlen(word) - 1], " ")) {
                strcat(word, " ");
            }
            strcat(requestsql, word);
            printf("%d>", ++counter);
        }
        if (strlen(word) == 0) {
            query_exit("");
            break;
        }
        if (!strcmp(upWord(word), "EXIT;")) {
            break;
        }

    }
}


char *upWord(char *word) {
    size_t len;
    int boucle;
    len = strlen(word);
    char *upword = malloc(sizeof(char) * (len + 1));
    for (boucle = 0; boucle < len; boucle++) {
        upword[boucle] = (char) ((word[boucle] >= 'a' && word[boucle] <= 'z') ? word[boucle] - 32 : word[boucle]);
    }
    upword[len] = '\0';
    return upword;
}




/**
 * @name fSize
 *
 * @brief Returns the number of characters present in the given file. In another meaning, the size of the file.
 *
 * @param FILE* file : file pointer of the concerned file.
 *
 * @remarks Reset the cursor at its initial position at the end of the process.
 */
int fSize(FILE *file) {
	int value = 0;
	int initialCursor;

	if(file != NULL) {
		initialCursor = ftell(file);            // Save the current cursor position.
		fseek(file, 0, SEEK_END);               // Shifting to the end of the file.
		value = ftell(file);                    // Recover the cursor position (i.e the number of characters)
		fseek(file, initialCursor, SEEK_SET);   // Reset the cursor to its original position.
	}
	return value;	// Return result.
}




/**
 * @name freadL
 *
 * @brief Reads a line from the current cursor position in a file and stores it in the string passed as argument.
 *			`fgets` has as cons to recover the possible line break lying at the end of the line read.
 *			`freadL` (the function below) has as only purpose to solve that behavior.
 *
 * @param char* destination : string in which one the result will be stored
 * @param unsigned int sizeMax : characters number to read (large number like 255 recommended)
 * @param FILE* sourceFile : file pointer of the concerned file.
 *
 * @return (on success) 1
 * @return (on failure) 0
 *
 * @remarks Cursor position not handled.
 */
int freadL(char* destination, unsigned int sizeMax, FILE* sourceFile) {
    int strLength;
    char result[MAX];

    if(sourceFile != NULL) {
        if(fgets(result, sizeMax, sourceFile) != NULL) {    // Read a line in the file
            FILE_LINE_COUNTER++;
            strLength = strlen(result);
            if(result[strLength-1] == '\n') {	// If the last character is a line break
                result[strLength-1] = '\0';		// Then it is replace by '\0' (known as end of string character)
                strcpy(destination, result);	// Copy the result in the passed argument
            }
            return 1;
        }
    }
    return 0;
}




/**
 * @name countTab
 *
 * @brief Counts the number of tabulation (one tabulation is 4 space characters)
 *
 * @param char* str : concerned string
 *
 * @return (on success) Counted tabulations.
 * @return (on failure) -1;
 */
int countTab(char* str) {
    int i = -1;
    int strLength;

    if(str != NULL) {
        strLength = strlen(str);
        if(strLength > 0) {
            for(i=0 ; i < strLength && str[i] == ' '; i++);
            i /= 4;
        }
    }
    return i;
}

/**
 * @brief Shift the file cursor at the start of the wanted line.
 *
 * @param int line : number of the line to shift to.
 * @param FILE* sourceFile : file pointer of the concerned file.
 *
 * @return (on success) 1
 * @return (on failure) 0
 *
 * @remarks If the end of line is exceed, i.e if the given number is superior of the line in the file,
 *			then put the cursor at the end of the file.
 */
int fGoToLine(int line, FILE* sourceFile) {
    int i;
    int fileSize;
    char temp[MAX];

    fileSize = fSize(sourceFile);
    if(sourceFile != NULL) {
        fseek(sourceFile, 0, SEEK_SET);					// Shifting to the start of the file.
        FILE_LINE_COUNTER = 0;
        for(i=0 ; i < line-1 ; i++) {					// Loop up to the wanted line.
            if(ftell(sourceFile) > fileSize) {			// If the file limit is exceed.
                return 0;
            } else if(fgets(temp, MAX, sourceFile)) {	// Next line.
                FILE_LINE_COUNTER++;
            } else {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}




/**
 * @name error
 *
 * @brief Error displaying handler. Write in `stderr` (output dedicated to the errors).
 *
 * @param char* message : error message.
 *
 * @return void
 *
 * @remarks Can be modify to have an index in which the function picks up the wanted error specify by in ID passed by argument.
 */
void error(const char* message) {
    if(message != NULL)
        fprintf(stderr, message);
}

char *cleanQuery(char *word) {
    size_t len;
    int boucle;
    int showchar;
    showchar = 1;
    size_t cleanspace;
    len = strlen(word);
    cleanspace = len;
    if (!strncmp(&word[0], " ", 1)) {
        cleanspace = len - 1;
        showchar = 0;
    }
    for (boucle = 0; boucle < len - 1; boucle++) {
        if (!strncmp(&word[boucle], " ", 1) && !strncmp(&word[boucle + 1], " ", 1)) {
            cleanspace--;
        }
    }
    char *cleanquery = malloc(sizeof(char) * (cleanspace + 1));
    cleanquery[cleanspace - 1] = ';';
    cleanquery[cleanspace] = '\0';
    cleanspace = 0;
    for (boucle = 0; boucle < len - 1; boucle++) {
        if (!strncmp(&word[boucle], " ", 1) && !strncmp(&word[boucle + 1], " ", 1)) {
            continue;
        } else {
            if (!showchar) {
                showchar = 1;
            } else {
                cleanquery[cleanspace] = word[boucle];
                cleanspace++;
            }
        }
    }
    return cleanquery;
}

/**
 * @name strALen
 *
 * @brief Takes a 2 dimensional array of char as parameter, i.e an array of strings, returns the number of strings in it.
 *
 * @param char *array : pointer of the two dimensional array.
 *
 * @remarks Called as a single pointer because the function does not need to access the inner pointer.
 */
size_t strALen (char *array) {
    size_t len = 0;

	if(array != NULL)
		while (*array++ != '\0')
			len++;
    return len/sizeof(char*);
}

/**
 * @name strIsIn
 *
 * @brief Checks if a given string is in a list of string
 *
 * @param char* str : string to search for.
 * @param char** strList : list of string to search in.
 *
 * @return (if found) the position of the occurrence in the list.
 * @return (otherwise) -1
 */
int strIsIn(char* str, char strList[][MAX]) {
	int i;
	int listSize;

	listSize = sizeof(strList)/sizeof(*strList);
	printf("Size : %d/%d = %d\n", sizeof(strList), sizeof(*strList), listSize);
	for(i=0 ; i < listSize ; i++) {
		printf("In loop : %d\n", i);
		if(strcmp(str, strList[i]) == 0) {
			printf("Stop : %s\n", i);
			return i;
		}
		printf("Next.\n");
	}
	return -1;
}

/**
 * @name addColumn
 *
 * @brief Allocates a column to the given array typed as `char**`
 *
 * @param
 *
 *
 *
 */
char** addColumn(char** stringArray, unsigned int currentSize, unsigned int dimToAdd, char value) {
	int i;
	char** temp;

	if ( (temp = malloc(sizeof(char*)*currentSize + dimToAdd)) != NULL ) {
		for(i=0 ; i < currentSize + dimToAdd ; i++) {
			if ( (temp[i] = malloc(sizeof(char)*MAX)) == NULL ) {
				while(i >= 0) {
					free(temp[--i]);
				}
				free(temp);
				return NULL;
			} else if(i < currentSize) {
				temp[i] = stringArray[i];
			}
		}
		free(stringArray);
		stringArray = temp;
	}
	return stringArray;
}
