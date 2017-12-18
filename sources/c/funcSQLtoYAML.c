//
// Created by Qut on 17/12/2017.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../h/globals.h"
#include "../h/struct.h"
#include "../h/some_funct.h"
#include "../h/parserYAML.h"
#include "../h/funcSQLtoYAML.h"


int createSQLtoYAML(char *name, char *type, char *null, char *primary, char *tablename) {
    listOfLines *column;
    lineStruct line;
    char table[MAX] = {'\0'};
    column = NULL;
    strcpy(line.key, "name");
    strcpy(line.value, name);
    column = addLineToList(column, line);
    strcpy(line.key, "type");
    strcpy(line.value, type);
    column = addLineToList(column, line);
    strcpy(line.key, "null");
    strcpy(line.value, null);
    column = addLineToList(column, line);
    strcpy(line.key, "primary");
    strcpy(line.value, primary);
    column = addLineToList(column, line);
    sprintf(table, "resources\\%s\\%s\\structure.yaml", CURRENT_DATABASE, tablename);
    if (insertEntity(column, table)) {
        freeListOfLines(&column);
        return 1;
    } else {
        freeListOfLines(&column);
        return 0;
    }
}


