#ifndef PARSERYAML_H_INCLUDED
	#define PARSERYAML_H_INCLUDED
    listOfLines* addLineToList(listOfLines*, lineStruct);
    void displayListOfLines(listOfLines*);
    void freeListOfLines(listOfLines**);
    listOfEntities* addEntityToList(listOfEntities*, listOfLines*);
    void displayListOfEntities(listOfEntities*);
    void freeListOfEntities(listOfEntities**);
    int isEOY(char*);
    char* getKey(char*);
    char* getValue(char*);
    lineStruct getLineStruct(char*);
    listOfLines* getEntity(int, FILE*);
    int verifLine(char*);
	listOfEntities* getBlockWhere(arrayOfStrings, arrayOfStrings, arrayOfStrings, FILE*);
    listOfEntities* getAllFrom(FILE*);
    int insertLine(lineStruct, FILE*);
    int insertEntity(listOfLines*, FILE*);
    int insertListOfEntities(listOfEntities*, FILE*);
#endif // PARSERYAML_H_INCLUDED
