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
    listOfEntities *tempList;

    if (countArgs(use, " ") == 1) {
        if (isAlphaNum(use)) {
            if ((tempList = getBlockWhere("name", use, "databases.yaml")) != NULL) {
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
    char createQuery[512] = "";
    const char delim[2] = " ";
    int error;
    char *table;
    error = 0;
    if (countArgs(buffer, delim) > 1) {
        table = splitWord(buffer, delim);
        if (isAlphaNum(table)) {
            strncpy(createQuery, buffer + strlen(table) + 1, strlen(buffer) - strlen(table));
/*            if (!createTable(table, "nomtable")) {
                printf("Error : Can't create table on CMD");
                error = 1;
            }*/
        } else {
            printf("Error: Not an alpha-numeric argument");
            error = 1;
        }
        if(table != NULL) {
            free(table);
        }
        if (!error) {
            if (createQuery[0] == 40 && createQuery[strlen(createQuery) - 1] == 41) {
                 createQuery[strlen(createQuery) - 1] = '\0';
                splitCreateQuery(createQuery+1, ",");
            } else {
                printf("Error : bad request");
            }
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
    char name[255] = "";
    char type[255] = "";
    char null[6];
    char auto_increment[6];
    char primary[6];
    int error = 0;
    strcpy(auto_increment, "");
    strcpy(primary, "");
    strcpy(null, "");
    if (countArgs(createQuery, " ") > 1) {
        (createQuery[0] == 32) ? strcpy(name, splitWord(createQuery+1, delim)) :  strcpy(name, splitWord(createQuery, delim));
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
            strcpy(null, checkExprSQL(createQuery, "NOT NULL"));
            strcpy(auto_increment, checkExprSQL(createQuery, "AUTO INCREMENT"));
            strcpy(primary, checkExprSQL(createQuery, "PRIMARY KEY"));
            strcpy(type, checkTypeSQL(createQuery));
            if (!type) { error = 1; }
        }
        if (!error) {
            printf("--type:%s--null:%s--auto:%s--primary:%s\n", type, null, auto_increment, primary);
        } else {
            printf("Error : No type selected");
        }
    } else {
        printf("Error : Query with too few args !");
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


