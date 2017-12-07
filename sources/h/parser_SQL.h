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

void query_use(char *);

void query_create_database(char *);

void query_create_table(char *);

void query_drop_database(char *);

void query_drop_table(char *);

void query_exit(char *);

void query_error(char *);

#endif /* MY_PROJ_PARSER_H */

