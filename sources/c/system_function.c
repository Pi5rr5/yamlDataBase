#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../h/struct.h"

/**
* Create database if not exist
* @param  : dbName
* @return : success ? 1 : 0
**/
int createDB(char *dbName) {
    char cmd[100];
    strcpy(cmd, "mkdir resources\\");
    strcat(cmd, dbName);
    if(!system(cmd)){
        // call function to initiate map at the current path
        printf("> Warning function to create map not implemented !\n");
        printf("> Query OK: database '%s' created\n",dbName);
        return 1;
    } else {
        printf("> Error: database '%s' already exist !\n", dbName);
        return 0;
    }
}


/**
* Use database if exist
* @param  : dbName
* @return : success ? 1 : 0
**/
int useDB(char *dbName) {
    char cmd[100];
    strcpy(cmd, "cd resources\\");
    strcat(cmd, dbName);
    strcat(cmd, " >nul 2>nul");
    if(!system(cmd)) {
        changeDatabase(dbName);
        printf("> Database changed\n");
        return 1;
    } else {
        printf("> Error: Unknown database\n");
        return 0;
    }
}

/**
* Create table if database
* @param  : tableName
* @return : success ? 1 : 0
**/
int createTable(char *tableName) {
    if(strcmp(getCurrentDB(), "NULL") == 0) {
        printf("> Error: No database selected !\n");
        return 0;
    }
    char cmd[100];
    strcpy(cmd, "fsutil file createnew resources\\");
    //strcat(cmd, getCurrentDB());
    strcat(cmd, "\\");
    strcat(cmd, tableName);
    strcat(cmd, ".yaml 0 >nul 2>nul");
    if(!system(cmd)) {
        printf("> Query OK: table '%s' created\n", tableName);
        return 1;
    } else {
        printf("> Error: Unknown database '%s' !\n", tableName);
        return 0;
    }
}

/**
* Drop table if database and if exist
* @param  : tableName
* @return : success ? 1 : 0
**/
void dropTable(char *tableName){
    if(strcmp(getCurrentDB(), "NULL") == 0) {
        printf("> Error: No database selected !\n");
        return;
    }
    char cmd[100];
    strcpy(cmd, "DEL /P resources\\");
    //strcat(cmd, getCurrentDB());
    strcat(cmd, "\\");
    strcat(cmd, tableName);
    strcat(cmd, ".yaml");
    system(cmd);
}

/**
* Drop database if exist
* @param  : dbName
* @return : success ? 1 : 0
**/
int dropDB(char *dbName) {
    char cmd[100];
    strcpy(cmd, "rmdir /s resources\\");
    strcat(cmd, dbName);
    if(!system(cmd)){
        printf("> Query OK: drop database call '%s'\n",dbName);
        return 1;
    } else {
        printf("> Error: Can't drop inexistent database call '%s'\n",dbName);
        return 0;
    }
}
