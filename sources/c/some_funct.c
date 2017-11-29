//
// Created by Qut on 29/10/2017.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../h/struct.h"

db_infos locationdb;


void verifFirstInit() {
    FILE *fp;

    if ((fp = fopen("donnees","r")) == NULL) {
        printf("Impossible d'ouvrir le fichier en lecture\n");
    }
}

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



/**
 * Description : Renvoie le nombre de caract�res pr�sents dans un fichiers.
 *               Sauvegarde la position du curseur avant le calcul pour pouvoir le remplacer � cet endroit � la fin de l'op�ration.
 * Param�tre(s) :
 *      FILE* file : Pointeur de fichier du fichier concern�.
 *
 */
int fSize(FILE *file) {
	int value;
	int initialCursor;

	initialCursor = ftell(file);           // Sauvegarde de la position du curseur actuelle
	fseek(file, 0, SEEK_END);               // D�placement vers la fin du fichier
	value = ftell(file);                    // Renvoi le nombre de charact�res dans le fichier
	fseek(file, initialCursor, SEEK_SET);  // Repositionnement du curseur � son emplacement initial.
	return value;
}


/**
 * Description : Comptele nombre de tabulation au d�but de la cha�ne donn�e.
 * Param�tre(s) :
 *      char* str : cha�ne de caract�res concern�e.
 * Renvoi :
 *      Succ�s : Le nombre de tabulations compt�es.
 *      �chec  : -1;
 *
 */
int countTab(char* str) {
    int i = -1;
    int strLength;

    if(str != NULL) {
        strLength = strlen(str);
        if(strLength > 0) {
            for(i=0 ; i < strLength ; i++) {
                if(str[i] != ' ') {
                    break;
                }
            }
            i /= 4;
        }
    }
    return i;
}

/**
 * Description : D�place le curseur du fichier jusqu'au d�but de la ligne voulue.
 * Param�tres :
 *      FILE* sourceFile : pointeur de fichier du fichier concern�.
 *      int line : num�ro de ligne auquel se d�placer.
 * Retour :
 *      Succ�s : renvoie 1.
 *      �chec : renvoie -1
 * Remarque : En cas de d�passement du fichier, c'est-�-dire si le num�ro de ligne demand� est sup�rieur
 *            au nombre actuel de lignes dans le fichier, place le curseur en fin de fichier.
 */
int fGoToLine(FILE* sourceFile, int line) {
    int i;
    int fileSize;
    char temp[MAX];

    fileSize = fSize(sourceFile);
    if(sourceFile != NULL) {
        fseek(sourceFile, 0, SEEK_SET);
        for(i=0 ; i < line-1 ; i++) {
            if(ftell(sourceFile) < fileSize) {
                fgets(temp, MAX, sourceFile);
            } else {
                return 0;
            }
        }
        printf("%c", fgetc(sourceFile));
        return 1;
    }
    return 0;
}
