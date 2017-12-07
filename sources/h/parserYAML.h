#include <stdio.h>

#ifndef PARSERYAML_H_INCLUDED
#define PARSERYAML_H_INCLUDED
    listOfLines* addLineToList(listOfLines*, lineStruct);
    listOfEntities* addEntityToList(listOfEntities*, listOfLines*);
    void displayListOfLines(listOfLines*);
    void displayListOfEntities(listOfEntities*);
    void freeListOfLines(listOfLines**);
    void freeListOfEntities(listOfEntities**);
    int freadL(char*, unsigned int, FILE*);
    int verifLine(char*);
    int hasKey(char*, char*);
    listOfEntities* getBlockWhere(char*, char*, FILE*);
#endif // PARSERYAML_H_INCLUDED
