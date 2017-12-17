//
// Created by Qut on 29/10/2017.
//



#ifndef YAML_SOME_FUNCT_H
#define YAML_SOME_FUNCT_H

void menu();

extern int FILE_LINE_COUNTER;

char *upWord(char *);

char *cleanQuery(char *);

int isAlphaNum(char *);

int countArgs(char *, const char *);

char *splitWord(char *, const char *);

int correctWord(char *);

char *checkExprSQL(char *, char *);

char *checkTypeSQL(char *);

int fGoToLine(int, FILE *);

void error(const char *);

char *whichType(char *);

char *updateSplitWord(char *, int, int);

int isNumber(char);

char *insertSplit(char *buffer, int number);

int fSize(FILE *);

int freadLine(char *, unsigned int, FILE *);

int countTab(char *);

int strSearchInArray(char *, arrayOfStrings);

arrayOfStrings createArrayOfStrings(unsigned int);

arrayOfStrings updateArrayOfStrings(arrayOfStrings, unsigned int);

void freeArrayOfStrings(arrayOfStrings *);

int compare(char *, char *, char *);

#endif /* YAML_SOME_FUNCT_H */
