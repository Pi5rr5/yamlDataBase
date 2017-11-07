//
// Created by Qut on 29/10/2017.
//

#ifndef YAML_SOME_FUNCT_H
#define YAML_SOME_FUNCT_H

typedef struct struct_db {
    char *database;
} db_infos;


void init();

void verifFirstInit();

char *upWord(char *);

void showInfo();

void changeDatabase(char *);

#endif //YAML_SOME_FUNCT_H
