#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../h/globals.h"


/**
* Create database if not exist
* @param  : dbName
* @return : success ? 1 : 0
**/
int createDB(char *dbName) {
    if(isExist(dbName)) {
        return 0;
    }
    char cmd[100];
    strcpy(cmd, "mkdir resources\\");
    strcat(cmd, dbName);
    strcat(cmd, " >nul 2>nul");
    if(!system(cmd)){
        return 1;
    } else {
        return 0;
    }
}

/**
* Set global CURRENT_DATABASE if exist
* @param  : dbName
* @return : success ? 1 : 0
**/
int useDB(char *dbName) {
    if(isExist(dbName)) {
        CURRENT_DATABASE = dbName;
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
int createTable(char *tableName) {
    if(CURRENT_DATABASE == NULL){
        return 0;
    }
    char cmd[100];
    strcpy(cmd, "fsutil file createnew resources\\");
    strcat(cmd, CURRENT_DATABASE);
    strcat(cmd, "\\");
    strcat(cmd, tableName);
    strcat(cmd, ".yaml 0 >nul 2>nul");
    if(!system(cmd)) {
        return 1;
    } else {
        return 0;
    }
    return 1;
}


/**
* Check if exist database
* @param  : dbName
* @return : success ? 1 : 0
**/
int isExist(char *dbName) {
    if(dbName == 0 || dbName == NULL) {
        return 0;
    }
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
* Drop table if database and if exist
* @param  : tableName
* TODO add return
**/
int dropTable(char *tableName){
    if(CURRENT_DATABASE == NULL){
        return 0;
    }
    char cmd[100];
    strcpy(cmd, "resources\\");
    strcat(cmd, CURRENT_DATABASE);
    strcat(cmd, "\\");
    strcat(cmd, tableName);
    strcat(cmd, ".yaml");
    int result = remove(cmd);
    return result+1;
}

/**
* Drop database if exist
* @param  : dbName
* @return : success ? 1 : 0
**/
int dropDB(char *dbName) {
    char cmd[100];
    strcpy(cmd, "rmdir /s /q resources\\");
    strcat(cmd, dbName);
    strcat(cmd, " >nul 2>nul");
    if(!system(cmd)){
        return 1;
    } else {
        return 0;
    }
}
