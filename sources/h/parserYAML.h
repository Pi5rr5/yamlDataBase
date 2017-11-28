#include <stdio.h>

#ifndef PARSERYAML_H_INCLUDED
#define PARSERYAML_H_INCLUDED
    tableEntity* ll_addAtEnd(tableEntity*, char*);
    int freadL(FILE*, unsigned int, char*);
    int verifLine(char*);
    int isKey(char*, char*);
    int getValue(FILE*, char*);
    void getKeyValue(FILE*, char*, char*);
#endif // PARSERYAML_H_INCLUDED
