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
                if (funcsys(buffer)) {
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
                if (funcsys(buffer)) {
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
                if (funcsys(buffer)) {
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
    const char delim[2] = " ";
    char *delim1 = " ";
    int error;
    error = 0;
    if (countArgs(buffer, delim) > 1) {
        char *table = splitWord(buffer, delim1);
        if(isAlphaNum(table)) {
            if(funcsys(table)) {

            } else {
                printf("Error : Can't create table on CMD");
               error = 1;
            }
        } else {
            printf("Error: Not an alpha-numeric argument");
         error = 1;
        }
       free(table);
        if(!error) {
            //continue
        }
    }

}