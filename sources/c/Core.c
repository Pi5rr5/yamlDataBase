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
/*            if ((tempList = getBlockWhere("name", use, "databases.yaml")) != NULL) {
                freeListOfEntities(&tempList);
                if (!useDB(use)) {
                    printf("Error: Problem for change db use (system cmd)");
                }
            } else {
                printf("Error: Base not exist");
            }*/
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
            if (dropTable(buffer)) {
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
            if (!createTable(table)) {
                printf("Error : Can't create table on CMD");
                error = 1;
            }
        } else {
            printf("Error: Not an alpha-numeric argument");
            error = 1;
        }
        if (table != NULL) {
            free(table);
        }
        if (!error) {
            if (createQuery[0] == 40 && createQuery[strlen(createQuery) - 1] == 41) {
                createQuery[strlen(createQuery) - 1] = '\0';
                splitCreateQuery(createQuery + 1, ",");
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
        (createQuery[0] == 32) ? strcpy(name, splitWord(createQuery + 1, delim)) : strcpy(name, splitWord(createQuery,
                                                                                                          delim));
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

//********************************************************************************************
//Partie 2





void query_insert(char *buffer) {
    char name[255] = "";
    int error;
    error = 0;
    if (countArgs(buffer, " ") > 1) {
        (buffer[0] == 32) ? strcpy(name, splitWord(buffer + 1, " ")) : strcpy(name, splitWord(buffer, " "));
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
            buffer += strlen(name) + 1;
            if (!strncmp(upWord(buffer), "VALUES (", 8) && buffer[strlen(buffer) - 1] == ')') {
                buffer += 8;
                insertSqlValues(buffer);
            } else {
                printf("Error : Missing VALUES word");
            }
        }
    }
}


void insertSqlValues(char *buffer) {
    int count;
    count = 1;
    char *word;
    while (1) {
        word = insertSplit(buffer, count);
        if (word == NULL) {
            free(word);
            break;
        } else {
            if (!strcmp(word, "%%%%%")) {
                printf("Erreur");
                break;
            }
            printf("mot:%s -- type: %s \n", word, whichType(word));
            free(word);
            count++;
        }
    }

}


// UPDATE table
//SET colonne_1 = 'valeur 1', colonne_2 = 'valeur 2', colonne_3 = 'valeur 3'
//WHERE condition

void query_update(char *buffer) {
    char *table;
    int error;
    char updateQuery[512] = "";
    const char delim[2] = " ";
    error = 0;
    if (countArgs(buffer, delim) > 1) {
        table = splitWord(buffer, delim);
        if (isAlphaNum(table)) {
            strncpy(updateQuery, buffer + strlen(table) + 1, strlen(buffer) - strlen(table));
        } else {
            printf("Error: Not an alpha-numeric argument");
            error = 1;
        }
        if (table != NULL) {
            free(table);
        }
        if (!error) {
            if (!strncmp(upWord(updateQuery), "SET ", 4)) {
                valuesUpdateQuery(updateQuery + 4);
            }
        }
    } else {
        printf("Error : Not enough args");
    }
}

//update coucou set cl1 = 'k', cl2 = 9, cl3 = 'ggggg';
void valuesUpdateQuery(char *buffer) {
    char *key;
    char *value;
    int count;
    int error;
    count = 1;
    error = 0;
    while (1) {
        key = updateSplitWord(buffer, count, 1);
        if (key == NULL) {
            free(key);
            break;
        } else {
            value = updateSplitWord(buffer, count, 2);
            if (!strncmp(value, "%%%%%", 5)) {
                printf("Erreur\n");
                free(key);
                free(value);
                error = 1;
                break;
            }
            printf("key:%s -- value:%s -- type:%s\n", key, value, whichType(value));
            free(key);
            free(value);
            count++;
        }
    }
    if (!error) {
        key = updateSplitWord(buffer, 0, 3);
        value = updateSplitWord(buffer, 0, 4);
        printf("contrainte key:%s -- contrainte value:%s -- contrainte type:%s", key, value, whichType(value));
        free(key);
        free(value);
    }
}







//DELETE FROM `table`
//WHERE condition

void query_delete(char *buffer) {
    char *table;
    int error;
    char deleteQuery[512] = "";
    const char delim[2] = " ";
    error = 0;
    if (countArgs(buffer, delim) > 1) {
        table = splitWord(buffer, delim);
        if (isAlphaNum(table)) {
            strncpy(deleteQuery, buffer + strlen(table) + 1, strlen(buffer) - strlen(table));
        } else {
            printf("Error: Not an alpha-numeric argument");
            error = 1;
        }
        if (table != NULL) {
            free(table);
        }
        if (!error) {
            if (!strncmp(upWord(deleteQuery), "WHERE ", 6)) {
                condDeleteQuery(deleteQuery + 6);
            }
        }
    } else {
        printf("Error : Not enough args");
    }
}


void condDeleteQuery(char *buffer) {
    int control = 1;
    int start = 0;
    int end = 1;
    char key[255];

    printf("key:%s -- value:%s", updateSplitWord(buffer, 1, 1), updateSplitWord(buffer, 1, 2));
    /*

    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == 61 && control == 1) {
            end = (buffer[i - 1] == 32) ? end - 2 : end - 1;
            strncpy(key, buffer + start, end);
            key[end] = '\0';
            printf("key:%s -- value:%s -- type:%s\n", key, insertSplit(buffer + i + 1, 1),
                   whichType(insertSplit(buffer + i + 1, 1)));
            start = i + 1;
            end = 1;
            control = 0;
            continue;
        }
        if (buffer[i] == 44 && control == 0) {
            control = 1;
            start = (buffer[i + 1] == 32) ? i + 2 : i + 1;
            end = 1;
            continue;
        }
        end++;
    }*/

}

