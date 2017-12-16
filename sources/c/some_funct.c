//
// Created by Qut on 29/10/2017.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../h/struct.h"
#include "../h/some_funct.h"
#include "../h/parser_SQL.h"
#include "../h/struct.h"

/* ----- GLOBALS ----- */
extern int FILE_LINE_COUNTER;


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

/**
 * Desc: up the string
 *
 * Param: Char * word : String to up
 *
 * Return: (char *) upper string
 */
char *upWord(char *word) {
    size_t len;
    int i;
    len = strlen(word);
    char *upword = malloc(sizeof(char) * (len + 1));
    for (i = 0; i < len; i++) {
        upword[i] = (char) ((word[i] >= 'a' && word[i] <= 'z') ? word[i] - 32 : word[i]);
    }
    upword[len] = '\0';
    return upword;
}


/**
 * @brief Renvoie le nombre de caractï¿½res prï¿½sents dans un fichiers.
 *               Sauvegarde la position du curseur avant le calcul pour pouvoir le remplacer ï¿½ cet endroit ï¿½ la fin de l'opï¿½ration.
 * Paramï¿½tre(s) :
 *      FILE* file : Pointeur de fichier du fichier concernï¿½.
 */
int fSize(FILE *file) {
    int value = 0;
    int initialCursor;

    if (file != NULL) {
        initialCursor = ftell(file);            // Sauvegarde de la position du curseur actuelle
        fseek(file, 0, SEEK_END);               // Déplacement vers la fin du fichier
        value = ftell(file);                    // Renvoi le nombre de charactères dans le fichier
        fseek(file, initialCursor, SEEK_SET);   // Repositionnement du curseur à son emplacement initial.
    }
    return value;
}


/**
 * @brief Compte le nombre de tabulations au dï¿½but de la chaï¿½ne donnï¿½e.
 * Paramï¿½tre(s) :
 *      char* str : chaï¿½ne de caractï¿½res concernï¿½e.
 * Renvoi :
 *      Succï¿½s : Le nombre de tabulations comptï¿½es.
 *      ï¿½chec  : Renvoie -1
 */
int countTab(char *str) {
    int i = -1;
    int strLength;

    if (str != NULL) {
        strLength = strlen(str);
        if (strLength > 0) {
            for (i = 0; i < strLength; i++) {
                if (str[i] != ' ') {
                    break;
                }
            }
            i /= 4;
        }
    }
    return i;
}

/**
 * @brief Dï¿½place le curseur du fichier jusqu'au dï¿½but de la ligne voulue.
 * Paramï¿½tres :
 *      int line : numï¿½ro de ligne auquel se dï¿½placer.
 *      FILE* sourceFile : pointeur de fichier du fichier concernï¿½.
 * Retour :
 *      Succï¿½s : renvoie 1.
 *      ï¿½chec  : renvoie -1
 * Remarque : En cas de dï¿½passement du fichier, c'est-ï¿½-dire si le numï¿½ro de ligne demandï¿½ est supï¿½rieur
 *            au nombre actuel de lignes dans le fichier, place le curseur en fin de fichier.
 */
int fGoToLine(int line, FILE *sourceFile) {
    int i;
    int fileSize;
    char temp[MAX];

    fileSize = fSize(sourceFile);
    if (sourceFile != NULL) {
        fseek(sourceFile, 0, SEEK_SET);                 // Dï¿½placement au dï¿½but du fichier
        FILE_LINE_COUNTER = 0;
        for (i = 0; i < line - 1; i++) {                   // Dï¿½placement jusqu'ï¿½ la ligne voulue
            if (ftell(sourceFile) >=
                fileSize) {         // Si on dï¿½passe la fin du fichier (ligne demandï¿½e plus grande que le nombre de lignes du fichier)
                return 0;                               // Alors reotur d'erreur
            } else if (fgets(temp, MAX, sourceFile)) {   // Sinon passage ï¿½ la lign suivante
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
 * @brief Fonction de gestion d'erreur. ï¿½crit dans l'outpout dï¿½diï¿½ au erreurs.
 *
 * @param char* message : message d'erreur.
 *
 * @return void.
 *
 * @remarks : peut ï¿½tre modifiï¿½ en crï¿½ant un rï¿½pertoire d'erreur avec chaque erreur correspondant ï¿½ un message prï¿½cis.
 */
void error(const char *message) {
    if (message != NULL)
        fprintf(stderr, message);
}


/**
 * Desc: delete multiple space
 *
 * Param: Char * word : String to clean of multiple space
 *
 * Return: (char *) clean string without multiple space
 */
char *cleanQuery(char *word) {
    size_t len;
    int i;
    int showchar;
    showchar = 1;
    size_t cleanspace;
    len = strlen(word);
    cleanspace = len;
    if (!strncmp(&word[0], " ", 1)) {
        cleanspace = len - 1;
        showchar = 0;
    }
    for (i = 0; i < len - 1; i++) {
        if (!strncmp(&word[i], " ", 1) && !strncmp(&word[i + 1], " ", 1)) {
            cleanspace--;
        }
    }
    char *cleanquery = malloc(sizeof(char) * (cleanspace + 1));
    cleanquery[cleanspace - 1] = ';';
    cleanquery[cleanspace] = '\0';
    cleanspace = 0;
    for (i = 0; i < len - 1; i++) {
        if (!strncmp(&word[i], " ", 1) && !strncmp(&word[i + 1], " ", 1)) {
            continue;
        } else {
            if (!showchar) {
                showchar = 1;
            } else {
                cleanquery[cleanspace] = word[i];
                cleanspace++;
            }
        }
    }
    return cleanquery;
}


/**
 * Desc: check if the string is alphanumeric
 *
 * Param: Char * word : String to check
 *
 * Return: 1 -> Alphanum ; 0 if not
 */
int isAlphaNum(char *word) {
    size_t len;
    int isOk;
    int i;

    isOk = 1;
    len = strlen(word);
    for (i = 0; i < len; i++) {
        if (word[i] < '0'
            || (word[i] > '9' && word[i] < 'A')
            || (word[i] > 'Z' && word[i] < 'a')
            || (word[i] > 'z')) {
            isOk = 0;
            break;
        }
    }
    return isOk;
}

/**
 * Desc: return number of terms split with the delim
 *
 * Param:
 *      Char * countChar : String to split and count
 *      char delim : Char delim
 *
 * Return: number of term (int)
 */
int countArgs(char *countChar, const char *delim) {
    char *countrequest;
    countrequest = malloc(sizeof(char) * (strlen(countChar) + 1));
    strcpy(countrequest, countChar);
    int count;
    count = 0;
    char *token = strtok(countrequest, delim);
    while (token != NULL) {
        count++;
        token = strtok(NULL, delim);
    }
    free(countrequest);
    return count;
}


/**
 * Desc: return the first word of a string
 *
 * Param: Char * word : String to csplit
 *
 * Return: first word
 */
char *splitWord(char *word, const char *delim) {
    int len;
    int count;
    char *firstWord;
    len = strlen(word);
    for (count = 0; count < len; count++) {
        if (word[count] == delim[0]) {
            firstWord = malloc(sizeof(char) * (count + 1));
            strncpy(firstWord, word, count);
            firstWord[count] = '\0';
            break;
        }
    }
    return firstWord;
}

/**
 * Desc: check if the word is ban
 *
 * Param: Char * word : String to check
 *
 * Return: 1 -> not ban ; 0 -> ban
 */
int correctWord(char *word) {
    return 1;
}

/**
 * Desc: check if the expression is on SQL expr
 *
 * Param: Char * word : String to check
 *
 * Return: 1 -> good ; 0 -> not in expr list
 */
char *checkExprSQL(char *line, char *expr) {
    char *checkline;
    checkline = strstr(upWord(line), expr);
    if (checkline) {
        return "true";
    } else {
        return "false";
    }

}


/**
 * Desc: check & return the type for the column
 *
 * Param: Char * word : String to check
 *
 * Return: type of column
 */
char *checkTypeSQL(char *line) {
    char *type;
    type = strstr(upWord(line), "INT");
    if (!type) {
        type = strstr(upWord(line), "VARCHAR");
        if (!type) {
            type = strstr(upWord(line), "CHAR");
            if (!type) {
                type = strstr(upWord(line), "FLOAT");
                if (type) {
                    type[5] = '\0';
                } else { type = "false"; }
            } else { type[4] = '\0'; }
        } else { type[7] = '\0'; }
    } else { type[3] = '\0'; }
    return type;
}


char *insertSplit(char *buffer, int number) {
    char *word;
    int i;
    int temp = 0;
    int count = 1;
    word = malloc(sizeof(char) * 512);
    for (i = 0; i < strlen(buffer); i++) {
        if (i == 0 && buffer[i] == 32) {
            continue;
        }
        if (buffer[i] == 39) {
            temp = i;
            while (buffer[++i] != 39 && buffer[i - 1] != 92) {
                if (i > strlen(buffer)) {
                    strcpy(word, "%%%%%");
                    return word;
                }
            }
            if (count == number) {
                strncpy(word, buffer + temp, i - temp + 1);
                word[i - temp + 1] = '\0';
                return word;
            } else {
                count++;
            }
        } else if (isNumber(buffer[i])) {
            temp = i;
            while (buffer[++i] != ',' && (isNumber(buffer[i]) || buffer[i] == '.')) {
                if (i > strlen(buffer)) {
                    strcpy(word, "%%%%%");
                    return word;
                }
            }
            if (count == number) {
                strncpy(word, buffer + temp, i - temp);
                word[i - temp] = '\0';
                return word;
            } else {
                count++;
            }
        } else {
            if (buffer[i + 1] == 32) { ++i; continue;} else {
                strcpy(word, "%%%%%");
                return word;
            }

        }

    }
    free(word);
    return NULL;
}


int isNumber(char buffer) {
    if (buffer < 48 || buffer > 57) {
        return 0;
    } else {
        return 1;
    }
}

char *whichType(char *buffer) {
    int intType = 1;
    int floatType = 0;
    if (buffer[0] == 39 && buffer[strlen(buffer) - 1] == 39) {
        if (strlen(buffer) > 3) {
            return "varchar";
        } else {
            return "char";
        }
    } else {
        for (int i = 0; i < strlen(buffer); i++) {
            if ((buffer[i] >= '0' && buffer[i] <= '9') || buffer[i] == 46) {
                if (buffer[i] == 46) { floatType = 1; }
            } else {
                intType = 0;
                break;
            }
        }
        if (intType && floatType) { return "float"; }
        if (intType && !floatType) { return "int"; }
    }
    return "Wrong Type";
}


char *updateSplitWord(char *buffer, int number, int type) {
    int control = 1;
    int constraint = 0;
    int start = 0;
    int end = 1;
    char *word;
    int count = 1;
    word = malloc(sizeof(char) * 512);
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == 61 && control == 1) {
            end = (buffer[i - 1] == 32) ? end - 2 : end - 1;
            strncpy(word, buffer + start, end);
            word[end] = '\0';
            if (number == count) {
                if (type == 1) {
                    return word;
                } else if (type == 2) {
                    word = insertSplit(buffer + i + 1, 1);
                    return word;
                }
            } else {
                start = i + 1;
                end = 1;
                control = 0;
                constraint = i + strlen(insertSplit(buffer + i + 1, 1)) + 3;
                count++;
                continue;
            }
        }
        if (buffer[i] == 44 && control == 0) {
            control = 1;
            start = (buffer[i + 1] == 32) ? i + 2 : i + 1;
            end = 1;
            continue;
        }
        end++;
    }
    if (!strncmp(upWord(buffer + constraint), "WHERE ", 5)) {
        if (type == 3) {
            word = updateSplitWord(buffer + constraint + 5, 1, 1);
            return word;
        } else if (type == 4) {
            word = updateSplitWord(buffer + constraint + 5, 1, 2);
            return word;
        } else {
            return NULL;
        }
    }
    free(word);
    return NULL;
}
