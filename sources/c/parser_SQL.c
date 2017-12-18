//
// Created by Qut on 29/10/2017.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../h/struct.h"
#include "../h/some_funct.h"
#include "../h/Core.h"
#include "../h/parserYAML.h"
#include "../h/parser_SQL.h"


/**
 * Desc: List of command
 *
 */
commandSQL cmdSQL[] = {
        {"USE",             queryUse},
        {"CREATE DATABASE", queryCreateDatabase},
        {"CREATE TABLE",    queryCreateTable},
        {"DROP DATABASE",   queryDropDatabase},
        {"DROP TABLE",      queryDropTable},
        {"EXIT",            queryExit},
        {"INSERT INTO",     queryInsert},
        {"UPDATE",          queryUpdate},
        {"DELETE FROM",     queryDelete},
        {"SELECT * FROM",   querySelectAll}
};


/**
 * Desc: parse the SQL query & call functions
 *
 * Param: Char * word : String to cut & check
 *
 */
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
            lenWord = strlen(cmdSQL[loop].name) + 1;
            querySent = malloc(sizeof(char) * (lenQuery - lenWord + 1));
            strncpy(querySent, cleanQueryChar + lenWord, lenQuery - lenWord);
            querySent[lenQuery - lenWord - 1] = '\0';
            cmdSQL[loop].functionSQL(querySent);
            free(querySent);
            error = 0;
            break;
        }
    }
    error ? queryError(word) : NULL;
    free(cleanQueryChar);
    free(upWordChar);
}

// count & quit
void queryExit(char *exit) {
    printf("Goodbye ( ^_^)／");
}

void queryError(char *error) {
    printf("Error: Invalid Command (╯°□°）╯︵ ┻━┻");
}