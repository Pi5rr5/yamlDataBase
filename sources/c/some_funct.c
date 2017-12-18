//
// Created by Qut on 29/10/2017.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../h/globals.h"
#include "../h/struct.h"
#include "../h/some_funct.h"
#include "../h/parserYAML.h"
#include "../h/parser_SQL.h"

/* ----- GLOBALS ----- */
extern int FILE_LINE_COUNTER;



void menu() {
    printf("WELCOME\ntype exit or return for exit");

    while (1) {
        char requestsql[MAX] = "";
        char word[MAX] = "";
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
            queryExit("");
            break;
        }
        if (!strcmp(upWord(word), "EXIT;")) {
            break;
        }

    }
}


/**
 * Desc: up the string
 *
 * Param: Char * word : String to up
 *
 * Return: (char *) upper string
 */

char *upWord(char *word) {
    size_t len;
    int i;
    len = strlen(word);
    char *upword = malloc(sizeof(char) * (len + 1));
    for (i = 0; i < len; i++) {
        upword[i] = (char) ((word[i] >= 'a' && word[i] <= 'z') ? word[i] - 32 : word[i]);
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
 * @name freadLine
 *
 * @brief Reads a line from the current cursor position in a file and stores it in the string passed as argument.
 *			`fgets` has as cons to recover the possible line break lying at the end of the line read.
 *			`freadLine` (the function below) has as only purpose to solve that behavior.
 *
 * @param char* destination : string in which one the result will be stored
 * @param unsigned int sizeMax : characters number to read (large number like 255 recommended)
 * @param FILE* sourceFile : file pointer of the concerned file.
 *
 * @return (on success) 1
 * @return (on failure) 0
 *
 * @remarks Cursor position not handled.
 *
 * @see FILE_LINE_COUNTER
 */
int freadLine(char* destination, unsigned int sizeMax, FILE* sourceFile) {
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
int countTab(char *str) {
    int i = -1;
    int strLength;

    if (str != NULL) {
        strLength = strlen(str);
        if(strLength > 0) {
            for(i=0 ; i < strLength && str[i] == ' ' ; i++);
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
 *
 * @see FILE_LINE_COUNTER
 */
int fGoToLine(int line, FILE* sourceFile) {
    int i;
    int fileSize;
    char temp[MAX];

    if(sourceFile != NULL) {
        fileSize = fSize(sourceFile);
        fseek(sourceFile, 0, SEEK_SET);					// Shifting to the start of the file.
        FILE_LINE_COUNTER = 0;
        for(i=0 ; i < line-1 ; i++) {					// Loop up to the wanted line.
            if(ftell(sourceFile) > fileSize) {			// If the file limit is exceed.
                error("out of file");
                return 0;
            } else if(fgets(temp, MAX, sourceFile) != NULL) {	// Next line.
                FILE_LINE_COUNTER++;
            } else {
                error("couldn't read line");
                return 0;
            }
        }
        return 1;
    } else {
        error("file empty");
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
        fprintf(stderr, "%s\n", message);
}


/**
 * Desc: delete multiple space
 *
 * Param: Char * word : String to clean of multiple space
 *
 * Return: (char *) clean string without multiple space
 */
char *cleanQuery(char *word) {
    size_t len;
    int i;
    int showchar;
    showchar = 1;
    size_t cleanspace;
    len = strlen(word);
    cleanspace = len;
    if (!strncmp(&word[0], " ", 1)) {
        cleanspace = len - 1;
        showchar = 0;
    }
    for (i = 0; i < len - 1; i++) {
        if (!strncmp(&word[i], " ", 1) && !strncmp(&word[i + 1], " ", 1)) {
            cleanspace--;
        }
    }
    char *cleanquery = malloc(sizeof(char) * (cleanspace + 1));
    cleanquery[cleanspace - 1] = ';';
    cleanquery[cleanspace] = '\0';
    cleanspace = 0;
    for (i = 0; i < len - 1; i++) {
        if (!strncmp(&word[i], " ", 1) && !strncmp(&word[i + 1], " ", 1)) {
            continue;
        } else {
            if (!showchar) {
                showchar = 1;
            } else {
                cleanquery[cleanspace] = word[i];
                cleanspace++;
            }
        }
    }
    return cleanquery;
}



/**
 * Desc: check if the string is alphanumeric
 *
 * Param: Char * word : String to check
 *
 * Return: 1 -> Alphanum ; 0 if not
 */
int isAlphaNum(char *word) {
    size_t len;
    int isOk;
    int i;
    isOk = 1;
    len = strlen(word);
    for (i = 0; i < len; i++) {
        if (word[i] < '0'
            || (word[i] > '9' && word[i] < 'A')
            || (word[i] > 'Z' && word[i] < 'a')
            || (word[i] > 'z')) {
            isOk = 0;
            break;
        }
    }
    return isOk;
}

/**
 * Desc: return number of terms split with the delim
 *
 * Param:
 *      Char * countChar : String to split and count
 *      char delim : Char delim
 *
 * Return: number of term (int)
 */
int countArgs(char *countChar, const char *delim) {
    char *countrequest;
    countrequest = malloc(sizeof(char) * (strlen(countChar) + 1));
    strcpy(countrequest, countChar);
    int count;
    count = 0;
    char *token = strtok(countrequest, delim);
    while (token != NULL) {
        count++;
        token = strtok(NULL, delim);
    }
    free(countrequest);
    return count;
}


/**
 * Desc: return the first word of a string
 *
 * Param: Char * word : String to csplit
 *
 * Return: first word
 */
char *splitWord(char *word, const char *delim) {
    int len;
    int count;
    char *firstWord;
    len = strlen(word);
    for (count = 0; count < len; count++) {
        if (word[count] == delim[0]) {
            firstWord = malloc(sizeof(char) * (count + 1));
            strncpy(firstWord, word, count);
            firstWord[count] = '\0';
            break;
        }
    }
    return firstWord;
}

/**
 * Desc: check if the word is ban
 *
 * Param: Char * word : String to check
 *
 * Return: 1 -> not ban ; 0 -> ban
 */
int correctWord(char *word) {
    return 1;
}

/**
 * Desc: check if the expression is on SQL expr
 *
 * Param: Char * word : String to check
 *
 * Return: 1 -> good ; 0 -> not in expr list
 */
char *checkExprSQL(char *line, char *expr) {
    char *checkline;
    checkline = strstr(upWord(line), expr);
    if (checkline) {
        return "true";
    } else {
        return "false";
    }

}


/**
 * Desc: check & return the type for the column
 *
 * Param: Char * word : String to check
 *
 * Return: type of column
 */
char *checkTypeSQL(char *line) {
    char *type;
    type = strstr(upWord(line), "INT");
    if (!type) {
        type = strstr(upWord(line), "VARCHAR");
        if (!type) {
            type = strstr(upWord(line), "CHAR");
            if (!type) {
                type = strstr(upWord(line), "FLOAT");
                if (type) {
                    type[5] = '\0';
                } else { type = "false"; }
            } else { type[4] = '\0'; }
        } else { type[7] = '\0'; }
    } else { type[3] = '\0'; }
    return type;
}


char *insertSplit(char *buffer, int number) {
    int i;
    int temp;
    int count;
    char word[MAX];

	temp = 0;
	count = 1;

    for (i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == 39) {
            temp = i;
            while (buffer[++i] != 39 && buffer[i-1] != 92) {
                if (i > strlen(buffer)) {
                    return NULL;
                }
            }
            if (count == number) {
                strncpy(word, buffer + temp, i - temp + 1);
                word[i - temp + 1] = '\0';
                return word;
            } else {
                count++;
            }
        } else if (isNumber(buffer[i])) {
            temp = i;
            while (buffer[++i] != ',' && (isNumber(buffer[i]) || buffer[i] == '.')) {
                if (i > strlen(buffer)) {
					printf("Maximum length overpassed for %s\n", buffer);
                    return NULL;
                }
            }
            if (count == number) {
                strncpy(word, buffer + temp, i - temp);
                word[i - temp] = '\0';
                return word;
            } else {
                count++;
            }
        } else if(buffer[i] != 32) {
			printf("error point : buffer[%d/%d] = %c\n", i, strlen(buffer), buffer[i]);
			return NULL;
        }
    }
    return NULL;
}


int isNumber(char buffer) {
    if (buffer < 48 || buffer > 57) {
        return 0;
    } else {
        return 1;
    }
}

char *whichType(char *buffer) {
    int i;
    int intType = 1;
    int floatType = 0;
    if (buffer[0] == 39 && buffer[strlen(buffer) - 1] == 39) {
        if (strlen(buffer) > 3) {
            return "VARCHAR";
        } else {
            return "CHAR";
        }
    } else {
        for (i = 0; i < strlen(buffer); i++) {
            if ((buffer[i] >= '0' && buffer[i] <= '9') || buffer[i] == 46) {
                if (buffer[i] == 46) { floatType = 1; }
            } else {
                intType = 0;
                break;
            }
        }
        if (intType && floatType) { return "FLOAT"; }
        if (intType && !floatType) { return "INT"; }
    }
    return "Wrong Type";
}


char *updateSplitWord(char *buffer, int number, int type) {
    int i;
    int control = 1;
    int constraint = 0;
    int start = 0;
    int end = 1;
    char *word;
    word = malloc(sizeof(char) * MAX);
    int count = 1;
    for (i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == 61 && control == 1) {
            end = (buffer[i - 1] == 32) ? end - 2 : end - 1;
            strncpy(word, buffer + start, end);
            word[end] = '\0';
            if (number == count) {
                if (type == 1) {
                    return word;
                } else if (type == 2) {
                    strcpy(word, insertSplit(buffer + i + 1, 1));
                    return word;
                }
            } else {
                start = i + 1;
                end = 1;
                control = 0;
                constraint = i + strlen(insertSplit(buffer + i + 1, 1)) + 3;
                count++;
                continue;
            }
        }
        if (buffer[i] == 44 && control == 0) {
            control = 1;
            start = (buffer[i + 1] == 32) ? i + 2 : i + 1;
            end = 1;
            continue;
        }
        end++;
    }
    if (!strncmp(upWord(buffer + constraint), "WHERE ", 5)) {
        if (type == 3) {
            strcpy(word, updateSplitWord(buffer + constraint + 5, 1, 1));
            return word;
        } else if (type == 4) {
            strcpy(word, updateSplitWord(buffer + constraint + 5, 1, 2));
            return word;
        } else {
            return NULL;
        }
    }
    return NULL;
}
/**
 * @name strSearchInArray
 *
 * @brief Checks if a given string is in an array of strings.
 *
 * @param char* str : string to search for.
 * @param arrayOfStrings array : array of string to search in.
 *
 * @return (if found) the position of the occurrence in the list.
 * @return (otherwise) -1
 */
int strSearchInArray(char* str, arrayOfStrings array) {
	int i;

	for(i=0 ; i < array.stringsNb ; i++) {
		if(strcmp(str, array.array[i]) == 0) {
			return i;
		}
	}
	return -1;
}

/**
 * @name createArrayOfStrings
 *
 * @brief Creates an "object" arrayOfStrings
 *
 * @param unsigned int nbOfStrings : number of strings possible in the array
 *
 * @return (on success) new object
 * @return (on failure) unknown
 *
 * @see arrayOfStrings
 */
arrayOfStrings createArrayOfStrings(int nbOfStrings) {
	int i;
	arrayOfStrings result;
	if(nbOfStrings > 0) {
		if ( (result.array = malloc(sizeof(char*) * nbOfStrings)) != NULL) {
			result.stringsNb = -1;
			for(i=0 ; i < nbOfStrings ; i++) {
				if ( (result.array[i] = malloc(sizeof(char)*MAX)) == NULL) {
					while(--i >= 0) {
						free(result.array[i]);
						result.stringsNb--;
					}
					free(result.array);
				}
				result.stringsNb++;
			}
		} else {
			error("Allocation error\n");
		}
	}
	return result;
}

/**
 * @name updateArrayOfStrings
 *
 * @brief Allocates columns to the given array typed as `char**`
 *
 * @param arrayOfStrings arrayToUpdate : concerned array
 * @param unsigned int nbOfNewStrings : number of rows to add to the concerned array.
 *
 * @return (on success) updated array
 * @return (on failure) non-updated array
 *
 * @see arrayOfStrings
 */
arrayOfStrings updateArrayOfStrings(arrayOfStrings arrayToUpdate, int nbOfNewStrings) {
	int i;
	char** temp;

	if ( (temp = malloc(sizeof(char*)*arrayToUpdate.stringsNb + nbOfNewStrings)) != NULL ) {
		for(i=0 ; i < arrayToUpdate.stringsNb + nbOfNewStrings ; i++) {
			if ( (temp[i] = malloc(sizeof(char)*MAX)) == NULL ) {
				while(--i >= 0) {
					if(temp[i] != NULL)
						free(temp[i]);
				}
				if(temp != NULL)
					free(temp);
				break;
			} else if(i < arrayToUpdate.stringsNb) {
				temp[i] = arrayToUpdate.array[i];
			}
		}
		free(arrayToUpdate.array);
		arrayToUpdate.array = temp;
	}
	return arrayToUpdate;
}

/**
 * @name freeArrayOfStrings
 *
 * @brief free recursively the given array of strings.
 *
 * @param char** arrayOfStrings : pointer to the concerned array.
 *
 * @return void
 *
 * @see arrayOfStrings
 */
void freeArrayOfStrings(arrayOfStrings* arrayToFree) {
	int i;
	unsigned int tempUInt;

	tempUInt = (*arrayToFree).stringsNb;

	for(i=0 ; i < tempUInt ; i++)
		if ( (*arrayToFree).array[i] != NULL) {
			free( (*arrayToFree).array[i]);
			(*arrayToFree).stringsNb--;
		}
	if ( (*arrayToFree).array != NULL)
		free( (*arrayToFree).array);

}

/**
 * @name compare
 *
 * @brief takes two values and a comparator to apply on them.
 *
 * @param char* str1 : first value.
 * @param char* comparator : string containing the comparator. Will call a pointer of function depending on the string.
 * @param char* str2 : second value.
 *
 * @return (if true) 1
 * @return (if false or error) 0
 */
int compare(char* str1, char* comparator, char* str2) {
	if(str1 != NULL && comparator != NULL && str2 != NULL) {
		if(strcmp(comparator, "=") == 0 || strcmp(comparator, "==") == 0)
			return strcmp(str1, str2) == 0;

		if(strcmp(comparator, ">") == 0)
			return atof(str1)  > atof(str2);

		if(strcmp(comparator, "<") == 0)
			return atof(str1)  < atof(str2);

		if(strcmp(comparator, "!=") == 0 || strcmp(comparator, "<>") == 0)
			return strcmp(str1, str2) != 0;

		if(strcmp(comparator,">=") == 0)
			return atof(str1) >= atof(str2);

		if(strcmp(comparator,"<=") == 0)
			return atof(str1) <= atof(str2);
	}
	return 0;
}

