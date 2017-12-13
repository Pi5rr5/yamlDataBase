//
// Created by Qut on 29/10/2017.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../h/struct.h"
#include "../h/some_funct.h"
#include "../h/parserYAML.h"
#include "../h/parser_SQL.h"



// interpreteur SQL détection mot clé, récurcivité, renvoi fonction


commandSQL cmdSQL[] = {
        {"USE",             query_use},
        {"CREATE DATABASE", query_create_database},
        {"CREATE TABLE",    query_create_table},
        {"DROP DATABASE",   query_drop_database},
        {"DROP TABLE",      query_drop_table},
        {"EXIT;",           query_exit},
        {NULL, NULL}
};

void parserSQL(char *word) {
    int error;
    int loop;
    char *cleanquery;
    char *upword;
    error = 1;
    cleanquery = cleanQuery(word);
    upword = upWord(cleanquery);
    printf("%s\n", upword);
    for (loop = 0; cmdSQL[loop].name; loop++) {
        if (!strncmp(upword, cmdSQL[loop].name, strlen(cmdSQL[loop].name))) {
            cmdSQL[loop].functionSQL(upword);
            error = 0;
            break;
        }
    }
    error ? query_error(word) : NULL;
    free(cleanquery);
    free(upword);
}


//***********************************************
// parse command
//***********************************************
void query_use(char *buffer) {
    // vérif à faire
    printf("parse_use: %s", buffer);
}

void query_exit(char *exit) {
    // vérifier qu'il n'y a rien d'autre ensuite
    printf("Goodbye ( ^_^)／");
}

void query_error(char *error) {
    printf("Error: Invalid Command (╯°□°）╯︵ ┻━┻");
}
//***********************************************


//***********************************************
// Parse create
//***********************************************
void query_create_database(char *buffer) {
    // verif à faire
    printf("parse_create_database: %s", buffer);
}

void query_create_table(char *buffer) {
    printf("parse_create_table: %s", buffer);
}
//***********************************************


//***********************************************
// Parse drop
//***********************************************
void query_drop_database(char *buffer) {
    // vérif à faire
    printf("parse_drop_database: %s", buffer);
}

void query_drop_table(char *buffer) {
    printf("parse_drop_table: %s", buffer);
}
//***********************************************
