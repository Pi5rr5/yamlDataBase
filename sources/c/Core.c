//
// Created by Qut on 12/11/2017.
//

#include "../h/Core.h"
#include <stdio.h>
#include "../h/some_funct.h"


// CORE prgm appel parser, renvoi à interpreteur

void query_use(char *use) {
    //verifier nombre d'arg
    if (countArgs(use, (char) " ") == 1) {
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
    }
}


void query_create_database(char *buffer) {
    if (countArgs(buffer, (char) " ") == 1) {
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
    }
}


void query_drop_database(char *buffer) {
    if (countArgs(buffer, (char) " ") == 1) {
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
    }
}


void query_drop_table(char *buffer) {
    if (countArgs(buffer, (char) " ") == 1) {
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
    }
}