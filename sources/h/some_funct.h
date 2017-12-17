#ifndef YAML_SOME_FUNCT_H
	#define YAML_SOME_FUNCT_H
	extern int FILE_LINE_COUNTER;
    void menu();

    char *upWord(char *);
    char *cleanQuery(char *);


    int fSize(FILE*);
    int freadLine(char*, unsigned int, FILE*);
    int countTab(char*);
    int fGoToLine(int, FILE*);
    void error(const char*);
	int strSearchInArray(char*, arrayOfStrings);
	arrayOfStrings createArrayOfStrings(unsigned int);
	arrayOfStrings updateArrayOfStrings(arrayOfStrings, unsigned int);
	void freeArrayOfStrings(arrayOfStrings*);
	int compare(char*, char*, char*);
#endif /* YAML_SOME_FUNCT_H */
