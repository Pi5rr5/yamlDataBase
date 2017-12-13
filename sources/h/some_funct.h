//
// Created by Qut on 29/10/2017.
//



#ifndef YAML_SOME_FUNCT_H
#define YAML_SOME_FUNCT_H

void menu();


char *upWord(char *);

char *cleanQuery(char *);

int isAlphaNum(char *);

int countArgs(char *, const char *);

char *splitWord(char *, const char *);

int correctWord(char *);

char *checkExprSQL(char *, char *);

char *checkTypeSQL(char *);

int fSize(FILE *);

int countTab(char *);

int fGoToLine(int, FILE *);

void error(const char *);

#endif /* YAML_SOME_FUNCT_H */
