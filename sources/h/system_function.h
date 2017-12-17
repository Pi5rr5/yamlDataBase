#ifndef SYSTEM_FUNCTION_H_INCLUDED
    #define SYSTEM_FUNCTION_H_INCLUDED

    int createDB(char *);

    int useDB(char *);

    int createTable(char *);

    int createEmptyFile(char *, char *);

    int initYamlFile(char *);

    int isExist(char *);

    int dropTable(char *);

    int dropDB(char *);

#endif // SYSTEM_FUNCTION_H_INCLUDED
