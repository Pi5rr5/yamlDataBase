#include <stdio.h>
#include <string.h>
#include "../h/struct.h"
#include "../h/some_funct.h"
#include "../h/parserYAML.h"

#ifndef MAX
    #define MAX 255     // Taille maximum utilée pour les chaine de caractères non dynamiques.
#endif // MAX

/**
 * Description : Ajoute un élément à une liste chaînée de type `tableEntity`
 * Paramètre(s) :
 *      tableEntity* list : pointeur du début de la liste chaînée.
 *      value : valeur à ajouter dans le nouvel élément
 * Retour :
 *      Succès : pointeur vers la liste chaînée mise à jour.
 *      Échec  : en cas d'erreur d'allocation, renvoie la liste non mise à jour.
 *
 */
tableEntity* ll_addAtEnd(tableEntity* list, char* value) {
    tableEntity* new_element;
    tableEntity* temp;

    new_element = malloc(sizeof(list));     // Allocation nécessaire pour le nouvel élément.
    if(new_element != NULL) {               // Si l'allocation s'est bien passée.
        strcpy(new_element->line, value);   // On affecte la valuer passée en argument à l'attribut du nouvel élement correspondant.
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
 * Description : Lit une ligne dans un fihcier donnée et la renvoie dans la chaîne passée en argument.
 *               `fgets` a pour défaut d'avoir un saut de ligne ('\n') en fin de chaîne.
 *               `freadL` (la fonction ci-dessous) a pour unique but de palier à ce défaut.
 * Paramètres :
 *      FILE* sourceFile : Pointeur du fichier concerné.
 *      unsigned int sizeMax : nombre de caractères à lire.
 *      char* destination : chaîne dans laquelle stockée la ligne lu.
 * Retour :
 *      Succès : renvoie 1
 *      Echec  : renvoie 0
 * Remarque : Pas de gestion de la position du pointeur.
 */
int freadL(FILE* sourceFile, unsigned int sizeMax, char* destination) {
    int strLength;
    char result[MAX];

    if(sourceFile != NULL) {
        if(fgets(result, sizeMax, sourceFile) != NULL) {        // Lecture d'un ligne dans le fichier
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
 * Description : Vérifie que la ligne passée en argument contient bien une clef.
 *               Pour ce faire, parcours le fichier à la recherche d'occurences.
 *               Dès qu'une est trouvée, on vérifie qu'il n'y a rien avant et rien après hormis des espaces ou des caractères autorisés ('-' et ':')
 * Paramètres :
 *      char* line : chaîne contenant la ligne lue.
 *      char* wantedStr : chaîne recherchée.
 * Retour :
 *      Succès : 1
 *      Échec  : 0
 */
int isKey(char* line, char* wantedStr) {
    int i;
    int findStrIndex;
    char* temp;

    if(line != NULL && wantedStr != NULL) {
        if((temp = strstr(line, wantedStr))) {          // `strstr` renvoie un pointeur correspondant à la position (ou l'adresse) de la première occurence de la valeur cherchée dans la chaîne donnée.
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
                for(i=findStrIndex+strlen(wantedStr) ; i < temp-line ; i++) {  // `findStrIndex+strlen(wantedStr)` est l'index de la fin de l'occurence. `temp-line` correspond à l'index où se trouve le ':'
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
 * Description : Fonction prête à lire une valeur dans le fichier à partir d'un curseur. Appelée par `fSearchKey` uniquement.
 * Paramètres :
 *      FILE* sourceFile : pointeur de fichier du fichier concerné avec le curseur pré-positionné à l'endroit convenu (juste devant la valeur).
 *      char* destination : chaîne de caractères dans laquelle sotcker la valeur lue.
 * Retour :
 *      Succès : 1
 *      Échec  : 0
 */
int getValue(FILE* sourceFile, char* destination) {
    int i;
    int tempInt;
    char tempChar;
    char line[MAX];
    char* tempCharPointer;

    if(sourceFile != NULL) {
        freadL(sourceFile, MAX, line);
        switch(line[0]) {
            case '|':   // Bloc litéral
                break;
            case '>':   // Bloc replié
                break;
            case '\'':  // Texte sur une ligne simple quote
                break;
            case '"':   // Texte sur une ligne double quote
                break;
            default:    // Valeur classique
                strcpy(destination, line);
                return 1;
        }
    }
    return 0;
}






/**
 * Description : Cherche la première occurence d'une clef dans un fichier et renvoie sa valeur.
 * Paramètres :
 *      FILE* sourceFile : Pointeur de fichier du fichier concerné.
 *      char* key : Chaîne de caractères à rechercher dans le fichier.
 *      char* destination : Chaîne de caractères dans laquelle enregistrer la valeur trouvée.
 * Retour :
 *      Succès : met la valeur dans destination.
 *      Echec  : assigne NULL dans destination.
 * Remarque : Peut être améliorée ou dérivée en une fonction renvoyant les valeurs de chaque occurence.
 */
void getKeyValue(FILE *sourceFile, char *key, char* destination) {
    int tempInt;
	int fileSize;
	int insideText;
	int lastCorrectTab;
	char line[MAX];

    insideText     = 0;
    lastCorrectTab = 0;
	fileSize       = fSize(sourceFile);

    while(ftell(sourceFile) < fileSize) {       // Parcours du fichier
        if(freadL(sourceFile, MAX, line)) {     // Lecture d'une ligne du fichier
            if(verifLine(line)) {               // Si la ligne peut être traitée.
                if(insideText) {                // insideText` est un booléen qui passe à `true` lorsqu'une syntaxe de valeur texte est détectée (cf. ligne 209).
                    if((tempInt = countTab(line)) < lastCorrectTab) {   // Avant de rentrer dans une valeur texte, on enregistre la tabulation actuelle. A partir du moment où l'on revient à, ou que l'on souspasse, cette tabulatio, c'est qu'on sort de la valeur texte.
                        lastCorrectTab = tempInt;                       // On met à jour la tabulation actuelle.
                        insideText = 0;                                 // Le booléen repasse à `false`.
                    } else {
                        continue;                                       // On passe à la ligne suivante.
                    }
                }   // Si la ligne lue n'est pas une valeur texte
                if(strchr(line, '>') || strchr(line, '|')) {            // /!\ ERREUR /!\ recherche un délimiteur de texte dans la ligne mais ne prend pas en compte le fait qu'il puisse être dans un valeur texte.
                    lastCorrectTab = countTab(line);                    // On met à jour la tabulation actuelle.
                    insideText = 1;                                     // Le booléen de texte passe à `true`.
                } else if(isKey(line, key)) {           // Vérification si la ligne contient une clef (optionnel en soi, mais plus sécurisé).
                    /* On veut se mettre juste avant la valeur */
                    tempInt = 0;
                    while(line[tempInt] != ':') {       // Déplacement jusqu'au ':' de la clef /!\ WARNING /!\ si la clef comprend ':', la suite ne fonctionnera pas comme il faut.
                        tempInt++;
                    }
                    while(line[tempInt] == ' ') {       // Déplacement jusqu'au premier caractère de la valeur.
                        tempInt++;
                    }
                    fseek(sourceFile, -strlen(line)+tempInt, SEEK_CUR);     // Déplacement du curseur juste avant la valeur.
                    getValue(sourceFile, destination);                      // Récupération de la valeur.
                    break;
                }
            }
        }
    }
}
