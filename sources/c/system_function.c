#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../h/globals.h"
#include "../h/system_function.h"


/**
* Create database if not exist
* @param  : dbName
* @return : success ? 1 : 0
**/
int createDB(char *dbName) {
    if(isExist(dbName)) {
        return 0;
    }
    char cmd[255];
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
* Create folder table and data/structure.yaml inside if CURRENT_DATABASE
* @param  : tableName
* @return : success ? 1 : 0
**/
int createTable(char *tableName) {
    if(CURRENT_DATABASE == NULL)
        return 0;
    char cmd[255];
    char path[255];
    // concatenate neutral path
    strcpy(path, "resources\\");
    strcat(path, CURRENT_DATABASE);
    strcat(path, "\\");
    strcat(path, tableName);
    // create table folder
    strcpy(cmd, "mkdir ");
    strcat(cmd, path);
    strcat(cmd, " >nul 2>nul");
    if(system(cmd))
        return 0;
    // create data.yaml file
    if(createEmptyFile(path, "\\data.yaml")) {
        if(!initYamlFile(path))
            return 0;
        // truncate path
        path[strlen(path) - 9] = 0;
        // create structure.yaml file
        if(createEmptyFile(path, "structure.yaml"))
            if(!initYamlFile(path))
                return 0;
    }
    return 1;
}

/**
* Create empty file
* @param  : path
* @return : success ? 1 : 0
**/
int createEmptyFile(char *path, char *fileName) {
    char cmd[255];
    strcpy(cmd, "fsutil file createnew ");
    strcat(path, fileName);
    strcat(cmd, path);
    strcat(cmd, " 0 >nul 2>nul");
    return !system(cmd);
}

/**
* Initiate yaml file
* @param  : tableName, path
* @return : success ? 1 : 0
**/
int initYamlFile(char *path) {
    FILE* f;
    f = fopen(path, "r+");
    if(f != NULL)
        if(fprintf(f,"# yaml file\n# path: %s\n---\n...\n",path) <= 0) {
            fclose(f);
            return 0;
        }
    fclose(f);
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
    char cmd[255];
    strcpy(cmd, "cd resources\\");
    strcat(cmd, dbName);
    strcat(cmd, " >nul 2>nul");
    if(!system(cmd)) {
        return 1;
    }
    return 0;
}

/**
* Drop table if CURRENT_DATABASE and if exist
* @param  : tableName
* TODO add return
**/
int dropTable(char *tableName){
    if(CURRENT_DATABASE == NULL){
        return 0;
    }
    char cmd[255];
    strcpy(cmd, "rmdir /s /q resources\\");
    strcat(cmd, CURRENT_DATABASE);
    strcat(cmd, "\\");
    strcat(cmd, tableName);
    strcat(cmd, " >nul 2>nul");
    if(!system(cmd)){
        return 1;
    } else {
        return 0;
    }
}

/**
* Drop database if exist
* @param  : dbName
* @return : success ? 1 : 0
**/
int dropDB(char *dbName) {
    char cmd[255];
    strcpy(cmd, "rmdir /s /q resources\\");
    strcat(cmd, dbName);
    strcat(cmd, " >nul 2>nul");
    if(!system(cmd)){
        return 1;
    } else {
        return 0;
    }
}
