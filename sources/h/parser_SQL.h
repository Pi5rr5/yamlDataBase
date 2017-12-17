//
// Created by Qut on 29/10/2017.
//

#ifndef MY_PROJ_PARSER_H
#define MY_PROJ_PARSER_H

typedef struct commandSQL {
    char *name;
    void (*functionSQL)(char *);
} commandSQL;

void parserSQL(char *);


void queryExit(char *);

void queryError(char *);

#endif /* MY_PROJ_PARSER_H */

