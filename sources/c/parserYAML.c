#include <stdio.h>
#include <string.h>
#include "../h/struct.h"
#include "../h/some_funct.h"
#include "../h/parserYAML.h"

#ifndef MAX
    #define MAX 255     // Taille maximum util�e pour les chaine de caract�res non dynamiques.
#endif // MAX

/**
 * Description : Ajoute un �l�ment � une liste cha�n�e de type `tableEntity`
 * Param�tre(s) :
 *      tableEntity* list : pointeur du d�but de la liste cha�n�e.
 *      value : valeur � ajouter dans le nouvel �l�ment
 * Retour :
 *      Succ�s : pointeur vers la liste cha�n�e mise � jour.
 *      �chec  : en cas d'erreur d'allocation, renvoie la liste non mise � jour.
 *
 */
tableEntity* ll_addAtEnd(tableEntity* list, char* value) {
    tableEntity* new_element;
    tableEntity* temp;

    new_element = malloc(sizeof(list));     // Allocation n�cessaire pour le nouvel �l�ment.
    if(new_element != NULL) {               // Si l'allocation s'est bien pass�e.
        strcpy(new_element->line, value);   // On affecte la valuer pass�e en argument � l'attribut du nouvel �lement correspondant.
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
 * Description : Lit un ligne dans un fihcier donn�e et la renvoie dans la cha�ne pass�e en argument.
 *               `fgets` a pour d�faut d'avoir un saut de ligne ('\n') en fin de cha�ne.
 *               `freadL` (la fonction ci-dessous) a pour unique but de palier � ce d�faut.
 * Param�tres :
 *      FILE* sourceFile : Pointeur du fichier concern�.
 *      unsigned int sizeMax : nombre de caract�res � lire.
 *      char* destination : cha�ne dans laquelle stock�e la ligne lu.
 * Retour :
 *      Succ�s : renvoie 1
 *      Echec  : renvoie 0
 * Remarque : Pas de gestion de la position du pointeur.
 */
int freadL(FILE* sourceFile, unsigned int sizeMax, char* destination) {
    int strLength;
    char result[MAX];

    if(sourceFile != NULL) {
        if(fgets(result, sizeMax, sourceFile) != NULL) {        // Lecture d'un ligne dans le fichier
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
    return 1;   // Si aucun des cas ci dessus, alors la ligne peut �tre traiter.
}


/**
 * Description : V�rifie que la ligne pass�e en argument contient bien une clef.
 *               Pour ce faire, parcours le fichier � la recherche d'occurences.
 *               D�s qu'une est trouv�e, on v�rifie qu'il n'y a rien avant et rien apr�s hormis des espace ou des caract�res autoris� ('-' et ':')
 * Param�tres :
 *      char* line : cha�ne contenant la ligne lue.
 *      char* wantedStr : cha�ne recherch�e
 * Retour :
 *      Succ�s : 1
 *      �chec  : 0
 */
int isKey(char* line, char* wantedStr) {
    int i;
    int findStrIndex;
    char* temp;

    if(line != NULL && wantedStr != NULL) {
        if((temp = strstr(line, wantedStr))) {          // `strstr` renvoie un pointeur correspondant � la position (ou l'adresse) de la premi�re occurence de la valeur cherch�e dans la cha�ne donn�e.
            findStrIndex = temp-line;                   // Par cons�quent soustraire cette valeur � l'adresse de la cha�ne dans laquelle on a cherch�; cela nous donne l'index o� se trouve l'occurence.
            /* V�rification des caract�re avant occurence */
            for(i=0 ; i < findStrIndex ; i++) {         // Parcourt de la cha�ne jusqu'� l'findStrIndex (jusqu'� l'occurence)
                if(line[i] != ' ' && line[i] != '-') {  // Si l'un des caract�re se trouvant avant l'occurence est incorrect
                    return 0;                           // Pas une clef
                }
            }
            /* V�rification des caract�res apr�s occurence */
            if( (temp = strchr(line, ':')) ) {          // Une clef a forc�ment un ':' apr�s elle. On v�rifie qu'il y a ce caract�re sur la m�me ligne.
                /* Boucle jusqu'� ':' */
                for(i=findStrIndex+strlen(wantedStr) ; i < temp-line ; i++) {  // `findStrIndex+strlen(wantedStr)` est l'index de la fin de l'occurence. `temp-line` correspond � l'index o� se trouve le ':'
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
 * Description : Fonction pr�te � lire une valeur dans le fichier � partir d'un curseur. Appel�e par fSearchKey uniquement.
 * Param�tres :
 *      FILE* sourceFile : pointeur de fichier du fichier concern� avec le curseur pr�-positionner � l'endroit convenu (juste devant la valeur).
 *      char* destination : cha�ne de caract�re dans laquelle sotcker la valeur lue.
 * Retour :
 *      Succ�s : 1
 *      �chec  : 0
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
            case '|':   // Bloc lit�ral
                break;
            case '>':   // Bloc repli�
                break;
            case '"':    // Text sur une ligne
                break;
            default:    // Valeur classique
                strcpy(destination, line);
                return 1;
        }
    }
    return 0;
}






/**
 * Description : Cherche un la premi�re occurence d'un clef dans un fichier et renvoie sa valeur.
 * Param�tres :
 *      FILE* sourceFile : Pointeur de fichier du fichier concern�.
 *      char* key : Cha�ne de caract�re � rechercher dans le fichier.
 *      char* destination : Cha�ne de caract�re dans laquelle enregistrer la valeur trouv�e.
 * Retour :
 *      Succ�s : met la valeur dans destination.
 *      Echec  : assigne NULL dans destination.
 * Remarque : Peut �tre am�lior�e ou d�riv�e en une fonction renvoyant les valeurs de chaque occurences.
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

    while(ftell(sourceFile) < fileSize) {
        if(freadL(sourceFile, MAX, line)) {
            if(verifLine(line)) {
                if(insideText) {
                    if((tempInt = countTab(line)) < lastCorrectTab) {
                        lastCorrectTab = tempInt;
                        insideText = 0;
                    }
                } else {
                    if(strchr(line, '>') || strchr(line, '|')) {
                        lastCorrectTab = countTab(line);
                        insideText = 1;
                    } else if(isKey(line, key)) {
                        tempInt = 0;
                        while(line[tempInt] != ':') {
                            tempInt++;
                        }
                        while(line[tempInt] == ' ') {
                            tempInt++;
                        }
                        fseek(sourceFile, -strlen(line)+tempInt, SEEK_CUR);
                        getValue(sourceFile, destination);
                        break;
                    }
                }
            }
        }
    }
}
