//
// Created by Qut on 29/10/2017.
//
#include <stdio.h>
#include "../h/some_funct.h"
#include "../h/parser_SQL.h"
#include <string.h>
#include <stdlib.h>


//fonction de base menu, init (procédure initialisation), ouverture fichiers


extern int fileLineCounter;



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


int isAlphaNum(char *word) {
    size_t len;
    int isOk;
    isOk = 1;
    len = strlen(word);
    for(int boucle = 0; boucle < len; boucle++) {
        if ((word[boucle] < 'a' || word[boucle] > 'z')) { isOk = 0; break; }
    }
    return isOk;
}


int countArgs(char* countChar, char delim) {
    int count;
    char* token = strtok(countChar, (const char *) delim);
    while( token != NULL ) {
        count++;
        token = strtok(NULL, (const char *) delim);
    }
    return count;
}

//exemple
/**
 * Description : Renvoie le nombre de caractères présents dans un fichiers.
 *               Sauvegarde la position du curseur avant le calcul pour pouvoir le remplacer à cet endroit à la fin de l'opération.
 * Paramètre(s) :
 *      FILE* file : Pointeur de fichier du fichier concerné.
 */
