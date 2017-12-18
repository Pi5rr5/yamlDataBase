//
// Created by Qut on 17/12/2017.
//

#ifndef YAMLDATABASE_FUNCSQLTOYAML_H
#define YAMLDATABASE_FUNCSQLTOYAML_H

#ifndef MAX
#define MAX 255
#endif // MAX

extern char CURRENT_DATABASE[MAX];

int createSQLtoYAML(char *, char *, char *, char *, char*);

#endif //YAMLDATABASE_FUNCSQLTOYAML_H
