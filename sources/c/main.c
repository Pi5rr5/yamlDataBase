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
	lineStruct line;
	listOfLines* tempEntity;
	listOfEntities* testList;

	strcpy(line.key, "test");
	strcpy(line.value, "valeur test");
	tempEntity = NULL;
	testList = NULL;

	if ( (tempEntity = addLineToList(tempEntity, line)) != NULL) {
		if ( (testList = addEntityToList(testList, tempEntity)) != NULL) {
			if( (fp = fopen("resources/struct.yaml", "a+")) != NULL) {
				if(!insertListOfEntities(testList, x) ) {
					printf("Fail to insert.\n");
				} else {
					printf("Success to insert.");
					fclose(fp);
				}
				freeListOfEntities(&testList);
			} else {
				error("File not find.\n");
			}
		}
	}
    return 0;
}
