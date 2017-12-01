#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../h/struct.h"
#include "../h/some_funct.h"
#include "../h/parserYAML.h"

#ifndef MAX
    #define MAX 255     // Taille maximum utilisée pour les chaines de caractères non dynamiques.
#endif // MAX

#ifndef DEBUG_PRINT
    #define DEBUG_PRINT 1
#endif // DEBUG_PRINT

/* ----- GLOBALS ----- */
extern int fileLineCounter;     // Extern est utlisé pour les globales uniquement.\
                                    Il permet au compilateur de signaler que cette variable a peut être déjà été déclarée qulquepart.\
                                    Il parcourt alors les fichiers (donc un peu coûteux en ressources)\
                                    et s'il trouve une autre déclaration qui a déjà été exécutée,\
                                    alors il ne recrée pas la globale.




/* ----- FUNCTIONS ----- */

/**
 * Description : Ajoute un élément à une liste chaînée de type `listOfLines`
 * Paramètre(s) :
 *      listOfLines* list : pointeur du début de la liste chaînée.
 *      value : valeur à ajouter dans le nouvel élément
 * Retour :
 *      Succès : pointeur vers la liste chaînée mise à jour.
 *      Échec  : en cas d'erreur d'allocation, renvoie la liste non mise à jour.
 */
listOfLines* addLineToList(listOfLines* list, lineStruct line) {
    listOfLines* new_element;
    listOfLines* temp;

    new_element = malloc(sizeof(listOfLines));     // Allocation nécessaire pour le nouvel élément.
    if(new_element != NULL) {               // Si l'allocation s'est bien passée.
        if(DEBUG_PRINT)
            printf("\tAdding to list : '%s' as key and '%s' as value.\n", line.key, line.value);
        new_element->line = line;           // On affecte la valeur passée en argument à l'attribut du nouvel élement correspondant.
        new_element->next = NULL;           // On fait pointer le pointeur de structure `next` à NULL, le nouvel élément devenant le dernier de la liste
        if(list == NULL) {                  // Si la liste donnée est vide.
            return new_element;             // On retourne le nouvel élément.
        } else {
            temp = list;                    // Sinon on ajoute le dernier élément à la fn de la liste
            while(temp->next != NULL) {     // Parcours de la liste.
                temp = temp->next;
            }
            temp->next = new_element;       // On fait pointer le dernier élément de la liste sur le nouvel élément.
            return list;                    // On retourne la liste mise  jour.
        }
    }
    return list;                            // Si erreur d'allocation, on retourne liste actuelle.
}




/**
 * Description : Affiche tous les éléments d'une liste chaînée de type listOfLines.
 *               Servira seulement pour du déboggage.
 * Parmètre(s) :
 *     listOfLines* list : liste chaînée concernée.
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
 * Description : libère tout l'espace mémoire pris par la liste chaînée.
 * Paramètres :
 *     listOfLines list : liste chaînée concernée.
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
 * Description : Lit une ligne dans un fihcier donnée et la renvoie dans la chaîne passée en argument.
 *               `fgets` a pour défaut d'avoir un saut de ligne ('\n') en fin de chaîne.
 *               `freadL` (la fonction ci-dessous) a pour unique but de palier à ce défaut.
 * Paramètres :
 *      char* destination : chaîne dans laquelle stockée la ligne lue.
 *      unsigned int sizeMax : nombre de caractères à lire.
 *      FILE* sourceFile : Pointeur du fichier concerné.
 * Retour :
 *      Succès : renvoie 1
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
            if(result[strLength-1] == '\n') {  // Si le dernier caractère avant le '\0' est un saut de ligne
                result[strLength-1] = '\0';    // On le remplace par un '\0'
                strcpy(destination, result);
            }
            return 1;
        }
    }
    return 0;
}



/**
 * Description : Vérifie que la ligne en question est bien à traiter.
 * Paramètre(s) :
 *      char* str : chaîne de caractères concerncée.
 * Retour :
 *      Succès : renvoie 1.
 *      Échec  :
 *          - Si la ligne est un commentaire ou une ligne vide, renvoie 0.
 *          - Si la ligne est le symbole de fin de fichier, ou s'il y a eu une erreur de base, renvoie -1.
 */
int verifLine(char* str) {
    // Le symbole de fin di fichier est "...". Il peut être suivit d'un saut de ligne ('\n'). Dans certains texte, le saut de ligne est en réalité "\r\n".
    if(str == NULL || strcmp(str, "...") == 0 || strcmp(str, "...\n") == 0 || strcmp(str, "...\r\n") == 0)
        return -1;
    // Si la ligne lue est un commentaire ou une ligne vide. (Là encore, il peut y avoir '\r' avant un saut de ligne)
    if(str[0] == '#' || str[0] == '\n' || str[0] == '\r')
        return 0;
    return 1;   // Si aucun des cas ci-dessus, alors la ligne peut être traiter.
}




/**
 * Description : Vérifie que la ligne passée en argument contient bien une clef donnée.
 *               Pour ce faire, parcours le fichier à la recherche d'occurences.
 *               Dès qu'une est trouvée, on vérifie qu'il n'y a rien avant et rien après hormis des espaces ou des caractères autorisés ('-' et ':')
 * Paramètres :
 *      char* line : chaîne contenant la ligne lue.
 *      char* key : chaîne recherchée.
 * Retour :
 *      Succès : 1
 *      Échec  : 0
 */
int hasKey(char* line, char* key) {
    int i;
    int findStrIndex;
    char* temp;

    if(line != NULL && key != NULL) {
        if((temp = strstr(line, key))) {                // `strstr` renvoie un pointeur correspondant à la position (ou l'adresse) de la première occurence de la valeur cherchée dans la chaîne donnée.
            findStrIndex = temp-line;                   // Par conséquent soustraire cette valeur à l'adresse de la chaîne dans laquelle on a cherché; cela nous donne l'index où se trouve l'occurence.
            /* Vérification des caractère avant occurence */
            for(i=0 ; i < findStrIndex ; i++) {         // Parcourt de la chaîne jusqu'à l'index (jusqu'à l'occurence)
                if(line[i] != ' ' && line[i] != '-') {  // Si l'un des caractères se trouvant avant l'occurence est incorrect
                    return 0;                           // Pas une clef
                }
            }
            /* Vérification des caractères après occurence */
            if( (temp = strchr(line, ':')) ) {          // Une clef a forcément un ':' après elle. On vérifie qu'il y a ce caractère sur la même ligne.
                /* Boucle jusqu'à ':' */
                for(i=findStrIndex+strlen(key) ; i < temp-line ; i++) {  // `findStrIndex+strlen(key)` est l'index de la fin de l'occurence. `temp-line` correspond à l'index où se trouve le ':'
                    if(line[i] != ' ') {                // Si l'un des caractères séparant l'occurence de ':' n'est pas un espace
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
 * Description : prend une ligne de données YAML en paramètre et retourne la clef qui s'y trouve.
 * Paramètre(s) :
 *      char* line : ligne YAML concernée.
 * Retour :
 *      Succès : Renvoie une chaîne de caractère contenant la clef.
 *      Échec  : Renvoie NULL.
 */
char* getKey(char* line) {
    int tempInt;
    int keyStart;
    char result[MAX];

    tempInt  = 0;
    keyStart = 0;

    while(line[tempInt++] == ' ');                          // Trouve l'index du premier caractère n'étant pas un espace
    keyStart = tempInt;
    while(line[tempInt++] != ' ' && line[tempInt] != ':');  // Trouve l'index du premier caractère n'étant ni espace ni un ':'

    strncpy(result, line+keyStart-1, tempInt-keyStart);     // copie juste la clef dans result
    result[tempInt-keyStart] = '\0';                        // strncpy ne prend pas en charge le '\0', on le rajoute à la fin de la chaîne
    if(DEBUG_PRINT)
        printf("\tKey recovered : %s\n", result);
    return result;
}




/**
 * Description : Prends une ligne de YAML en paramètre et renvoie la valeur qui s'y trouve.
 * Paramètes :
 *      char* destination : chaîne de caractères dans laquelle sotcker la valeur.
 *      char* line : ligne de YAML à traiter.
 * Retour :
 *      Succès : renvoie la valeur trouvée sous forme de chaîne de caractère.
 *      Échec  : renvoie une chaîne vide.
 */
char* getValue(char* line) {
    int tempInt = 0;

    while(line[tempInt++] != ':');      // Déplacement jusqu'au ':' de la clef /!\ WARNING /!\ si la clef comprend ':', la suite ne fonctionnera pas comme il faut.
    while(line[tempInt++] == ' ');      // Déplacement jusqu'au premier caractère de la valeur (inclu)

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
 * Description : Prend une ligne de donnée YAML en paramètre et renvoie un objet `line` contenant sa clef et sa valeur.
 * Paramètre(s) :
 *      char* str : chaîné de caractère de la ligne YAML concernée.
 * Retour :
 *      Succès : Renvoie un objet `line` avec la clef et la valeur de la donnée.
 */
lineStruct getLineStruct(char* str) {
    lineStruct line;
    char temp[MAX];

    strcpy(line.key, getKey(str));      // Récupère la clef de la ligne
    strcpy(line.value, getValue(str));  // Récupère la valeur correspondante
    return line;
}




/**
 * Description : Récupère l'intégralité d'une entité.
 * Paramètres :
 *      int startLine : Ligne où démarre l'ensemble des informations de l'entité.
 *      FILE* sourceFile : pointeur de fichier du fichier concerné.
 * Retour :
 *      Succès : Renvoie une liste chaînée de lignes.
 *      Échec  : Renvoie NULL
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
 * Description : Renvoie l'ensemble des entité ayant la clef passée en paramètre valant la valeur donnée.
 * Paramètres :
 *      char* key : Clef à rechercher
 *      char* value : Valeur que la clef doit avoir.
 *      FILE* sourceFile : Pointeur de fichier du fichier concerné.
 * Retour :
 *      Succès : Renvoie la liste chaînée de tous les blocs de données contenant la clef à la valeur correspondante.
 *      Échec  : Renvoie NULL.
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
            if(verifLine(line)) {                           // Si la ligne peut être traitée.
                tabulation = countTab(line);
                if(tabulation == 0) {                       // Si début d'entité
                    printf("Start of entity found at line %d\n", fileLineCounter);
                    startingLine = fileLineCounter;             // On enregistre la ligne de début de l'entité
                } else {
                    printf("Recovering entity : \n");
                    getEntity(startingLine+1, sourceFile);  // Récupération de l'entité
                    printf("Entity recovered.\n");
                    system("pause >NULL");
                }
            }
        }
    }
    return NULL;
}




/* FONCTION DE GESTION DE LISTE CHAINÉE DES BLOC DE DONNÉES */
