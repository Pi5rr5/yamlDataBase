//
// Created by Qut on 29/10/2017.
//
#include "../h/parser_SQL.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../h/some_funct.h"
#include "../h/Core.h"



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
    int lenQuery;
    int lenWord;
    char *cleanQueryChar;
    char *upWordChar;
    char *querySent;
    error = 1;
    cleanQueryChar = cleanQuery(word);
    upWordChar = upWord(cleanQueryChar);
    for (loop = 0; cmdSQL[loop].name; loop++) {
        if (!strncmp(upWordChar, cmdSQL[loop].name, strlen(cmdSQL[loop].name))) {
            lenQuery = strlen(cleanQueryChar);
            lenWord = strlen(cmdSQL[loop].name) +1;
            querySent = malloc(sizeof(char) * (lenQuery - lenWord));
            strncpy(querySent, cleanQueryChar + lenWord, lenQuery - lenWord - 1);
            cmdSQL[loop].functionSQL(querySent);
            free(querySent);
            error = 0;
            break;
        }
    }
    error ? query_error(word) : NULL;
    free(cleanQueryChar);
    free(upWordChar);
}



void query_exit(char *exit) {
    printf("Goodbye ( ^_^)／");
}

void query_error(char *error) {
    printf("Error: Invalid Command (╯°□°）╯︵ ┻━┻");
}






















/*int
float
char
string*/


/*CREATE TABLE MyGuests (
        id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
        firstname VARCHAR(30) NOT NULL,
lastname VARCHAR(30) NOT NULL,
email VARCHAR(50),
        reg_date TIMESTAMP
)*/


