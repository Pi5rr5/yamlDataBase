#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../h/struct.h"
#include "../h/some_funct.h"
#include "../h/parserYAML.h"

/* ----- GLOBALS ----- */
int FILE_LINE_COUNTER;

/* ----- MAIN ----- */
int main(int argc, char **argv) {
	int i;
	FILE* fp;
	arrayOfStrings keys;
	arrayOfStrings values;
	arrayOfStrings comparators;

	keys = createArrayOfStrings((unsigned int)2);
	values = createArrayOfStrings((unsigned int)2);
	comparators = createArrayOfStrings((unsigned int)2);

	strcpy(keys.array[0], "null");
	strcpy(keys.array[1], "length");
	strcpy(values.array[0], "false");
	strcpy(values.array[1], "1023");
	strcpy(comparators.array[0], "=");
	strcpy(comparators.array[1], "<");

	listOfEntities* test = NULL;
	if( (fp = fopen("resources/struct.yaml", "r")) != NULL) {
		if( (test = getBlockWhere(keys, comparators, values, fp)) != NULL) {
			displayListOfEntities(test);
			freeListOfEntities(&test);
		} else {
			printf("No recover.\n");
		}
	} else {
		error("File not find.\n");
	}

	freeArrayOfStrings(&keys);
	freeArrayOfStrings(&values);
	freeArrayOfStrings(&comparators);

    return 0;
}
