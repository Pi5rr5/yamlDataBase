//
// Created by Qut on 29/10/2017.
//
#include <stdio.h>
#include "../h/some_funct.h"
#include <string.h>
#include <stdlib.h>

db_infos locationdb;

void init() {
    verifFirstInit();

    locationdb.database = "None (select one)";
    showInfo();
}






//a modifier pour up que le premier mot
char *upWord(char *word) {
    int len;
    len = strlen(word);
    int boucle;
    char *upword = malloc(sizeof(char) * len);
    for (boucle = 0; boucle < len; boucle++) {
        if (word[boucle] >= 'a' && word[boucle] <= 'z') {
            upword[boucle] = word[boucle] - 32;
        } else {
            upword[boucle] = word[boucle];
        }
    }
    return upword;
}

void showInfo() {
printf("current database : %s\n", locationdb.database);
}

void changeDatabase(char *newDB) {
    locationdb.database = newDB;

}
void verifFirstInit() {
    FILE *fp;

    if ((fp = fopen("donnees","r")) == NULL)
    {
        printf("Impossible d'ouvrir le fichier en lecture\n");
    }


}