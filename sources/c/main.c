#include <stdio.h>
#include <string.h>
#include "../h/struct.h"
#include "../h/parser_SQL.h"
#include "../h/some_funct.h"
#include "../h/parserYAML.h"

#ifndef MAX
    #define MAX 255
#endif  // MAX

int main(int argc, char **argv) {
    FILE* fp;
    ll_dataBlock* test;

    fp = fopen("aepo_platform.yml", "r");
    if(fp != NULL) {
        test = getKey(fp, "id_machin");
    } else {
        printf("\nEmpty file.");
    }
    /*
    init();
    requestSQL();*/
    return 0;
}
