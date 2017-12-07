//
// Created by Qut on 29/10/2017.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../h/struct.h"
/* ----- GLOBALS ----- */
db_infos locationdb;
extern int FILE_LINE_COUNTER;
extern int DEBUG_PRINT;

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
 * @breif Renvoie le nombre de caractères présents dans un fichiers.
 *               Sauvegarde la position du curseur avant le calcul pour pouvoir le remplacer à cet endroit à la fin de l'opération.
 * Paramètre(s) :
 *      FILE* file : Pointeur de fichier du fichier concerné.
 */
int fSize(FILE *file) {
	int value;
	int initialCursor;

	initialCursor = ftell(file);            // Sauvegarde de la position du curseur actuelle
	fseek(file, 0, SEEK_END);               // Déplacement vers la fin du fichier
	value = ftell(file);                    // Renvoi le nombre de charactères dans le fichier
	fseek(file, initialCursor, SEEK_SET);   // Repositionnement du curseur à son emplacement initial.
	return value;
}


/**
 * @breif Compte le nombre de tabulations au début de la chaîne donnée.
 * Paramètre(s) :
 *      char* str : chaîne de caractères concernée.
 * Renvoi :
 *      Succès : Le nombre de tabulations comptées.
 *      Échec  : Renvoie -1
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
 * @breif Déplace le curseur du fichier jusqu'au début de la ligne voulue.
 * Paramètres :
 *      int line : numéro de ligne auquel se déplacer.
 *      FILE* sourceFile : pointeur de fichier du fichier concerné.
 * Retour :
 *      Succès : renvoie 1.
 *      Échec  : renvoie -1
 * Remarque : En cas de dépassement du fichier, c'est-à-dire si le numéro de ligne demandé est supérieur
 *            au nombre actuel de lignes dans le fichier, place le curseur en fin de fichier.
 */
int fGoToLine(int line, FILE* sourceFile) {
    int i;
    int fileSize;
    char temp[MAX];

    fileSize = fSize(sourceFile);
    if(sourceFile != NULL) {
        fseek(sourceFile, 0, SEEK_SET);                 // Déplacement au début du fichier
        FILE_LINE_COUNTER = 0;
        for(i=0 ; i < line-1 ; i++) {                   // Déplacement jusqu'à la ligne voulue
            if(ftell(sourceFile) >= fileSize) {         // Si on dépasse la fin du fichier (ligne demandée plus grande que le nombre de lignes du fichier)
                return 0;                               // Alors reotur d'erreur
            } else if(fgets(temp, MAX, sourceFile)) {   // Sinon passage à la lign suivante
                FILE_LINE_COUNTER++;
            } else {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}




/**
 * @brief Fonction de gestion d'erreur. Écrit dans l'outpout dédié au erreurs.
 *
 * @param char* message : message d'erreur.
 *
 * @return void.
 *
 * Remarque : peut être modifié en créant un répertoire d'erreur avec chaque erreur correspondant à un message précis.
 */
void error(const char* message) {
    if(message != NULL)
        fprintf(stderr, message);
}
