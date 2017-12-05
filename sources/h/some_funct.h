//
// Created by Qut on 29/10/2017.
//

#ifndef YAML_SOME_FUNCT_H
    #define YAML_SOME_FUNCT_H

    void init();

    void verifFirstInit();

    char *upWord(char *);

    void showInfo();

    void changeDatabase(char *);

    int fSize(FILE*);

    int countTab(char*);

    int fGoToLine(int, FILE*);

    void error(const char*);
#endif //YAML_SOME_FUNCT_H
