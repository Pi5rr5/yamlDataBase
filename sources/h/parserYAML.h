#ifndef PARSERYAML_H_INCLUDED
    #define PARSERYAML_H_INCLUDED
    extern int FILE_LINE_COUNTER;

    listOfLines* addLineToList(listOfLines*, lineStruct);
    void displayListOfLines(listOfLines*);
    void freeListOfLines(listOfLines**);

    listOfEntities* addEntityToList(listOfEntities*, listOfLines*);
    listOfEntities* removeLastEntity(listOfEntities**);
    listOfEntities* removeEntityAt(listOfEntities**, int);
    void displayListOfEntities(listOfEntities*);
    void freeListOfEntities(listOfEntities**);

    int isEOY(char*);
    int verifLine(char*);
    char* getKey(char*);
    char* getValue(char*);
    lineStruct getLineStruct(char*);
    listOfLines* getEntity(int, char*);

    int compareIntoLine(lineStruct, char*, char*, char*);
    int compareIntoEntity(listOfLines*, char*, char*, char*);
    int compareIntoList(listOfEntities*, char*, char*, char*);
    int updateLine(lineStruct*, char*, char*);

    listOfEntities* getBlockWhere(arrayOfStrings, arrayOfStrings, arrayOfStrings, char*);
    listOfEntities* getAllFrom(char*);

    int updateValuesWhere(AoS, AoS, AoS, AoS, AoS, char*);
    int insertLine(lineStruct, char*);
    int insertEntity(listOfLines*, char*);
    int insertListOfEntities(listOfEntities*, char*);

#endif // PARSERYAML_H_INCLUDED
