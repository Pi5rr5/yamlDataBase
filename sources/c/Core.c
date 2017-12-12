//
// Created by Qut on 12/11/2017.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../h/Core.h"
#include "../h/struct.h"
#include "../h/some_funct.h"
#include "../h/parserYAML.h"
#include "../h/system_function.h"

// CORE prgm appel parser, renvoi à interpreteur


void query_use(char *use) {
	listOfEntities* tempList;

    if (countArgs(use, " ") == 1) {
        if (isAlphaNum(use)) {
            if ( (tempList = getBlockWhere("name", use, "databases.yaml")) != NULL) {
				freeListOfEntities(&tempList);
                /*if (!useDB(use)) {
                    printf("Error: Problem for change db use (system cmd)");
                }*/
            } else {
                printf("Error: Base not exist");
            }
        } else {
            printf("Error: Not an alpha-numeric argument");
        }
    } else {
        printf("Error : Query with too few args");
    }
}


void query_create_database(char *buffer) {
    if (countArgs(buffer, " ") == 1) {
        if (isAlphaNum(buffer)) {
            //if (funcyaml(buffer)) {
                if (createDB(buffer)) {
                    printf("Query : Database created");
                } else {
                    printf("Error : Can't create database on CMD");
                }
            /*} else {
                printf("Error : Can't create database on YAML");
            }*/
        } else {
            printf("Error: Not an alpha-numeric argument");
        }
    } else {
        printf("Error : Query with too few args");
    }
}


void query_drop_database(char *buffer) {
    if (countArgs(buffer, " ") == 1) {
        if (isAlphaNum(buffer)) {
            //if (funcyaml(buffer)) {
                if (dropDB(buffer)) {
                    printf("Query : Database dropped");
                } else {
                    printf("Error : Can't drop database on CMD");
                }
            /*} else {
                printf("Error : Can't drop database on YAML");
            }*/
        } else {
            printf("Error: Not an alpha-numeric argument");
        }
    } else {
        printf("Error : Query with too few args");
    }
}


void query_drop_table(char *buffer) {
    if (countArgs(buffer, " ") == 1) {
        if (isAlphaNum(buffer)) {
            //if (funcyaml(buffer)) {
                if (dropTable(buffer, "nomtable")) {
                    printf("Query : Table dropped");
                } else {
                    printf("Error : Can't drop table on CMD");
                }
            /*} else {
                printf("Error : Can't drop table on YAML");
            }*/
        } else {
            printf("Error: Not an alpha-numeric argument");
        }
    } else {
        printf("Error : Query with too few args");
    }
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
             if (!createTable(table, "nomtable")) {
                 printf("Error : Can't create table on CMD");
                 error = 1;
             }
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
    token = strtok1(createQuery, delim);
    while (token != NULL) {
        goSplitCreateQuery(token, " ");
        token = strtok1(NULL, delim);
    }
}

/**
 * Desc: check & call function for insert into YAML files
 *
 * Param: Char * word : String to check
 *
 */
void goSplitCreateQuery(char *createQuery, const char *delim) {
    char *token1;
    char *name;
    char *type;
    char *checknull;
    char *null;
    char *checkauto;
    char *auto_increment;
    char *checkprimary;
    char *primary;
    int error = 0;
    if (countArgs(createQuery, " ") > 1) {
        char *name = splitWord(createQuery, " ");
        if (correctWord(name)) {
            if (!isAlphaNum(name)) {
                printf("Error: Not an alpha-numeric argument(blop)\n");
                error = 1;
            }
        } else {
            printf("Error: Use of a forbidden word");
            error = 1;
        }
        if (!error) {
            type = malloc(sizeof(char) * 20);
            type = strstr(upWord(createQuery), "INT");
            if (!type) {
                type = strstr(upWord(createQuery), "VARCHAR");
                if (!type) {
                    type = strstr(upWord(createQuery), "CHAR");
                    if (!type) {
                        type = strstr(upWord(createQuery), "FLOAT");
                        if (!type) {
                            error = 1;
                        } else {
                            type[5] = '\0';
                        }
                    } else { type[5] = '\0'; }
                } else { type[8] = '\0'; }
            } else { type[3] = '\0'; }
            checknull = malloc(sizeof(char) * 20);
            checknull = strstr(upWord(createQuery), "NOT NULL");
            if (checknull) {
                null = malloc(sizeof(char) * 4);
                strcpy(null, "true");
                null[4] = '\0';
            } else {
                null = malloc(sizeof(char) * 5);
                strcpy(null, "false");
                null[5] = '\0';
            }
            checkauto = malloc(sizeof(char) * 20);
            checkauto = strstr(upWord(createQuery), "AUTO INCREMENT");
            if (checkauto) {
                auto_increment = malloc(sizeof(char) * 4);
                strcpy(auto_increment, "true");
                auto_increment[4] = '\0';
            } else {
                auto_increment = malloc(sizeof(char) * 5);
                strcpy(auto_increment, "false");
                auto_increment[5] = '\0';
            }
            checkprimary = malloc(sizeof(char) * 20);
            checkprimary = strstr(upWord(createQuery), "PRIMARY KEY");
            if (checkprimary) {
                primary = malloc(sizeof(char) * 4);
                strcpy(primary, "true");
                primary[4] = '\0';
            } else {
                primary = malloc(sizeof(char) * 5);
                strcpy(primary, "false");
                primary[5] = '\0';
            }

        }
        if(!error) {
            printf("--type:%s--null:%s--auto:%s--primary:%s\n", type, null, auto_increment, primary);
        } else {
            printf("Error : No type selected");
        }
/*        createQuery += strlen(name);
        token1 = strtok(createQuery, delim);

        // recherche de param;
        while (token1 != NULL) {
            // recherche de mot ok;

            token1 = strtok(NULL, delim);
        }*/
    } else {
        printf("Error : Query with too few args");
    }

}


// à expliquer
char *strtok1(char *s, const char *delim) {
    static char *lasts;
    register int ch;

    if (s == 0)
        s = lasts;
    do {
        if ((ch = *s++) == '\0')
            return 0;
    } while (strchr(delim, ch));
    --s;
    lasts = s + strcspn(s, delim);
    if (*lasts != 0)
        *lasts++ = 0;
    return s;
}


