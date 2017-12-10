//
// Created by Qut on 12/11/2017.
//

#include "../h/Core.h"
#include <stdio.h>
#include "../h/some_funct.h"
#include <string.h>
#include <stdlib.h>

// CORE prgm appel parser, renvoi à interpreteur



void query_use(char *use) {
/*    if (countArgs(use, (char) " ") == 1) {
        if (isAlphaNum(use)) {
            if (getBlockWhere("name", use, "databases.yaml") != NULL) {
                if (useDB(use)) {
                    changeDatabase(dbName);
                } else {
                    printf("Error: Problem for change db use (system cmd)");
                }
            } else {
                printf("Error: Base not exist");
            }
        } else {
            printf("Error: Not an alpha-numeric argument");
        }
    } else {
        printf("Error : Query with too few args");
    }*/
}


void query_create_database(char *buffer) {
/*    if (countArgs(buffer, (char) " ") == 1) {
        if (isAlphaNum(buffer)) {
            if (funcyaml(buffer)) {
                if (createDB(buffer)) {
                    printf("Query : Database created");
                } else {
                    printf("Error : Can't create database on CMD");
                }
            } else {
                printf("Error : Can't create database on YAML");
            }
        } else {
            printf("Error: Not an alpha-numeric argument");
        }
    } else {
        printf("Error : Query with too few args");
    }*/
}


void query_drop_database(char *buffer) {
/*    if (countArgs(buffer, (char) " ") == 1) {
        if (isAlphaNum(buffer)) {
            if (funcyaml(buffer)) {
                if (dropDB(buffer)) {
                    printf("Query : Database dropped");
                } else {
                    printf("Error : Can't drop database on CMD");
                }
            } else {
                printf("Error : Can't drop database on YAML");
            }
        } else {
            printf("Error: Not an alpha-numeric argument");
        }
    } else {
        printf("Error : Query with too few args");
    }*/
}


void query_drop_table(char *buffer) {
/*    if (countArgs(buffer, (char) " ") == 1) {
        if (isAlphaNum(buffer)) {
            if (funcyaml(buffer)) {
                if (dropTable(buffer)) {
                    printf("Query : Table dropped");
                } else {
                    printf("Error : Can't drop table on CMD");
                }
            } else {
                printf("Error : Can't drop table on YAML");
            }
        } else {
            printf("Error: Not an alpha-numeric argument");
        }
    } else {
        printf("Error : Query with too few args");
    }*/
}

void query_create_table(char *buffer) {
    char *createQuery;
    const char delim[2] = " ";
    char *delim1 = " ";
    int error;
    char *table;
    error = 0;
    if (countArgs(buffer, delim) > 1) {
        table = splitWord(buffer, delim1);
        if (isAlphaNum(table)) {
            createQuery = malloc(sizeof(char) * (strlen(buffer) - strlen(table) + 1));
            strncpy(createQuery, buffer + strlen(table) + 1, strlen(buffer) - strlen(table));
            /* if (!createTable(table)) {
                 printf("Error : Can't create table on CMD");
                 error = 1;
             }*/
        } else {
            printf("Error: Not an alpha-numeric argument");
            error = 1;
        }
        free(table);
        if (!error) {
            splitCreateQuery(createQuery, ",");
            free(createQuery);
        }
    } else {
        printf("Error : Not enough args");
    }

}

/**
 * Desc: split each column of Query Create
 *
 * Param: Char * word : String to split
 *
 */
void splitCreateQuery(char *createQuery, const char *delim) {
    char *token;
    token = strtok(createQuery, delim);
    while (token != NULL) {
        printf("colonne:%s\n", token);
        GoSplitCreateQuery(token, " ");
        token = strtok(NULL, delim);
    }


}

/**
 * Desc: check & call function for insert into YAML files
 *
 * Param: Char * word : String to check
 *
 */
void GoSplitCreateQuery(char *createQuery, const char *delim) {
    printf("%s\n", createQuery);
    char *token;
    char *name;
    char *type;
    char *null = "true";
    char *auto_increment = "false";
    char *primary = "false";
    int count = 1;
    if (countArgs(createQuery, " ") > 1) {
        token = strtok(createQuery, delim);
        while (token != NULL) {
            if (count == 1) {
                if (correctWord(token)) {
                    printf("(-)%s\n", token);
                    if (isAlphaNum(token)) {
                        name = malloc(sizeof(char) * strlen(token));
                        strcpy(name, token);
                    } else {
                        printf("Error: Not an alpha-numeric argument(blop)\n");
                    }
                } else {
                    printf("Error: Use of a forbidden word");
                }
                count++;
            } else {
                // au dessus de 1
                //vérifier les termes
            }
            token = strtok(NULL, delim);
        }
    } else {
        printf("Error : Query with too few args");
    }
    printf("------>%s\n", name);
}


