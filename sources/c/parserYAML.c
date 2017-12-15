#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../h/struct.h"
#include "../h/some_funct.h"
#include "../h/parserYAML.h"

#ifndef MAX
    #define MAX 255     // Maximum size for the non-dynamic strings.
#endif // MAX

/* ---------------- GLOBALS ---------------- */
/**
 * @name FILE_LINE_COUNTER
 *
 * @brief global counting le current line number on which is the file cursor. Updated by few functions.
 *
 * @remarks `extern` is exclusive to globals variables.
 *			It allows to specify to the compiler that the variable may have been already declared in another file.
 *			And if it has been, then it will be not redeclared
 *
 * @see getEntity() getBlockWhere() getAllFrom() freadL()
 */
extern int FILE_LINE_COUNTER;








/* ---------------- FUNCTIONS ---------------- */




/* ----- LINKED LISTS  ----- */


/* listOfLines */

/**
 * @name addLineToList
 *
 * @brief Add an element to linked list typed as `listOfLines`
 *
 * @param listOfLines* list : pointer of the start of the linked list.
 * @param value : value to add in the new element.
 *
 * @return (on success) : pointer to the updated linked list.
 * @return (on failure) : in case of an allocation error, returns a null pointer.
 *
 * @see listOfLines lineStruct
 */
listOfLines* addLineToList(listOfLines* list, lineStruct line) {
    listOfLines* new_element;
    listOfLines* temp;

    new_element = malloc(sizeof(listOfLines));	// Required allocation for the new element.
    if(new_element != NULL) {				// If the allocation went well.
        new_element->line = line;			// We assign the value passed in argument to the corresponding attribute of the new element.
        new_element->next = NULL;			// `next` pointer is set to NULL, the new element becoming the last node.
        if(list == NULL) {					// If the given list is empty.
            return new_element;				// Return of the new element only (because it's the only node).
        } else {
            temp = list;					// Otherwise, adding of the new element to the list.
            while(temp->next != NULL) {		// Browse the list.
                temp = temp->next;
            }
            temp->next = new_element;		// Make the current last node of the list points on the new element.
            return list;					// Returning of the updated list.
        }
    }
    return list;	// If allocation error, returns the passed list, unchanged.
}

/**
 * @name displayListOfLines
 *
 * @brief Display each element of a linked list typed as `listOfLines`.
 *
 * @param listOfLines* list : concerned linked list.
 *
 * @return void
 *
 * @remarks Could be use as debugging tool as well as user interface. Feel free to personalize the displaying.
 *
 * @see listOflines lineStruct
 */
void displayListOfLines(listOfLines* list) {
    listOfLines* temp;

    printf("\tList of lines :\n");
    if(list != NULL) {
        while ( (temp = list) != NULL) {
            printf("\t\tkey : %s\n\t\tvalue : %s\n\n", list->line.key, list->line.value);
            list = list->next;
        }
    } else {
        error("\t\tEmpty list.");
    }
    printf("\tEnd of list.\n\n");
}

/**
 * @name freeListOfLines
 *
 * @brief releasing of the memory used by a linked list typed as `listOfLines`.
 *
 * @param listOfLines** list : pointer of the concerned linked list.
 *
 * @return void
 *
 * @see listOfLines
 */
void freeListOfLines(listOfLines** list) {
    listOfLines* temp;

    if(*list != NULL) {
        while( (temp = *list) != NULL ) {	// Browsing the list
        	*list = (*list)->next;
			free(temp);
        }
    }
}


/* listOfEntities */

/**
 * @name addEntityToList
 *
 * @brief Add an element to a linked list typed as `listOfEntites`.
 *
 * @param listOfEntities* list : pointer of the start of the linked list.
 * @param value : value to put in the new element.
 *
 * @return (on success) : pointer to the updated linked list
 * @return (on failure) : in case of allocation error, returns a null pointer
 *
 * @see listOfEntities listOfLines addLineToList()
 */
listOfEntities* addEntityToList(listOfEntities* list, listOfLines* entity) {
    listOfEntities* new_element;

    new_element = malloc(sizeof(listOfEntities));	// Required memory allocation for the new element
    if(new_element != NULL) {				// If the allocation went well
		new_element->entity = entity;		// We assign the value passed in argument to the corresponding attribute of the new element.
        new_element->next = NULL;			// `next` pointer is set to NULL, the new element becoming the last node.
		if(list == NULL) {					// If the given list is empty.
            return new_element;				// Return of the new element only (because it's the only node).
        } else {								// Otherwise, adding of the new element to the list.
            while( list->next != NULL ) {	// Browse the list.
                list = list->next;
            }
            list->next = new_element;		// Make the current last node of the list points on the new element.
            return list;					// Returning of the updated list.
        }
    }
    return list;		// If allocation error, returns the passed list, unchanged.
}

/**
 * @name displayListOfEntities
 *
 * @brief Display each element of linked list typed as `listOfEntities`
 *
 * @param listOfEntities* list : concerned linked list.
 *
 * @return void
 *
 * @remarks Could be used as debugging tool as well as user interface.
 *
 * @see listOfEntities displayListOfLines()
 */
void displayListOfEntities(listOfEntities* list) {
    listOfEntities* temp;

    printf("\nList of entities :\n");
    if(list != NULL) {
        while ( (temp = list) != NULL) {
            displayListOfLines(list->entity);
            list = list->next;
        }
    } else {
        error("\tEmpty list.\n");
    }
    printf("End of list.\n\n");
}

/**
 * @name freeListOfEntities
 *
 * @brief Release the memory used by a linked list typed as `listOfEntities`
 *
 * @param listOfEntities** list : pointer of the concerned linked list.
 *
 * @return void
 *
 * @see listOfEntities freeListOfLines()
 */
void freeListOfEntities(listOfEntities** list) {
    listOfEntities* temp;

    if(*list != NULL) {
        while ( (temp = *list) != NULL ) {		// Browsing the list
            *list = (*list)->next;
			freeListOfLines(&temp->entity);		// Releasing the `listOfLines` attribute.
			free(temp);
        }
    }
}




/* ----- YAML PARSER FUNCTIONS ----- */

/**
 * @name isEOY (isEndOfYAML)
 *
 * @brief checks if the given string is corresponding of the indicator of end of YAML file (i.e "...").
 *
 * @param char* str : string to test.
 *
 * @return (on success) 1
 * @return (on failure) 0
 */
int isEOY(char* str) {
	return str != NULL && ( strcmp(str, "...") == 0 || strcmp(str, "...\n") == 0 || strcmp(str, "...\r\n") == 0 );
}

/**
 * @name verifLine
 *
 * @brief Checks if the concerned line is subject to treatment.
 *
 * @param char* str : concerned string.
 *
 * @return (on success) 1
 * @return (on failure) 0
 */
int verifLine(char* str) {
	int tempInt = 0;

    // Empty string case
    if(str == NULL || strlen(str) == 0)
        return 0;

    // Start of file case
    if(strcmp(str, "---") == 0      // A YAML file starts with "---"
    || strcmp(str, "---\n") == 0    // It can be followed by a line break
    || strcmp(str, "---\r\n") == 0) // There can be a carriage return before the line break
        return 0;

    // End of file case
    if(strcmp(str, "...") == 0      // A YAML file ends with "..."
    || strcmp(str, "...\n") == 0    // It can be followed by a line break
    || strcmp(str, "...\r\n") == 0) // There can be a carriage return before the line break
        return 0;

    // Comment or empty line
    while(str[tempInt++] == ' ');	// Ignore indentation
    if(str[tempInt] == '#' || str[tempInt] == '\n' || str[tempInt] == '\r')		// If is a comment or line break
        return 0;

    return 1;   // If none of above, then the line can be treated.
}

/**
 * @name getKey
 *
 * @brief Takes a line of a YAML file as argument and return the key which is therein.
 *
 * @param char* line : concerned YAML line.
 *
 * @return (on success) char* result : obtained key.
 * @return (on failure) null pointer.
 */
char* getKey(char* line) {
    int tempInt;
    int keyStart;
    char result[MAX];

    tempInt  = 0;
    keyStart = 0;

    while(line[tempInt++] == ' ');                          // Founds the index of the first character that is not ' '
    keyStart = tempInt-1;									// `tempInt` is one step too far (since '++' in the previous loop is triggered even at the last lap).
    while(line[tempInt++] != ' ' && line[tempInt] != ':');  // Founds the index of the next character that is neither a ' ' nor a ':'

    strncpy(result, line+keyStart, tempInt-keyStart-1);     /* Copy the key in result.
																line+KeyStart : position to start the copy.
																		line is the address of the string. The size of a `char` is, in almost any case, 1.
																		Therefore adding 1 to `line` is the same as starting this line one character further.
																tempInt-keyStart+1 : number of characters to copy (-1 because tempInt is one step too far). */

    result[tempInt-keyStart-1] = '\0';						// `strncpy` does not handle '\0' (-1 because tempInt is one step too far).
    strcpy(line, result);	// Straight return of `result` might be dangerous since it's a local variable. Therefore it is stored in `line`.
    return line;
}

/**
 * @name getValue
 *
 * @brief Takes a line of a YAML file as argument and return the key which is therein.
 *
 * @param char* line : concerned YAML line.
 *
 * @return (on success) char* : obtained value.
 * @return (on failure) char* : ""
 */
char* getValue(char* line) {
    int tempInt = 0;

    while(line[tempInt++] != ':');      // Founds the index of the first occurrence of ':'
    while(line[tempInt++] == ' ');      // Founds the index of the next character that is not ' '

    switch(line[tempInt]) {
        case 39:    // Texte sur une ligne simple quote (39 en ASCII)
            break;
        case 34:    // Texte sur une ligne double quote (34 en ASCII)
            break;
        default:    // Valeur classique
            return line+tempInt-1;	/* line+tempInt-1 : position to start the copy.
										Line is the address of the string. The size of a `char` is, in almost any case, 1.
										Therefore adding 1 to `line` is the same as starting this line one character further.
										'-1' : `tempInt` is one step too far (since '++' in the previous loop is triggered even at the last lap).*/
    }
    return "";
}

/**
 * @name getLineStruct
 *
 * @brief Takes a YAML line as parameter and retruns an object `lineStruct` from it.
 *
 * @param char* str : concerned string of YAML line.
 *
 * @return (on success) lineStruct line : `lineStruct` object.
 *
 * @remarks Failure case is not handled but should not appears.
 *
 * @see lineStruct getKey() getValue()
 */
lineStruct getLineStruct(char* str) {
    lineStruct line;

    strcpy(line.key, getKey(str));      // Recover the key from the line.
    strcpy(line.value, getValue(str));  // Recover the value from the line.
    return line;
}

/**
 * @name getEntity
 *
 * @brief Recover the entirety of an entity.
 *
 * @param int startLine : Line where start the entity.
 * @param FILE* sourceFile : file pointer of the concerned file.
 *
 * @return (on success) listOfLines* resultList : line linked list.
 * @return (on failure) null pointer.
 *
 * @see listOfLines lineStruct fGoToLine() freadL() countTab() verifLine() getLineStruct() addLineToList() FILE_LINE_COUNTER
 */
listOfLines* getEntity(int startLine, FILE* sourceFile) {
    char tempStr[MAX];
    lineStruct line;
    listOfLines* resultList;

    resultList = NULL;
    if(sourceFile != NULL) {
        if(fGoToLine(startLine, sourceFile)) {		// Move the cursor the wanted line.
            while(freadL(tempStr, MAX, sourceFile) && countTab(tempStr) != 0 && verifLine(tempStr)) {	// Read a line, checks if it's still inside the block and if it has to be treated
            	line = getLineStruct(tempStr);					// Recover line object form the line.
            	resultList = addLineToList(resultList, line);	// Add that object to the list.
            }
            fseek(sourceFile, -strlen(tempStr)-2, SEEK_CUR);	// Return to previous line
            FILE_LINE_COUNTER--;
        }
    }
    return resultList;
}




/* ----- YAML QUERY FUNCTIONS ----- */

/**
 * @name getBlockWhere
 *
 * @brief Returns all the entities having the a matching the key and value passed as parameters.
 *
 * @param char** keysList : list of keys to search which will be compare to `valuesList`
 * @param char* comparators : list of comparators (treated as string)
 * @param char** valuesList : list of values which will be compare to `keysList`
 * @param FILE* sourceFile : file pointer of the concerned file.
 *
 * @return (on success) listOfEntities* entities : linked list of entities matching the request.
 * @return (on failure) null pointer
 *
 * @remarks If an error occurs during the process, still returns the previous found elements.
 *
 * @warning No estimation of the danger the previous remark could generates. A review may be required.
 *
 * @see listOfEntities listOfLines FILE_LINE_COUNTER freadL() verifLine() countTab() getKey() getValue() getEntity() addEntityToList() error()
 */
listOfEntities* getBlockWhere(arrayOfStrings keysList, arrayOfStrings comparators, arrayOfStrings valuesList, FILE* sourceFile) {
	char line[MAX];
	char tempKey[MAX];
	char tempValue[MAX];
	int tempInt;
	int fileSize;
	int tabulation;
	int startingLine;
	listOfLines* tempEntity;
	listOfEntities* entities;

    startingLine = 0;
    FILE_LINE_COUNTER = 0;
    entities   = NULL;
    tempEntity = NULL;
	fileSize   = fSize(sourceFile);
	fseek(sourceFile, 0, SEEK_SET);

    while(ftell(sourceFile) < fileSize) {					// Browse the file.
		if(freadL(line, MAX, sourceFile)) {					// Read a line from the file.
        	if(verifLine(line)) {							// If the read line can be treated.
            	tabulation = countTab(line);
                if(tabulation == 0 && strcmp("-", line) == 0) {		// If start of entity
                    startingLine = FILE_LINE_COUNTER;				// Stores the current line number.
                } else if(tabulation > 0) {																// Will be '-1' if an error occurred before.
                    if(strcpy(tempKey, getKey(line)) != NULL) {											// Recovers the key.
						if( (tempInt = strSearchInArray(tempKey, keysList)) >= 0) {							// Checks if this key is the wanted one.
							if(strcpy(tempValue, getValue(line)) != NULL) {									// Recovers the value.
								if( compare(tempValue, comparators.array[tempInt], valuesList.array[tempInt]) ) {	// Checks if this value matches the wanted comparison.
									if((tempEntity = getEntity(startingLine+1, sourceFile)) != NULL) {				// Recovers the entity containing those key and value.
                                        if ( (entities = addEntityToList(entities, tempEntity)) == NULL) {			// Add this entity to the list of entities.
                                            error("Error while adding entity from file.");							// If an occurs during the previous manipulation,
                                            break;																	// Then stop the process.
                                        }
                                    } else {
                                        error("Error while recovering entity.");
                                        break;
                                    }
                                }
                            } else {
                                error("Error while recovering value.");
                                break;
                            }
                        }
                    } else {
                        error("Error while recovering key.");
                        break;
                    }
                }
            }
        }
    }
    return entities;
}

/**
 * @name getAllFrom
 *
 * @brief Recovers all the entities from a given table
 *
 * @param FILE* sourceFile : file pointer of the concerned file.
 *
 * @return (on success) listOfEntities* entities :
 * @return (on failure) NULL
 *
 * @remarks Can be used for complex queries where the file manipulation will be too complicated compared to a linked list handling.
 *
 * @see listOfEntities listOfLines fSize() FILE_LINE_COUNTER freadL() countTab() getEntity() addEntityToList() error()
 */
listOfEntities* getAllFrom(FILE* sourceFile) {
    int fileSize;
	char line[MAX];
	listOfLines* tempEntity;
	listOfEntities* entities;

	if(sourceFile != NULL) {
		/* Initialization */
		entities = NULL;
		fileSize = fSize(sourceFile);
		FILE_LINE_COUNTER = 0;
		fseek(sourceFile, 0, SEEK_SET);
		/* End of initialization */

		while(ftell(sourceFile) < fileSize) {					// Browse the file
			if(freadL(line, MAX, sourceFile)) {					// Read a line from the file.
				if(verifLine(line)) {							// If the line can be treated.
					if(countTab(line) == 0 && strcmp("-", line) == 0) {								// If start of entity
						if ( (tempEntity = getEntity(FILE_LINE_COUNTER+1, sourceFile)) != NULL) {	// Recover the entity
							if ( (entities = addEntityToList(entities, tempEntity)) == NULL) {		// Add the entity to the list of entities
								error("Error while adding entity from file.");							// If an error occurred during the previous manipulation,
								break;																	// Stop the process.
							}
						} else {
							error("Error while recovering entity.");
							break;
						}
					}
				}
			}
		}
	}
    return entities;
}

/*
/\**
 * @name updateValuesWhere
 *
 * @brief update several values in following some conditions.
 *
 * @param char** keysList : list of keys having a condition to comply with.
 * @param char* comparator : array of char listing comparator (has to finish by '\0' as a string)
 * @param char** valuesList : list of values compare to `keysList` (bind by index).
 * @param char** keysToUpdate : list of keys to update.
 * @param char** newValues : values to set to the keys being updated.
 * @param FILE* destinationFile : YAML file to which do the update.
 *
 * @return (on success) 1
 * @return (on failure) 0
 *
 * @see
 *\/
int updateValuesWhere(char** keysList, char* comparators, char** valuesList, char** keysToUpdate, char** newValues, FILE* destinationFile) {
	int i;
	int j;
	size_t keysNb;
	size_t keyEqualsNb;
	size_t keysToUpdateNb;
	size_t newValuesNb;

	if ( destinationFile != NULL && keysToUpdate != NULL && newValues != NULL ) {
		if ( keysNb == strALen(valuesList) && keysNb == strlen(comparators) ) {
			for(i=0 ; i < keysNb ; i++) {

			}
		}
	}
	return 0;
}*/

/**
 * @name insertLine
 *
 * @brief Insert a line in the given file at the current cursor position which is then set to a new empty line bellow the inserted one.
 *
 * @param lineStruct line : line to insert.
 * @param FILE* destinationFile : file pointer to the concerned pointer.
 *
 * @return (on success) 1
 * @return (on failure) 0
 *
 * @warning Better call this function through `insertEntity`.
 *
 * @see lineStruct insertEntity() insertEntity()
 */
int insertLine(lineStruct line, FILE* destinationFile) {
	if(line.key != NULL && line.value != NULL && destinationFile != NULL) {
		printf("    %s : %s\n", line.key, line.value);
		return fprintf("    %s : %s\n", line.key, line.value) > 0;
	}
	return 0;
}

/**
 * @name insertEntity
 *
 * @brief Insert an entity in the given file at the current cursor position.
 *
 * @param listOfLines* entity : entity to insert.
 * @param FILE* destinationFile : file pointer to the concerned file.
 *
 * @return (on success) 1
 * @return (on failure) 0
 *
 * @warning Shall be called by `insertListOfEntities` function only.
 * 			The cursor has to be set before process the following function (which `insertListOfEntities` does)
 *
 * @see listOfLines insertLine() insertListOfEntities()
 */
int insertEntity(listOfLines* entity, FILE* destinationFile) {
	listOfLines* tempEntity;

	if(entity != NULL && destinationFile != NULL) {
		while ( (tempEntity = entity) != NULL) {
			if(!insertLine(entity->line, destinationFile)) {
				return 0;
			}
			tempEntity = entity->next;
		}
		return 1;
	}
	return 0;
}


/**
 * @name insertListOfEntities
 *
 * @brief Insert a list of entities in conformed YAML format at the end of the YAML file.
 *
 * @param listOfEntities* entities : list of entities to insert.
 * @param FILE* destination : file pointer to the concerned file.
 *
 * @return (on success) 1
 * @return (on failure) 0
 *
 * @see listOfEntities fSize() FILE_LINE_COUNTER freadL() insertEntity()
 */
int insertListOfEntities(listOfEntities* entities, FILE* destinationFile) {
	int i = 0;
	int fileSize;
	char tempStr[MAX];
	listOfEntities* tempEntity;

	if(destinationFile != NULL) {

		while( ftell(destinationFile) < fileSize ) {
			i++;
			if(freadL(tempStr, MAX, destinationFile)) {
				if(isEOY(tempStr)) {
					if(fprintf(destinationFile, "-\n") > 0) {
						while ( (tempEntity = entities) != NULL) {
							insertEntity(entities->entity, destinationFile);
							entities = entities->next;
						}
					}
				}
			}
		}
	}
	return 0;
}
