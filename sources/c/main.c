#include <stdio.h>
#include <string.h>
#include "../h/main.h"
#include "../h/parser_SQL.h"
#include "../h/some_funct.h"


int main() {
    init();
    requestSQL();
    return 0;
}

void requestSQL() {
    int counter;
    int len;
    counter = 1;
    char word[255];
    printf("\n%d : ", counter);
    while (scanf("%[^\n]%*c", word) == 1) {
        if (strstr(word, ";") != NULL) {
            len = strlen(word);
            word[len - 1] = '\0';
            parserSQL(word, cmdRequest);

            break;
        }
        //traiter le multi-ligne
        printf("%d : ", ++counter);
    }

}


//blop