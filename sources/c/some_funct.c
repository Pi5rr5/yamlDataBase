//
// Created by Qut on 29/10/2017.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../h/struct.h"
#include "../h/some_funct.h"
#include "../h/parser_SQL.h"
/* ----- GLOBALS ----- */
db_infos locationdb;
extern int FILE_LINE_COUNTER;
extern int DEBUG_PRINT;



//fonction de base menu, init (procédure initialisation), ouverture fichiers


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
            parserSQL(word);
            break;
        }
        //traiter le multi-ligne
        printf("%d : ", ++counter);
    }

}


void menu() {
    //  verifFirstInit();
    //  showInfo();
    printf("WELCOME\ntype exit or blanck query for exit");

    while (1) {
        char requestsql[1024] = "";
        char word[255] = "";
        int counter;
        counter = 1;
        printf("\n%d>", counter);
        //si ; en fin
        while (scanf("%[^\n]%*c", word) == 1) {
            if (!strcmp(&word[strlen(word) - 1], ";")) {
                strcat(requestsql, word);
                parserSQL(requestsql);
                break;
            } else if (strcmp(&word[strlen(word) - 1], " ")) {
                strcat(word, " ");
            }
            strcat(requestsql, word);
            printf("%d>", ++counter);
        }
        if (strlen(word) == 0) {
            query_exit("");
            break;
        }
        if (!strcmp(upWord(word), "EXIT;")) {
            break;
        }

    }
}


char *upWord(char *word) {
    size_t len;
    int boucle;
    len = strlen(word);
    char *upword = malloc(sizeof(char) * (len + 1));
    for (boucle = 0; boucle < len; boucle++) {
        upword[boucle] = (char) ((word[boucle] >= 'a' && word[boucle] <= 'z') ? word[boucle] - 32 : word[boucle]);
    }
    upword[len] = '\0';
    return upword;
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
 * @remarks : peut �tre modifi� en cr�ant un r�pertoire d'erreur avec chaque erreur correspondant � un message pr�cis.
 */
void error(const char* message) {
    if(message != NULL)
        fprintf(stderr, message);
}

char *cleanQuery(char *word) {
    size_t len;
    int boucle;
    int showchar;
    showchar = 1;
    size_t cleanspace;
    len = strlen(word);
    cleanspace = len;
    if (!strncmp(&word[0], " ", 1)) {
        cleanspace = len - 1;
        showchar = 0;
    }
    for (boucle = 0; boucle < len - 1; boucle++) {
        if (!strncmp(&word[boucle], " ", 1) && !strncmp(&word[boucle + 1], " ", 1)) {
            cleanspace--;
        }
    }
    char *cleanquery = malloc(sizeof(char) * (cleanspace + 1));
    cleanquery[cleanspace - 1] = ';';
    cleanquery[cleanspace] = '\0';
    cleanspace = 0;
    for (boucle = 0; boucle < len - 1; boucle++) {
        if (!strncmp(&word[boucle], " ", 1) && !strncmp(&word[boucle + 1], " ", 1)) {
            continue;
        } else {
            if (!showchar) {
                showchar = 1;
            } else {
                cleanquery[cleanspace] = word[boucle];
                cleanspace++;
            }
        }
    }
    return cleanquery;
}

