#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../h/globals.h"
#include "../h/struct.h"
#include "../h/some_funct.h"
#include "../h/parserYAML.h"

#ifndef MAX
    #define MAX 255     // Maximum size for the non-dynamic strings.
#endif // MAX







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
 * @return (on failure) : in case of allocation error, returns the non-updated list.
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
 * @name removeLastEntity
 *
 * @brief Add an element to a linked list typed as `listOfEntites`.
 *
 * @param listOfEntities* list : pointer of the start of the linked list.
 *
 * @return (on success) : pointer to the updated linked list
 * @return (on failure) : null
 *
 * @see listOfEntities listOfLines addLineToList()
 */
listOfEntities* removeLastEntity(listOfEntities** list) {
	int i;
	listOfEntities* theOneToFree;
	listOfEntities* previous;

	if(*list != NULL) {
		i = 0;
		theOneToFree = *list;
		while(theOneToFree->next != NULL ) {	// Browse the list.
			previous = theOneToFree;
			theOneToFree = theOneToFree->next;
			i++;
		}
		if(i > 0) {
			freeListOfLines(&theOneToFree->entity);	// Frees last node.
			free(theOneToFree);
			if(previous != NULL)
				previous->next = NULL;		// Sets the before-last "next" attribute node of the list to NULL.
			return *list;				// Returns updated list.
		} else {
			freeListOfLines(&theOneToFree->entity);
			return NULL;
		}

	}
    return *list;		// If allocation error, returns the passed list, unchanged.
}

/**
 * @name removeEntityAt
 *
 * @brief Add an element to a linked list typed as `listOfEntites`.
 *
 * @param listOfEntities* list : pointer of the start of the linked list.
 *
 * @return (on success) : pointer to the updated linked list
 * @return (on failure) : null
 *
 * @see listOfEntities listOfLines addLineToList()
 */
listOfEntities* removeEntityAt(listOfEntities** list, int pos) {
	int i;
	listOfEntities* theOneToFree;
	listOfEntities* previous;

	if(list != NULL && pos >= 0) {
		i = 0;
		theOneToFree = *list;
		while(theOneToFree->next != NULL && i != pos) {	// Browse the list.
			previous = theOneToFree;
			theOneToFree = theOneToFree->next;
			i++;
		}
		if(i > 0) {
			previous->next = theOneToFree->next;
		} else {
			*list = (*list)->next;
		}
		freeListOfLines(&theOneToFree->entity);	// Frees appropriated nodes.
		return *list;					// Returns updated list.
	}
    return *list;		// If allocation error, returns the passed list, unchanged.
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
        /*case 39:    // Texte sur une ligne simple quote (39 en ASCII)
            break;
        case 34:    // Texte sur une ligne double quote (34 en ASCII)
            break;*/
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
 * @param char* filePath : path of the concerned file.
 *
 * @return (on success) listOfLines* resultList : line linked list.
 * @return (on failure) null pointer.
 *
 * @see listOfLines lineStruct fGoToLine() freadLine() countTab() verifLine() getLineStruct() addLineToList() FILE_LINE_COUNTER
 */
listOfLines* getEntity(int startLine, char* filePath) {
    char tempStr[MAX];
    lineStruct line;
    listOfLines* resultList;
    FILE* fp;

	if(filePath != NULL) {
		if ( (fp = fopen(filePath, "r")) != NULL) {
			resultList = NULL;
			if(fGoToLine(startLine, fp)) {		// Move the cursor the wanted line.
				while(freadLine(tempStr, MAX, fp) && countTab(tempStr) != 0 && verifLine(tempStr)) {	// Read a line, checks if it's still inside the block and if it has to be treated
					line = getLineStruct(tempStr);					// Recover line object form the line.
					resultList = addLineToList(resultList, line);	// Add that object to the list.
				}
				fseek(fp, -strlen(tempStr)-2, SEEK_CUR); // Return to previous line
				FILE_LINE_COUNTER--;
			}
			fclose(fp);
		}
	}
    return resultList;
}




/* ----- YAML QUERY FUNCTIONS ----- */


/* COMPARISONS */

/**
 * @name compareIntoLine
 *
 * @brief
 *
 * @param lineStruct line : concerned line.
 * @param char* key : key to find and to compare.
 * @param char* value : value to find and to pair up with the key.
 * @param char* comparator : comparator to pair up with the value.
 *
 * @return (on success) 1
 * @return (on failure) 0
 *
 * @see lineStruct
 */
int compareIntoLine(lineStruct line, char* key, char* comparator, char* value) {
	if(key != NULL && comparator != NULL && value != NULL) {
		return compare(line.value, comparator, value);
	}
    return 0;
}

/**
 * @name compareIntoEntities
 *
 * @brief
 *
 * @param listOfLines* list : concerned linked list.
 * @param char* key : key to find and to compare.
 * @param char* value : value to find and to pair up with the key.
 * @param char* comparator : comparator to pair up with the value.
 *
 * @return (on success) 1
 * @return (on failure) 0
 *
 * @see listOfLines compareIntoLine
 */
int compareIntoEntity(listOfLines* entity, char* key, char* comparator, char* value) {
	int occurrenceFound;
    listOfLines* tempList;

	if(entity != NULL && key != NULL && value != NULL) {
		occurrenceFound = 0;
        while( (tempList = entity) != NULL) {
			if(strcmp(entity->line.key, key) == 0) {
				occurrenceFound++;
				if(!compareIntoLine(entity->line, key, comparator, value)) {
					return 0;
				}
            }
            entity = entity->next;
        }
        return occurrenceFound > 0;
    }
    return 0;
}


/* SELECTION */

/**
 * @name getBlocksWhere
 *
 * @brief Returns all the entities having the a matching the key and value passed as parameters.
 *
 * @param char** keys : list of keys to search which will be compare to `values`
 * @param char* comparators : list of comparators (treated as string)
 * @param char** values : list of values which will be compare to `keys`
 * @param char* filePath : path of the concerned file.
 *
 * @return (on success) listOfEntities* entities : linked list of entities matching the request.
 * @return (on failure) null pointer
 *
 * @remarks If an error occurs during the process, still returns the previous found elements.
 *
 * @warning No estimation of the danger the previous remark could generates. A review may be required.
 *
 * @see listOfEntities listOfLines FILE_LINE_COUNTER freadLine() verifLine() countTab() getKey() getValue() getEntity() addEntityToList() error()
 */
listOfEntities* getBlocksWhere(arrayOfStrings keys, arrayOfStrings comparators, arrayOfStrings values, char* filePath) {
	char line[MAX];
	int i;
	int fileSize;
	listOfLines* tempEntity;
	listOfEntities* entities;
	FILE* fp;

	if(filePath != NULL && keys.stringsNb > 0 && keys.stringsNb == comparators.stringsNb && comparators.stringsNb == values.stringsNb) {
		if ( (fp = fopen(filePath, "r")) ) {
			/* Initialization */
			FILE_LINE_COUNTER = 0;
			entities   = NULL;
			tempEntity = NULL;
			fileSize   = fSize(fp);
			fseek(fp, 0, SEEK_SET);
			/* End of initialization */

			while(ftell(fp) < fileSize) {					// Browse the file.
				if(freadLine(line, MAX, fp)) {				// Read a line from the file.
					if(verifLine(line)) {					// If the read line can be treated.
						if(countTab(line) == 0 && strcmp("-", line) == 0) {		// If start of entity
							fclose(fp);
							if ( (tempEntity = getEntity(++FILE_LINE_COUNTER, filePath)) != NULL) {				// Recovers the entity containing those key and value.
								if ( (entities = addEntityToList(entities, tempEntity)) != NULL) {			// Add this entity to the list of entities.
									for(i=0 ; i <= keys.stringsNb ; i++) {
										if(!compareIntoEntity(tempEntity, keys.array[i], comparators.array[i], values.array[i])) {
											entities = removeLastEntity(&entities);
											break;
										}
									}
								}
							} else {
								error("Error while recovering entity.");
								break;
							}
							if ( (fp = fopen(filePath, "r")) !=NULL) {
								fGoToLine(++FILE_LINE_COUNTER, fp);
							}
						}
					}
				}
			}
			fclose(fp);
		}
	}
    return entities;
}

/**
 * @name getAllFrom
 *
 * @brief Recovers all the entities from a given table
 *
 * @param FILE* fp : file pointer of the concerned file.
 *
 * @return (on success) listOfEntities* entities
 * @return (on failure) NULL
 *
 * @remarks Can be used for complex queries where the file manipulation will be too complicated compared to a linked list handling.
 *
 * @see listOfEntities listOfLines fSize() FILE_LINE_COUNTER freadLine() countTab() getEntity() addEntityToList() error()
 */
listOfEntities* getAllFrom(char* filePath) {
    int fileSize;
	char line[MAX];
	listOfLines* tempEntity;
	listOfEntities* entities;
	FILE* fp;

	if(filePath != NULL) {
		if( (fp = fopen(filePath, "r")) != NULL) {
			/* Initialization */
			entities = NULL;
			fileSize = fSize(fp);
			FILE_LINE_COUNTER = 0;
			fseek(fp, 0, SEEK_SET);
			/* End of initialization */

			while(ftell(fp) < fileSize) {			// Browse the file
				if(freadLine(line, MAX, fp)) {		// Read a line from the file.
					if(verifLine(line)) {			// If the line can be treated.
						if(countTab(line) == 0 && strcmp("-", line) == 0) {						// If start of entity
							fclose(fp);
							if ( (tempEntity = getEntity(FILE_LINE_COUNTER+1, filePath)) != NULL) {		// Recover the entity
								if ( (entities = addEntityToList(entities, tempEntity)) == NULL) {	// Add the entity to the list of entities
									error("Error while adding entity from file.");					// If an error occurred during the previous manipulation,
									break;															// Stop the process.
								}
							} else {
								error("Error while recovering entity.");
								break;
							}
							if ( (fp = fopen(filePath, "r")) == NULL) {
								break;
							} else if(!fGoToLine(FILE_LINE_COUNTER, fp)) {
								break;
							}
						}
					}
				}
			}
			fclose(fp);
		}
	}
    return entities;
}


/* INSERTION */

/**
 * @name insertLine
 *
 * @brief Insert a line in the given file at the current cursor position which is then set to a new empty line bellow the inserted one.
 *
 * @param lineStruct line : line to insert.
 * @param FILE* fp : file pointer to the concerned pointer.
 *
 * @return (on success) 1
 * @return (on failure) 0
 *
 * @warning Better call this function through `insertEntity`.
 *
 * @see lineStruct insertEntity() insertEntity()
 */
int insertLine(lineStruct line, char* filePath) {
	FILE* fp;

	if(filePath != NULL) {
		if ( (fp = fopen(filePath, "r+")) != NULL ) {
			fseek(fp, -5, SEEK_END);
			fprintf(fp, "    %s : %s\n...\n", line.key, line.value);
			fclose(fp);
			return 1;
		}
	}
	return 0;
}

/**
 * @name insertEntity
 *
 * @brief Insert an entity in the given file at the current cursor position.
 *
 * @param listOfLines* entity : entity to insert.
 * @param FILE* fp : file pointer to the concerned file.
 *
 * @return (on success) 1
 * @return (on failure) 0
 *
 * @warning Shall be called by `insertListOfEntities` function only.
 * 			The cursor has to be set before process the following function (which `insertListOfEntities` does)
 *
 * @see listOfLines insertLine() insertListOfEntities()
 */
int insertEntity(listOfLines* entity, char* filePath) {
	FILE* fp;
	listOfLines* tempEntity;

	if(filePath != NULL) {
		if(entity != NULL && filePath != NULL) {
			if ( (fp = fopen(filePath, "r+")) != NULL ) {
				fseek(fp, -5, SEEK_END);
				fputs("\n-\n...\n", fp);
				fclose(fp);
				while ( (tempEntity = entity) != NULL) {
					if(!insertLine(entity->line, filePath)) {
						return 0;
					}
					entity = entity->next;
				}
				if ( (fp = fopen(filePath, "r+")) != NULL ) {
					fseek(fp, -5, SEEK_END);
					fputs("\n...\n", fp);
					fclose(fp);
					return 1;
				}
			}
		}
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
 * @see listOfEntities fSize() FILE_LINE_COUNTER freadLine() insertEntity()
 */
int insertListOfEntities(listOfEntities* entities, char* filePath) {
	listOfEntities* tempEntity;

	if(filePath != NULL) {
		while ( (tempEntity = entities) != NULL) {
			if(!insertEntity(entities->entity, filePath)) {
				return 0;
			}
			entities = entities->next;
		}
		return 1;
	}
	return 0;
}

/**
 * @name updateLine
 *
 * @brief
 *
 * @param lineStruct line : concerned line.
 * @param char* key : key to find and to compare.
 * @param char* value : value to find and to pair up with the key.
 * @param char* comparator : comparator to pair up with the value.
 *
 * @return (on success) updated line
 * @return (on failure) non-updated line
 *
 * @see lineStruct
 */
int updateLine(lineStruct* line, char* key, char* value) {
	if(line != NULL && key != NULL && value != NULL) {
		strcpy((*line).key, key);
		strcpy((*line).value, value);
		return 1;
	}
    return 0;
}

/**
 * @name updateEntity
 *
 * @brief
 *
 * @param listOfLines** entity : pointer of the concerned linked list.
 * @param char* key : key to find and to compare.
 * @param char* value : value to find and to pair up with the key.
 * @param char* comparator : comparator to pair up with the value.
 *
 * @return (on success) updated entity
 * @return (on failure) non-updated or partially updated entity
 *
 * @see listOfEntities updateLine
 */
int updateEntity(listOfLines** entity, char* key, char* value) {
	if(*entity != NULL && key != NULL && value != NULL) {
        if(*entity != NULL) {
			if(strcmp((*entity)->line.key, key) == 0) {
				if(!updateLine(&((*entity)->line), key, value)) {
					return 0;
				}
            }
        }
        return 1;
    }
    return 0;
}

/**
 * @name updateFile
 *
 * @brief
 *
 * @param char* filePath : path of the concerned file
 * @param listOfEntities* newContent : linked list to write in the file
 *
 * @return (on success) 1
 * @return (on failure) 0
 *
 * @see listOfEntities
 */
int updateFile(char* filePath, listOfEntities* newContent) {
	FILE* fp;
	if(filePath != NULL && newContent != NULL) {
		if ( (fp = fopen(filePath, "w"))) {
			fprintf(fp, "# %s\n---\n...\n", filePath);
			fclose(fp);
			return insertListOfEntities(newContent, filePath);
		}
	}
	return 0;
}

/**
 * @name updateValuesWhere
 *
 * @brief update several values in following some conditions.
 *
 * @param char** keys : list of keys having a condition to comply with.
 * @param char* comparator : array of char listing comparator (has to finish by '\0' as a string)
 * @param char** values : list of values compare to `keys` (bind by index).
 * @param char** keysToUpdate : list of keys to update.
 * @param char** newValues : values to set to the keys being updated.
 * @param FILE* fp : YAML file to which do the update.
 *
 * @return (on success) 1
 * @return (on failure) 0
 *
 * @see
 */
int updateValuesWhere(AoS keys, AoS comparators, AoS values, AoS keysToUpdate, AoS newValues, char* filePath) {
	int i;
	int changesDone;
	int comparisonsAllTrue;
	FILE* fp;
	listOfEntities* cursor;
	listOfEntities* entities;

	if(filePath != NULL
	&& keys.stringsNb > 0
	&& keysToUpdate.stringsNb > 0
	&& keysToUpdate.stringsNb == newValues.stringsNb
	&& keys.stringsNb == comparators.stringsNb
	&& comparators.stringsNb == values.stringsNb
	) {
		if ( (fp = fopen(filePath, "r")) ) {
			/* Initialization */
			cursor = NULL;
			entities = NULL;
			entities = NULL;
			/* End of initialization */

			if ( (entities = getAllFrom(filePath)) != NULL) {
				changesDone = 0;
				cursor = entities;
				while(cursor != NULL) {
					comparisonsAllTrue = 0;
					for(i=0 ; i < keys.stringsNb ; i++) {
						if(compareIntoEntity(cursor->entity, keys.array[i], comparators.array[i], values.array[i])) {
							comparisonsAllTrue = 1;
						} else {
							comparisonsAllTrue = 0;
							break;
						}
					}
					if(comparisonsAllTrue) {
						for(i=0 ; i < keysToUpdate.stringsNb ; i++) {
							if(updateEntity(&(cursor->entity), keysToUpdate.array[i], newValues.array[i])) {
								changesDone = 1;
							} else {
								error("Error while updating.\n");
							}
						}
					}
					cursor = cursor->next;
				}
				if(changesDone) {
					if(updateFile(filePath, entities)) {
						printf("Updated successfull.\n");
						freeListOfEntities(&entities);
						return 1;
					}
				}
				freeListOfEntities(&entities);
			}
		}
	}
	return 0;
}


/* DELETION */

