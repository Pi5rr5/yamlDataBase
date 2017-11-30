//
// Created by Qut on 29/10/2017.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../h/some_funct.h"
#include "../h/system_function.h"
#include "../h/struct.h"

//***********************************************
void parse_use(char *buffer) {
    //  verifier qu'il reste un mot (un seul)
    buffer += 4;
    useDB(buffer);
    requestSQL();
}

void parserSQL(char *word, command_options *command) {
    int error;
    error = 1;
    int loop;
    char *upword;
    upword = upWord(word);
    for (loop = 0; command[loop].name; loop++) {
        if (!strncmp(upword, command[loop].name, strlen(command[loop].name))) {
            command[loop].f(word);
            error = 0;
            break;
        }
    }
    error ? parse_error() : NULL;
    free(upword);
}

void create_database(char *buffer) {
    buffer += 9;
    createDB(buffer);
    requestSQL();
}

void create_table(char *buffer) {
    buffer += 6;
    createTable(buffer);
    requestSQL();
}

command_options cmdCreate[] = {
        {"DATABASE", create_database},
        {"TABLE",    create_table},
        {NULL, NULL}

};

void parse_create(char *buffer) {
//verifier qu'il y a au moins un mot
    // DATABASE avec 1 mot
    // TABLE nom ( col type(xx),
    // col2 type(xx)
    // )
    buffer += 7;
    parserSQL(buffer, cmdCreate);
}

void drop_database(char *buffer) {
    buffer += 9;
    dropDB(buffer);
    requestSQL();
}

void drop_table(char *buffer) {
    buffer += 6;
    dropTable(buffer);
    requestSQL();
}

command_options cmdDrop[] = {
        {"DATABASE", drop_database},
        {"TABLE",    drop_table},
        {NULL, NULL}
};

void parse_drop(char *buffer) {
    // verifier qu'il y a au moins un mot
    // DATABASE 1 mot
    // TABLE 1 mot
    buffer += 5;
    parserSQL(buffer, cmdDrop);
}

void parse_exit(char *buffer) {
    printf("Goodbye ( ^_^)／");
}

void parse_error() {
    printf("Error: Invalid Command (╯°□°）╯︵ ┻━┻");
    requestSQL();
}

command_options cmdRequest[] = {
        {"USE",    parse_use},
        {"CREATE", parse_create},
        {"DROP",   parse_drop},
        {"EXIT",   parse_exit},
        {NULL, NULL}
};
