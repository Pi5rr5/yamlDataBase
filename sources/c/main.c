#include <stdio.h>
#include <string.h>
#include "../h/struct.h"
#include "../h/parser_SQL.h"
#include "../h/some_funct.h"
#include "../h/parserYAML.h"

#ifndef MAX
    #define MAX 255
#endif  // MAX

/* ----- GLOBALS ----- */
int FILE_LINE_COUNTER;

/* ----- MAIN ----- */
int main(int argc, char **argv) {
    FILE* fp;
    listOfEntities* test;

    fp = fopen("resources/databases.yaml", "r");
    if(fp != NULL) {
        FILE_LINE_COUNTER = 0;
        if ( (test = getBlockWhere("name", "test1", fp)) != NULL)
            displayListOfEntities(test);
        freeListOfEntities(test);
        displayListOfEntities(test);
        if(fclose(fp) != 0) {
            perror("\nError while closing file.\n");
        }
    } else {
        error("File not found.");
    }
    /*
    init();
    requestSQL();*/
    return 0;
}
