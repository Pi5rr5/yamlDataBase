//
// Created by Qut on 12/11/2017.
//

#ifndef YAMLDATABASE_CORE_H
#define YAMLDATABASE_CORE_H

void queryUse(char *);

void queryCreateDatabase(char *);

void queryDropDatabase(char *);

void queryDropTable(char *);

void queryCreateTable(char *);

void queryInsert(char *);

void queryUpdate(char *);

void queryDelete(char *);

void insertSqlValues(char*, char*);

void splitCreateQuery(char *, const char *, char *);

void goSplitCreateQuery(char *, const char *, char *);

char *strtok1(char *, const char *);

void valuesUpdateQuery(char *, char *);

void condDeleteQuery(char *);

#endif //YAMLDATABASE_CORE_H
