#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../h/struct.h"
#include "../h/some_funct.h"
#include "../h/parserYAML.h"

#ifndef MAX
    #define MAX 255     // Taille maximum utilis�e pour les chaines de caract�res non dynamiques.
#endif // MAX

#ifndef DEBUG_PRINT
    #define DEBUG_PRINT 1
#endif // DEBUG_PRINT

/* ----- GLOBALS ----- */
extern int fileLineCounter;     // Extern est utlis� pour les globales uniquement.\
                                    Il permet au compilateur de signaler que cette variable a peut �tre d�j� �t� d�clar�e qulquepart.\
                                    Il parcourt alors les fichiers (donc un peu co�teux en ressources)\
                                    et s'il trouve une autre d�claration qui a d�j� �t� ex�cut�e,\
                                    alors il ne recr�e pas la globale.




/* ----- FUNCTIONS ----- */

/**
 * Description : Ajoute un �l�ment � une liste cha�n�e de type `listOfLines`
 * Param�tre(s) :
 *      listOfLines* list : pointeur du d�but de la liste cha�n�e.
 *      value : valeur � ajouter dans le nouvel �l�ment
 * Retour :
 *      Succ�s : pointeur vers la liste cha�n�e mise � jour.
 *      �chec  : en cas d'erreur d'allocation, renvoie la liste non mise � jour.
 */
listOfLines* addLineToList(listOfLines* list, lineStruct line) {
    listOfLines* new_element;
    listOfLines* temp;

    new_element = malloc(sizeof(listOfLines));     // Allocation n�cessaire pour le nouvel �l�ment.
    if(new_element != NULL) {               // Si l'allocation s'est bien pass�e.
        if(DEBUG_PRINT)
            printf("\tAdding to list : '%s' as key and '%s' as value.\n", line.key, line.value);
        new_element->line = line;           // On affecte la valeur pass�e en argument � l'attribut du nouvel �lement correspondant.
        new_element->next = NULL;           // On fait pointer le pointeur de structure `next` � NULL, le nouvel �l�ment devenant le dernier de la liste
        if(list == NULL) {                  // Si la liste donn�e est vide.
            return new_element;             // On retourne le nouvel �l�ment.
        } else {
            temp = list;                    // Sinon on ajoute le dernier �l�ment � la fn de la liste
            while(temp->next != NULL) {     // Parcours de la liste.
                temp = temp->next;
            }
            temp->next = new_element;       // On fait pointer le dernier �l�ment de la liste sur le nouvel �l�ment.
            return list;                    // On retourne la liste mise  jour.
        }
    }
    return list;                            // Si erreur d'allocation, on retourne liste actuelle.
}




/**
 * Description : Affiche tous les �l�ments d'une liste cha�n�e de type listOfLines.
 *               Servira seulement pour du d�boggage.
 * Parm�tre(s) :
 *     listOfLines* list : liste cha�n�e concern�e.
 * Retour : Aucun.
 */
void displayListOfLines(listOfLines* list) {
    listOfLines* temp;


    if(DEBUG_PRINT)
        printf("\tList :\n");
    if(list != NULL) {
        temp = list;
        while(temp->next != NULL) {
            if(DEBUG_PRINT)
                printf("\t\tkey :\t%s\n\t\tvalue :\t%s\n", temp->line.key, temp->line.value);
            temp = temp->next;
        }

            if(DEBUG_PRINT)
                printf("\t\tkey :\t%s\n\t\tvalue :\t%s\n", temp->line.key, temp->line.value);
    } else {
        fprintf(stderr, "Liste vide.");
    }
    if(DEBUG_PRINT)
        printf("\tEnd of list.\n\n");
}




/**
 * Description : lib�re tout l'espace m�moire pris par la liste cha�n�e.
 * Param�tres :
 *     listOfLines list : liste cha�n�e concern�e.
 * Retour : Aucun.
 */
void freeListOfLines(listOfLines* list) {
    listOfLines* temp;
    listOfLines* temp2;

    if(list != NULL) {
        temp  = list;
        temp2 = list;
        while(temp->next != NULL) {
            temp2 = temp;
            temp = temp->next;
            if(temp2 != NULL) {
                free(temp2);
            }
        }
        free(temp);
    }
}




/**
 * Description : Lit une ligne dans un fihcier donn�e et la renvoie dans la cha�ne pass�e en argument.
 *               `fgets` a pour d�faut d'avoir un saut de ligne ('\n') en fin de cha�ne.
 *               `freadL` (la fonction ci-dessous) a pour unique but de palier � ce d�faut.
 * Param�tres :
 *      char* destination : cha�ne dans laquelle stock�e la ligne lue.
 *      unsigned int sizeMax : nombre de caract�res � lire.
 *      FILE* sourceFile : Pointeur du fichier concern�.
 * Retour :
 *      Succ�s : renvoie 1
 *      Echec  : renvoie 0
 * Remarque : Pas de gestion de la position du pointeur.
 */
int freadL(char* destination, unsigned int sizeMax, FILE* sourceFile) {
    int strLength;
    char result[MAX];

    if(sourceFile != NULL) {
        if(fgets(result, sizeMax, sourceFile) != NULL) {        // Lecture d'un ligne dans le fichier
            fileLineCounter++;
            strLength = strlen(result);
            if(result[strLength-1] == '\n') {  // Si le dernier caract�re avant le '\0' est un saut de ligne
                result[strLength-1] = '\0';    // On le remplace par un '\0'
                strcpy(destination, result);
            }
            return 1;
        }
    }
    return 0;
}



/**
 * Description : V�rifie que la ligne en question est bien � traiter.
 * Param�tre(s) :
 *      char* str : cha�ne de caract�res concernc�e.
 * Retour :
 *      Succ�s : renvoie 1.
 *      �chec  :
 *          - Si la ligne est un commentaire ou une ligne vide, renvoie 0.
 *          - Si la ligne est le symbole de fin de fichier, ou s'il y a eu une erreur de base, renvoie -1.
 */
int verifLine(char* str) {
    // Le symbole de fin di fichier est "...". Il peut �tre suivit d'un saut de ligne ('\n'). Dans certains texte, le saut de ligne est en r�alit� "\r\n".
    if(str == NULL || strcmp(str, "...") == 0 || strcmp(str, "...\n") == 0 || strcmp(str, "...\r\n") == 0)
        return -1;
    // Si la ligne lue est un commentaire ou une ligne vide. (L� encore, il peut y avoir '\r' avant un saut de ligne)
    if(str[0] == '#' || str[0] == '\n' || str[0] == '\r')
        return 0;
    return 1;   // Si aucun des cas ci-dessus, alors la ligne peut �tre traiter.
}




/**
 * Description : V�rifie que la ligne pass�e en argument contient bien une clef donn�e.
 *               Pour ce faire, parcours le fichier � la recherche d'occurences.
 *               D�s qu'une est trouv�e, on v�rifie qu'il n'y a rien avant et rien apr�s hormis des espaces ou des caract�res autoris�s ('-' et ':')
 * Param�tres :
 *      char* line : cha�ne contenant la ligne lue.
 *      char* key : cha�ne recherch�e.
 * Retour :
 *      Succ�s : 1
 *      �chec  : 0
 */
int hasKey(char* line, char* key) {
    int i;
    int findStrIndex;
    char* temp;

    if(line != NULL && key != NULL) {
        if((temp = strstr(line, key))) {                // `strstr` renvoie un pointeur correspondant � la position (ou l'adresse) de la premi�re occurence de la valeur cherch�e dans la cha�ne donn�e.
            findStrIndex = temp-line;                   // Par cons�quent soustraire cette valeur � l'adresse de la cha�ne dans laquelle on a cherch�; cela nous donne l'index o� se trouve l'occurence.
            /* V�rification des caract�re avant occurence */
            for(i=0 ; i < findStrIndex ; i++) {         // Parcourt de la cha�ne jusqu'� l'index (jusqu'� l'occurence)
                if(line[i] != ' ' && line[i] != '-') {  // Si l'un des caract�res se trouvant avant l'occurence est incorrect
                    return 0;                           // Pas une clef
                }
            }
            /* V�rification des caract�res apr�s occurence */
            if( (temp = strchr(line, ':')) ) {          // Une clef a forc�ment un ':' apr�s elle. On v�rifie qu'il y a ce caract�re sur la m�me ligne.
                /* Boucle jusqu'� ':' */
                for(i=findStrIndex+strlen(key) ; i < temp-line ; i++) {  // `findStrIndex+strlen(key)` est l'index de la fin de l'occurence. `temp-line` correspond � l'index o� se trouve le ':'
                    if(line[i] != ' ') {                // Si l'un des caract�res s�parant l'occurence de ':' n'est pas un espace
                        return 0;                       // Pas une clef
                    }
                }
                return 1;   // Si aucun des cas ci-dessus, alors il s'agit d'une clef.
            }
        }
    }
    return 0;
}




/**
 * Description : prend une ligne de donn�es YAML en param�tre et retourne la clef qui s'y trouve.
 * Param�tre(s) :
 *      char* line : ligne YAML concern�e.
 * Retour :
 *      Succ�s : Renvoie une cha�ne de caract�re contenant la clef.
 *      �chec  : Renvoie NULL.
 */
char* getKey(char* line) {
    int tempInt;
    int keyStart;
    char result[MAX];

    tempInt  = 0;
    keyStart = 0;

    while(line[tempInt++] == ' ');                          // Trouve l'index du premier caract�re n'�tant pas un espace
    keyStart = tempInt;
    while(line[tempInt++] != ' ' && line[tempInt] != ':');  // Trouve l'index du premier caract�re n'�tant ni espace ni un ':'

    strncpy(result, line+keyStart-1, tempInt-keyStart);     // copie juste la clef dans result
    result[tempInt-keyStart] = '\0';                        // strncpy ne prend pas en charge le '\0', on le rajoute � la fin de la cha�ne
    if(DEBUG_PRINT)
        printf("\tKey recovered : %s\n", result);
    return result;
}




/**
 * Description : Prends une ligne de YAML en param�tre et renvoie la valeur qui s'y trouve.
 * Param�tes :
 *      char* destination : cha�ne de caract�res dans laquelle sotcker la valeur.
 *      char* line : ligne de YAML � traiter.
 * Retour :
 *      Succ�s : renvoie la valeur trouv�e sous forme de cha�ne de caract�re.
 *      �chec  : renvoie une cha�ne vide.
 */
char* getValue(char* line) {
    int tempInt = 0;

    while(line[tempInt++] != ':');      // D�placement jusqu'au ':' de la clef /!\ WARNING /!\ si la clef comprend ':', la suite ne fonctionnera pas comme il faut.
    while(line[tempInt++] == ' ');      // D�placement jusqu'au premier caract�re de la valeur (inclu)

    switch(line[--tempInt]) {           // Recule d'un cran avant
        case 39:    // Texte sur une ligne simple quote (39 en ASCII)
            break;
        case 34:    // Texte sur une ligne double quote (34 en ASCII)
            break;
        default:    // Valeur classique
            if(DEBUG_PRINT)
                printf("\tValue recovered : %s\n", line+tempInt);
            return line+tempInt;
    }
    return "";
}




/**
 * Description : Prend une ligne de donn�e YAML en param�tre et renvoie un objet `line` contenant sa clef et sa valeur.
 * Param�tre(s) :
 *      char* str : cha�n� de caract�re de la ligne YAML concern�e.
 * Retour :
 *      Succ�s : Renvoie un objet `line` avec la clef et la valeur de la donn�e.
 */
lineStruct getLineStruct(char* str) {
    lineStruct line;
    char temp[MAX];

    strcpy(line.key, getKey(str));      // R�cup�re la clef de la ligne
    strcpy(line.value, getValue(str));  // R�cup�re la valeur correspondante
    return line;
}




/**
 * Description : R�cup�re l'int�gralit� d'une entit�.
 * Param�tres :
 *      int startLine : Ligne o� d�marre l'ensemble des informations de l'entit�.
 *      FILE* sourceFile : pointeur de fichier du fichier concern�.
 * Retour :
 *      Succ�s : Renvoie une liste cha�n�e de lignes.
 *      �chec  : Renvoie NULL
 */
listOfLines* getEntity(int startLine, FILE* sourceFile) {
    int i;
    char tempStr[MAX];
    lineStruct line;
    listOfLines* resultList;

    resultList = NULL;
    if(sourceFile != NULL) {
        if(fGoToLine(startLine, sourceFile)) {
            while(freadL(tempStr, MAX, sourceFile) && verifLine(tempStr) && countTab(tempStr) != 0) {
                line = getLineStruct(tempStr);
                resultList = addLineToList(resultList, line);
                displayListOfLines(resultList);
            }
            fseek(sourceFile, -strlen(tempStr)-2, SEEK_CUR);
            fileLineCounter--;
        }
    }
    freeListOfLines(resultList);
    return NULL;
}




/**
 * Description : Renvoie l'ensemble des entit� ayant la clef pass�e en param�tre valant la valeur donn�e.
 * Param�tres :
 *      char* key : Clef � rechercher
 *      char* value : Valeur que la clef doit avoir.
 *      FILE* sourceFile : Pointeur de fichier du fichier concern�.
 * Retour :
 *      Succ�s : Renvoie la liste cha�n�e de tous les blocs de donn�es contenant la clef � la valeur correspondante.
 *      �chec  : Renvoie NULL.
 */
listOfEntities* getBlockWhere(char* key, char* value, FILE* sourceFile) {
	int fileSize;
	int tabulation;
	int startingLine;
	char line[MAX];
	listOfEntities* entities;

	fileSize     = fSize(sourceFile);
    fileLineCounter  = 0;
    startingLine = 0;

    while(ftell(sourceFile) < fileSize) {                   // Parcours du fichier
        if(freadL(line, MAX, sourceFile)) {                 // Lecture d'une ligne du fichier
            if(verifLine(line)) {                           // Si la ligne peut �tre trait�e.
                tabulation = countTab(line);
                if(tabulation == 0) {                       // Si d�but d'entit�
                    printf("Start of entity found at line %d\n", fileLineCounter);
                    startingLine = fileLineCounter;             // On enregistre la ligne de d�but de l'entit�
                } else {
                    printf("Recovering entity : \n");
                    getEntity(startingLine+1, sourceFile);  // R�cup�ration de l'entit�
                    printf("Entity recovered.\n");
                    system("pause >NULL");
                }
            }
        }
    }
    return NULL;
}




/* FONCTION DE GESTION DE LISTE CHAIN�E DES BLOC DE DONN�ES */
