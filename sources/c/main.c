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
	FILE* fp;
	char* comparators;
	arrayOfStrings keysList;
	arrayOfStrings valuesList;

	keysList = createArrayOfStrings((unsigned int)5);
	valuesList = createArrayOfStrings((unsigned int)5);

	listOfEntities* test = NULL;
	if( (fp = fopen("resources/struct.yaml", "r")) != NULL) {
//		if( (test = getBlockWhere(keysList, comparators, valuesList, fp)) != NULL) {
//			displayListOfEntities(test);
//			freeListOfEntities(&test);
//		} else {
//			error("Error while recovering.\n");
//		}
	} else {
		error("File not found.\n");
	}
    return 0;
}
