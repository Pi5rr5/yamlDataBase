#include <stdio.h>

#ifndef PARSERYAML_H_INCLUDED
#define PARSERYAML_H_INCLUDED
    ll_line* ll_addAtEnd(ll_line*, char*);
    int freadL(FILE*, unsigned int, char*);
    int verifLine(char*);
    int isKey(char*, char*);
    int getValue(FILE*, char*);
    ll_dataBlock* getKey(FILE*, char*);
#endif // PARSERYAML_H_INCLUDED
