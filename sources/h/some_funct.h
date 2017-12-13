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
    size_t strALen(char*);
	int strIsIn(char*, char[][255]);
#endif /* YAML_SOME_FUNCT_H */
