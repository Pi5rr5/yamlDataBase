#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../h/globals.h"
#include "../h/struct.h"
#include "../h/some_funct.h"
#include "../h/parserYAML.h"

/* ----- MAIN ----- */
int main(int argc, char **argv) {
    //menu();
    char filePath[MAX] = "resources/struct.yaml";
    arrayOfStrings keys;
    arrayOfStrings values;
    arrayOfStrings comparators;
    arrayOfStrings keysToUpdate;
    arrayOfStrings newValues;
    listOfEntities* testList;

    keys = createArrayOfStrings(2);
    values = createArrayOfStrings(2);
    comparators = createArrayOfStrings(2);

    newValues = createArrayOfStrings(4);
    keysToUpdate = createArrayOfStrings(4);

    strcpy(keys.array[0], "type");
    strcpy(comparators.array[0], "!=");
    strcpy(values.array[0], "double");

    strcpy(keys.array[1], "auto_increment");
    strcpy(comparators.array[1], "==");
    strcpy(values.array[1], "false");

    strcpy(newValues.array[0], "the one");
    strcpy(newValues.array[1], "undefined");
    strcpy(newValues.array[2], "true");
    strcpy(newValues.array[3], "false");
    strcpy(keysToUpdate.array[0], "name");
    strcpy(keysToUpdate.array[1], "type");
    strcpy(keysToUpdate.array[2], "null");
    strcpy(keysToUpdate.array[3], "primary");

	if(updateValuesWhere(keys, comparators, values, keysToUpdate, newValues, filePath)) {
		if ( (testList = getBlockWhere(keys, comparators, values, filePath)) != NULL) {
			displayListOfEntities(testList);
			freeListOfEntities(&testList);
		}
	}

    freeArrayOfStrings(&keys);
    freeArrayOfStrings(&values);
    freeArrayOfStrings(&comparators);
    return 0;
}
