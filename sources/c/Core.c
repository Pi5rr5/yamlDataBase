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
#include "../h/funcSQLtoYAML.h"

/**
 * Desc: go on a db
 *
 * Param: Char *use: name of the db
 *
 */
void queryUse(char *use) {
    if (countArgs(use, " ") == 1) {                               // check num of args (query)
        if (isAlphaNum(use)) {                                    // check if alphanum : go
            if (useDB(use)) {                                     // check is database exist then change global
                printf("Base changed for: %s", use);
            } else {
                printf("Base '%s' not found !", use);
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
    if (countArgs(buffer, " ") ==
        1) {                                                          // check num of args (query)
        if (isAlphaNum(
                buffer)) {                                                           // check if db not exist : go (YAML)
            if (createDB(
                    buffer)) {                                                             // create file system : go (sysCMD)
                printf("Query : Database created");
            } else {
                printf("Error : Can't create database on CMD");
            }
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
    if (countArgs(buffer, " ") ==
        1) {                                                          // check num of args (query)
        if (isAlphaNum(
                buffer)) {                                                               // check if alphanum : go
            if (dropDB(
                    buffer)) {                                                               // check if db drop : go (sysCMD)
                printf("Query : Database dropped");
            } else {
                printf("Error : Can't drop database on CMD");
            }
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
    if (countArgs(buffer, " ") ==
        1) {                                                          // check num of args (query)
        if (isAlphaNum(
                buffer)) {                                                               // check if alphanum : go
            //if (funcyaml(buffer)) {                                                           // check if table drop (erase table info in db struct) (YAML)
            if (dropTable(
                    buffer)) {                                                            // check if table drop (sysCMD)
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
    if (countArgs(buffer, delim) >
        1) {                                                              // check num of args (query)
        table = splitWord(buffer,
                          delim);                                                            // split query and take the first word (table)
        if (isAlphaNum(
                table)) {                                                                     // check if alphanum : go
            strncpy(createQuery, buffer + strlen(table) + 1, strlen(buffer) -
                                                             strlen(table));        // alter query and begin after table name (+1 count the space after name)
            if (!createTable(
                    table)) {                                                               // check if table create : go (sysCMD)
                printf("Error : Can't create table on CMD");
                error = 1;
            }
        } else {
            printf("Error: Not an alpha-numeric argument");
            error = 1;
        }

        if (!error) {
            if (createQuery[0] == 40 && createQuery[strlen(createQuery) - 1] ==
                                        41) {                // if rest of the query start with ( and end with ) : go
                createQuery[strlen(createQuery) - 1] = '\0';                                         // remove the )
                splitCreateQuery(createQuery + 1, ",",
                                 table);                                              // split the query with , delimiter
				printf("Query : table created");
            } else {
                printf("Error : bad request");
            }
        }
    } else {
        printf("Error : Not enough args");
    }
    if (table != NULL) {
        free(table);
    }
}

/**
 * Desc: split each column of Query Create
 *
 * Param: Char * word : String to split
 *
 */
void
splitCreateQuery(char *createQuery, const char *delim,
                 char *name) {               // cl1 type1 type2   // cl2 type1 type2 type3
    char *token;
    token = strtok1(createQuery, delim);
    while (token != NULL) {
        goSplitCreateQuery(token, " ",
                           name);                                                             // split the string with space delimiter
        token = strtok1(NULL, delim);
    }
}

/**
 * Desc: check & call function for insert into YAML files
 *
 * Param: Char * word : String to check
 *
 */
void goSplitCreateQuery(char *createQuery, const char *delim, char *tablename) {             // cl1 // type // type2
    char name[MAX] = "";
    char type[MAX] = "";
    char null[6];
    char auto_increment[6];
    char primary[6];
    int error = 0;
    strcpy(auto_increment, "");
    strcpy(primary, "");
    strcpy(null, "");
    if (countArgs(createQuery, " ") >
        1) {                                                                                                // check num of args : go
        (createQuery[0] == 32) ? strcpy(name, splitWord(createQuery + 1, delim)) : strcpy(name, splitWord(createQuery,
                                                                                                          delim));                        // take the name of column (without space)
        if (correctWord(
                name)) {                                                                                                          // check if name of column is correct : go
            if (!isAlphaNum(
                    name)) {                                                                                                      // check if name if alphanum : go
                printf("Error: Not an alpha-numeric argument(blop)\n");
                error = 1;
            }
        } else {
            printf("Error: Use of a forbidden word");
            error = 1;
        }
        if (!error) {
            strcpy(null, checkExprSQL(createQuery,
                                      "NOT NULL"));                                                                          // check if NOT NULL is an arg
            strcpy(auto_increment, checkExprSQL(createQuery,
                                                "AUTO INCREMENT"));                                                          // check if AUTO INC is an arg
            strcpy(primary, checkExprSQL(createQuery,
                                         "PRIMARY KEY"));                                                                    // check if PK is an arg
            strcpy(type, checkTypeSQL(
                    createQuery));
            // si false = error;// check if type is correct & the type
            if (!type) { error = 1; }
        }
        if (!error) {
            createSQLtoYAML(name, type, null, primary, tablename);
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


void insertSqlValues(char *buffer, char *tablename) {
    int count;
    char *word;
    char path[MAX];
    char column[MAX];
    lineStruct templine;
    listOfLines *insertlines;
    listOfEntities *allstruct;

    count = 1;
    insertlines = NULL;

    sprintf(path, "resources\\%s\\%s\\structure.yaml", CURRENT_DATABASE, tablename);
    allstruct = getAllFrom(path);


    while (1) {
        if ( (word = insertSplit(buffer, count)) == NULL) {
            if (allstruct != NULL) {
                printf("Error");
                freeListOfLines(&insertlines);
            }
            break;
        } else {
            strcpy(column, allstruct->entity->line.value);
            allstruct->entity = allstruct->entity->next;
            if (!strcmp(whichType(word), allstruct->entity->line.value)) {
                strcpy(templine.key, column);
                strcpy(templine.value, word);
                insertlines = addLineToList(insertlines, templine);
            } else {
                printf("Error : Wrong type (%s) ", word);
                freeListOfLines(&insertlines);
                break;
            }
            allstruct = allstruct->next;
            free(word);
            count++;
        }
    }
    if (insertlines != NULL) {
        sprintf(path, "resources\\%s\\%s\\data.yaml", CURRENT_DATABASE, tablename);
        insertEntity(insertlines, path);
        freeListOfLines(&insertlines);
    }
}



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
                buffer[strlen(buffer) - 1] = '\0';
                insertSqlValues(buffer, name);
            } else {
                printf("Error : Missing VALUES word");
            }
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

        if (!error) {
            if (!strncmp(upWord(updateQuery), "SET ", 4)) {
                valuesUpdateQuery(updateQuery + 4, table);
            }
        }
    } else {
        printf("Error : Not enough args");
    }
    if (table != NULL) {
        free(table);
    }
}

//update coucou set cl1 = 'k', cl2 = 9, cl3 = 'ggggg';
void valuesUpdateQuery(char *buffer, char *tablename) {
    int i;
    char key[MAX];
    char value[MAX];
    char path[MAX] = {'\0'};
    AoS tabKeysToUpdate;
    AoS tabNewValues;
    AoS tabConstraintKey;
    AoS tabConstraintValue;
    AoS tabCompare;
    int count;
    int error;
    count = 1;
    error = 0;
    sprintf(path, "resources\\%s\\%s\\data.yaml", CURRENT_DATABASE, tablename);
    printf("The path : %s\n", path);
    while (1) {
        if( strcpy(key, updateSplitWord(buffer, count, 1)) == NULL) {
			printf("break1\n");
            break;
        } else {
            if ( strcpy(value, updateSplitWord(buffer, count, 2)) == NULL) {
                printf("Erreur\n");
                free(key);
                free(value);
                error = 1;
                break;
            }
            if (count == 1) {
				printf("creating...\n");
                tabKeysToUpdate = createArrayOfStrings(1);
                tabNewValues = createArrayOfStrings(1);
				printf("done\n");
            } else {
				printf("updating...\n");
                tabKeysToUpdate = updateArrayOfStrings(tabKeysToUpdate, 1);
                tabNewValues = updateArrayOfStrings(tabNewValues, 1);
				printf("done\n");
            }
            printf("copying %s\n", key);
            if(tabKeysToUpdate.array == NULL)
				printf("	NANI\n");
            strcpy(tabKeysToUpdate.array[count], key);
            printf("copying %s\n", value);
            strcpy(tabNewValues.array[count], value);
            count++;
        }
    }
    if (!error) {
        if (strcpy(key, updateSplitWord(buffer, 0, 3)) == NULL) {
            tabCompare = createArrayOfStrings(count);
            for (i = 0; i < count; i++) {
                strcpy(tabCompare.array[i], "<>");
            }
            updateValuesWhere(tabKeysToUpdate, tabCompare, tabNewValues, tabKeysToUpdate, tabNewValues, path);
        } else {
			strcpy(value, updateSplitWord(buffer, 0, 4));
            tabCompare = createArrayOfStrings(1);
            tabConstraintKey = createArrayOfStrings(1);
            tabConstraintValue = createArrayOfStrings(1);
            strcpy(tabCompare.array[0], "=");
            strcpy(tabConstraintKey.array[0], key);
            strcpy(tabConstraintValue.array[0], value);
            updateValuesWhere(tabConstraintKey, tabCompare, tabConstraintValue, tabKeysToUpdate, tabNewValues, path);
        }
        freeArrayOfStrings(&tabCompare);
        freeArrayOfStrings(&tabConstraintKey);
        freeArrayOfStrings(&tabConstraintValue);
        freeArrayOfStrings(&tabKeysToUpdate);
        freeArrayOfStrings(&tabNewValues);
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

