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



/**
 * Desc: go on a db
 *
 * Param: Char *use: name of the db
 *
 */
void queryUse(char *use) {
    listOfEntities *tempList;
    if (countArgs(use, " ") == 1) {                               // check num of args (query)
        if (isAlphaNum(use)) {                                    // check if alphanum : go
            if (useDB(use)) {                                     // check is database exist then change global
                printf("Base changed for: %s",use);
            } else {
                printf("Base '%s' not found !",use);
            }
        } else {
            printf("Error: Not an alpha-numeric argument");
        }
    } else {
        printf("Error : Query with too few args");
    }
}

/**
 * Desc: create a db
 *
 * Param: Char * : name of the db
 *
 */
void queryCreateDatabase(char *buffer) {
    if (countArgs(buffer, " ") == 1) {                                                          // check num of args (query)
        if (isAlphaNum(buffer)) {                                                               // check if alphanum : go
            //if (funcyaml(buffer)) {                                                           // check if db not exist : go (YAML)
            if (createDB(buffer)) {                                                             // create file system : go (sysCMD)
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

/**
 * Desc: drop a db
 *
 * Param: Char * : name of the db
 *
 */
void queryDropDatabase(char *buffer) {
    if (countArgs(buffer, " ") == 1) {                                                          // check num of args (query)
        if (isAlphaNum(buffer)) {                                                               // check if alphanum : go
            //if (funcyaml(buffer)) {                                                           // check if db drop : go (YAML)
            if (dropDB(buffer)) {                                                               // check if db drop : go (sysCMD)
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

/**
 * Desc: drop a table
 *
 * Param: Char * : name of the table
 *
 */
void queryDropTable(char *buffer) {
    if (countArgs(buffer, " ") == 1) {                                                          // check num of args (query)
        if (isAlphaNum(buffer)) {                                                               // check if alphanum : go
            //if (funcyaml(buffer)) {                                                           // check if table drop (erase table info in db struct) (YAML)
            if (dropTable(buffer)) {                                                            // check if table drop (sysCMD)
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

/**
 * Desc: create a table
 *
 * Param: Char * : query
 *
 */
void queryCreateTable(char *buffer) {       // CREATE TABLE name ( cl1 type1 type2, cl2 type1 type2 type3);
    char createQuery[MAX] = "";
    const char delim[2] = " ";
    int error;
    char *table;
    error = 0;
    if (countArgs(buffer, delim) > 1) {                                                              // check num of args (query)
        table = splitWord(buffer, delim);                                                            // split query and take the first word (table)
        if (isAlphaNum(table)) {                                                                     // check if alphanum : go
            strncpy(createQuery, buffer + strlen(table) + 1, strlen(buffer) - strlen(table));        // alter query and begin after table name (+1 count the space after name)
            if (!createTable(table)) {                                                               // check if table create : go (sysCMD)
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
            if (createQuery[0] == 40 && createQuery[strlen(createQuery) - 1] == 41) {                // if rest of the query start with ( and end with ) : go
                createQuery[strlen(createQuery) - 1] = '\0';                                         // remove the )
                splitCreateQuery(createQuery + 1, ",");                                              // split the query with , delimiter
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
void splitCreateQuery(char *createQuery, const char *delim) {               // cl1 type1 type2   // cl2 type1 type2 type3
    char *token;
    token = strtok1(createQuery, delim);
    while (token != NULL) {
        goSplitCreateQuery(token, " ");                                                             // split the string with space delimiter
        token = strtok1(NULL, delim);
    }
}

/**
 * Desc: check & call function for insert into YAML files
 *
 * Param: Char * word : String to check
 *
 */
void goSplitCreateQuery(char *createQuery, const char *delim) {             // cl1 // type // type2
    char name[MAX] = "";
    char type[MAX] = "";
    char null[6];
    char auto_increment[6];
    char primary[6];
    int error = 0;
    strcpy(auto_increment, "");
    strcpy(primary, "");
    strcpy(null, "");
    if (countArgs(createQuery, " ") > 1) {                                                                                                // check num of args : go
        (createQuery[0] == 32) ? strcpy(name, splitWord(createQuery + 1, delim)) : strcpy(name, splitWord(createQuery,
                                                                                                          delim));                        // take the name of column (without space)
        if (correctWord(name)) {                                                                                                          // check if name of column is correct : go
            if (!isAlphaNum(name)) {                                                                                                      // check if name if alphanum : go
                printf("Error: Not an alpha-numeric argument(blop)\n");
                error = 1;
            }
        } else {
            printf("Error: Use of a forbidden word");
            error = 1;
        }
        if (!error) {
            strcpy(null, checkExprSQL(createQuery, "NOT NULL"));                                                                          // check if NOT NULL is an arg
            strcpy(auto_increment, checkExprSQL(createQuery, "AUTO INCREMENT"));                                                          // check if AUTO INC is an arg
            strcpy(primary, checkExprSQL(createQuery, "PRIMARY KEY"));                                                                    // check if PK is an arg
            strcpy(type, checkTypeSQL(createQuery));                                                                                      // check if type is correct & the type
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


/**
 * Desc: Recopy of strtok because 2 strtok cant be use in the same time (static...)
 *
 */
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




/**
 * Desc: Insert function
 *
 * Param: Char * word : query
 *
 */
void queryInsert(char *buffer) {
    char name[MAX] = "";
    int error;
    error = 0;
    if (countArgs(buffer, " ") > 1) {                                                                                       // check num of args : go
        (buffer[0] == 32) ? strcpy(name, splitWord(buffer + 1, " ")) : strcpy(name, splitWord(buffer, " "));                // take the name of column (without space)
        if (correctWord(name)) {                                                                                            // check if name of column is correct : go
            if (!isAlphaNum(name)) {                                                                                        // check if name if alphanum : go
                printf("Error: Not an alpha-numeric argument(blop)\n");
                error = 1;
            }
        } else {
            printf("Error: Use of a forbidden word");
            error = 1;
        }
        if (!error) {
            buffer += strlen(name) + 1;                                                                                     // alter query and begin after table name (+1 count the space after name)
            if (!strncmp(upWord(buffer), "VALUES (", 8) && buffer[strlen(buffer) - 1] == ')') {                             // check if values ( is present : go
                buffer += 8;
                insertSqlValues(buffer);
            } else {
                printf("Error : Missing VALUES word");
            }
        }
    }
}


void insertSqlValues(char *buffer) {            //
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

void queryUpdate(char *buffer) {
    char *table;
    int error;
    char updateQuery[MAX] = "";
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

void queryDelete(char *buffer) {
    char *table;
    int error;
    char deleteQuery[MAX] = "";
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

    printf("key:%s -- value:%s", updateSplitWord(buffer, 1, 1), updateSplitWord(buffer, 1, 2));

}

