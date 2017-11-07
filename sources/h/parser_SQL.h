//
// Created by Qut on 29/10/2017.
//

#ifndef MY_PROJ_PARSER_H
#define MY_PROJ_PARSER_H


typedef struct struct_command {
    char *name;

    void (*f)(char *);
} command_options;

extern command_options cmdRequest[];


void parse_use(char *);

void parse_create(char *);

void parse_drop(char *);

void parse_exit(char *);

void parse_error();

void parserSQL(char *, command_options *);

void create_database(char *);

void create_table(char *);

void drop_database(char *);

void drop_table(char *);

#endif /* MY_PROJ_PARSER_H */

