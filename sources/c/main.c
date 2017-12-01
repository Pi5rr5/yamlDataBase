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
int fileLineCounter;

/* ----- MAIN ----- */
int main(int argc, char **argv) {
    FILE* fp;

    fp = fopen("test.yml", "r");
    if(fp != NULL) {
        fileLineCounter = 0;
        getBlockWhere("id_machin", "1", fp);
        if(fclose(fp) != 0) {
            perror("\nError while closing file.\n");
        }
    } else {
        printf("\nEmpty file.");
    }
    /*
    init();
    requestSQL();*/
    return 0;
}
