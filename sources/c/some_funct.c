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
 * @breif Renvoie le nombre de caract�res pr�sents dans un fichiers.
 *               Sauvegarde la position du curseur avant le calcul pour pouvoir le remplacer � cet endroit � la fin de l'op�ration.
 * Param�tre(s) :
 *      FILE* file : Pointeur de fichier du fichier concern�.
 */
int fSize(FILE *file) {
	int value;
	int initialCursor;

	initialCursor = ftell(file);            // Sauvegarde de la position du curseur actuelle
	fseek(file, 0, SEEK_END);               // D�placement vers la fin du fichier
	value = ftell(file);                    // Renvoi le nombre de charact�res dans le fichier
	fseek(file, initialCursor, SEEK_SET);   // Repositionnement du curseur � son emplacement initial.
	return value;
}


/**
 * @breif Compte le nombre de tabulations au d�but de la cha�ne donn�e.
 * Param�tre(s) :
 *      char* str : cha�ne de caract�res concern�e.
 * Renvoi :
 *      Succ�s : Le nombre de tabulations compt�es.
 *      �chec  : Renvoie -1
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
 * @breif D�place le curseur du fichier jusqu'au d�but de la ligne voulue.
 * Param�tres :
 *      int line : num�ro de ligne auquel se d�placer.
 *      FILE* sourceFile : pointeur de fichier du fichier concern�.
 * Retour :
 *      Succ�s : renvoie 1.
 *      �chec  : renvoie -1
 * Remarque : En cas de d�passement du fichier, c'est-�-dire si le num�ro de ligne demand� est sup�rieur
 *            au nombre actuel de lignes dans le fichier, place le curseur en fin de fichier.
 */
int fGoToLine(int line, FILE* sourceFile) {
    int i;
    int fileSize;
    char temp[MAX];

    fileSize = fSize(sourceFile);
    if(sourceFile != NULL) {
        fseek(sourceFile, 0, SEEK_SET);                 // D�placement au d�but du fichier
        FILE_LINE_COUNTER = 0;
        for(i=0 ; i < line-1 ; i++) {                   // D�placement jusqu'� la ligne voulue
            if(ftell(sourceFile) >= fileSize) {         // Si on d�passe la fin du fichier (ligne demand�e plus grande que le nombre de lignes du fichier)
                return 0;                               // Alors reotur d'erreur
            } else if(fgets(temp, MAX, sourceFile)) {   // Sinon passage � la lign suivante
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
 * @brief Fonction de gestion d'erreur. �crit dans l'outpout d�di� au erreurs.
 *
 * @param char* message : message d'erreur.
 *
 * @return void.
 *
 * Remarque : peut �tre modifi� en cr�ant un r�pertoire d'erreur avec chaque erreur correspondant � un message pr�cis.
 */
void error(const char* message) {
    if(message != NULL)
        fprintf(stderr, message);
}
