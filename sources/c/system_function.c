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
        return 1;
    } else {
        return 0;
    }
}

/**
* Check if exist database
* @param  : dbName
* @return : success ? 1 : 0
**/
int isExist(char *dbName) {
    char cmd[100];
    strcpy(cmd, "cd resources\\");
    strcat(cmd, dbName);
    strcat(cmd, " >nul 2>nul");
    if(!system(cmd)) {
        return 1;
    }
    return 0;
}

/**
* Create table if database
* @param  : tableName
* @return : success ? 1 : 0
* TODO use the current database instead using parameter
**/
int createTable(char *tableName,char *dbName) {
    char cmd[100];
    strcpy(cmd, "fsutil file createnew resources\\");
    strcat(cmd, dbName);
    strcat(cmd, "\\");
    strcat(cmd, tableName);
    strcat(cmd, ".yaml 0 >nul 2>nul");
    if(!system(cmd)) {
        return 1;
    } else {
        return 0;
    }
}

/**
* Drop table if database and if exist
* @param  : tableName
* TODO add return
**/
int dropTable(char *tableName, char *dbName){
    char cmd[100];
    strcpy(cmd, "DEL /P resources\\");
    strcat(cmd, dbName);
    strcat(cmd, "\\");
    strcat(cmd, tableName);
    strcat(cmd, ".yaml");
    system(cmd);
    return 1;
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
    strcat(cmd, " >nul 2>nul");
    if(!system(cmd)){
        return 1;
    } else {
        return 0;
    }
}
