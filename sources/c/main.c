#include <stdio.h>
#include <string.h>
#include "../h/struct.h"
#include "../h/parser_SQL.h"
#include "../h/some_funct.h"
#include "../h/parserYAML.h"

#ifndef MAX
    #define MAX 255
#endif  // MAX

int main() {
    FILE* fp;
    char test[MAX];

    fp = fopen("aepo_platform.yml", "r");
    if(fp != NULL) {
        getKeyValue(fp, "id", test);
        if(test != NULL) {
            printf("%s", test);
        }
    } else {
        printf("\nEmpty file.");
    }
    /*
    init();
    requestSQL();*/
    return 0;
}
