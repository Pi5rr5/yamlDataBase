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
	char* comparators;
	char** keysList;
	char** valuesList;

	listOfEntities* test = NULL;
	printf("%d/%d = %d\n", sizeof(keysList), sizeof(*keysList), sizeof(keysList)/sizeof(*keysList));
	if( (fp = fopen("resources/struct.yaml", "r")) != NULL) {
		if( (test = getBlockWhere(keysList, comparators, valuesList, fp)) != NULL) {
			displayListOfEntities(test);
			freeListOfEntities(&test);
		} else {
			error("Error while recovering.\n");
		}
	} else {
		error("File not found.\n");
	}
    return 0;
}
