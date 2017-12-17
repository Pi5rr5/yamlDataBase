#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../h/globals.h"
#include "../h/struct.h"
#include "../h/some_funct.h"
#include "../h/parserYAML.h"

/* ----- MAIN ----- */
int main(int argc, char **argv) {

    menu();
    /*arrayOfStrings keys;
    arrayOfStrings values;
    arrayOfStrings comparators;
    listOfEntities* testList;

    keys = createArrayOfStrings(2);
    values = createArrayOfStrings(2);
    comparators = createArrayOfStrings(2);

    strcpy(keys.array[0], "type");
    strcpy(comparators.array[0], "!=");
    strcpy(values.array[0], "double");

    strcpy(keys.array[1], "auto_increment");
    strcpy(comparators.array[1], "==");
    strcpy(values.array[1], "false");

    if ( (testList = getBlockWhere(keys, comparators, values, "resources/struct.yaml")) != NULL) {
        displayListOfEntities(testList);
        freeListOfEntities(&testList);
    }

    freeArrayOfStrings(&keys);
    freeArrayOfStrings(&values);
    freeArrayOfStrings(&comparators);*/
    return 0;
}
