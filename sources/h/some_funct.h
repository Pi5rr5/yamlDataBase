#ifndef YAML_SOME_FUNCT_H
	#define YAML_SOME_FUNCT_H

    void menu();

    char *upWord(char *);
    char *cleanQuery(char *);


    int fSize(FILE*);
    int freadL(char*, unsigned int, FILE*);
    int countTab(char*);
    int fGoToLine(int, FILE*);
    void error(const char*);
	int strIsIn(char*, char[][255]);
	arrayOfStrings createArrayOfStrings(unsigned int);
	arrayOfStrings updateArrayOfStrings(arrayOfStrings, unsigned int);
	void freeArrayOfStrings(arrayOfStrings*);
#endif /* YAML_SOME_FUNCT_H */
