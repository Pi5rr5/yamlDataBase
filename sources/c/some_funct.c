//
// Created by Qut on 29/10/2017.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../h/struct.h"

db_infos locationdb;

void init() {
    verifFirstInit();

    locationdb.database = "None (select one)";
    showInfo();
}

void requestSQL() {
    int counter;
    int len;
    counter = 1;
    char word[255];
    printf("\n%d : ", counter);
    while (scanf("%[^\n]%*c", word) == 1) {
        if (strstr(word, ";") != NULL) {
            len = strlen(word);
            word[len - 1] = '\0';
            parserSQL(word, cmdRequest);

            break;
        }
        //traiter le multi-ligne
        printf("%d : ", ++counter);
    }

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

/*
 * Description : Renvoie le nombre de caractères présents dans un fichiers.
 *               Sauvegarde la position du curseur avant le calcul pour pouvoir le remplacer à cet endroit à la fin de l'opération.
 * Paramètre(s) :
 *      FILE* file : Pointeur de fichier du fichier concerné.
 *
*/
int fileSize(FILE *file) {
	int value;
	int prevCursor;

	prevCursor = ftell(file);           // Sauvegarde de la position du curseur actuelle
	fseek(file, 0, SEEK_END);           // Déplacement vers la fin du fichier
	value = ftell(file);                // Renvoi le nombre de charactères dans le fichier
	fseek(file, prevCursor, SEEK_SET);  // Repositionnement du curseur à son emplacement initial.
	return value;
}
