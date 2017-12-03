#include <stdio.h>

#ifndef PARSERYAML_H_INCLUDED
#define PARSERYAML_H_INCLUDED
    listOfLines* addLineToList(listOfLines*, lineStruct);
    listOfEntities* addEntityToList(listOfEntities*, listOfLines*);
    void displayListOfLines(listOfLines*);
    void displayListOfLines(listOfLines*);
    void freeListOfLines(listOfLines*);
    int freadL(char*, unsigned int, FILE*);
    int verifLine(char*);
    int hasKey(char*, char*);
#endif // PARSERYAML_H_INCLUDED
