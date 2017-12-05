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
extern int FILE_LINE_COUNTER;     // Extern est utlis� pour les globales uniquement.\
                                    Il permet au compilateur de signaler que cette variable a peut �tre d�j� �t� d�clar�e qulquepart.\
                                    Il parcourt alors les fichiers (donc un peu co�teux en ressources)\
                                    et s'il trouve une autre d�claration qui a d�j� �t� ex�cut�e,\
                                    alors il ne recr�e pas la globale.



/* ----- FUNCTIONS ----- */

/**
 * @name addLineToList
 *
 * @brief Ajoute un �l�ment � une liste cha�n�e de type `listOfLines`
 *
 * @param listOfLines* list : pointeur du d�but de la liste cha�n�e.
 * @param value : valeur � ajouter dans le nouvel �l�ment
 *
 * @return (on success) : pointeur vers la liste cha�n�e mise � jour.
 * @return (on failure) : en cas d'erreur d'allocation, renvoie la liste non mise � jour.
 */
listOfLines* addLineToList(listOfLines* list, lineStruct line) {
    listOfLines* new_element;
    listOfLines* temp;

    new_element = malloc(sizeof(listOfLines));     // Allocation n�cessaire pour le nouvel �l�ment.
    if(new_element != NULL) {               // Si l'allocation s'est bien pass�e.
        if(DEBUG_PRINT) printf("Adding to list : '%s' as key and '%s' as value.\n", line.key, line.value);
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
 * @name addEntityToList
 *
 * @brief Ajoute un �l�ment � une liste cha�n�e de type `listOfEntities`
 *
 * @param listOfEntities* list : pointeur du d�but de la liste cha�n�e.
 * @param value : valeur � ajouter dans le nouvel �l�ment
 *
 * @return (on success) : pointeur vers la liste cha�n�e mise � jour.
 * @return (on failure) : en cas d'erreur d'allocation, renvoie la liste non mise � jour.
 */
listOfEntities* addEntityToList(listOfEntities* list, listOfLines* entity) {
    listOfEntities* new_element;
    listOfEntities* temp;

    new_element = malloc(sizeof(listOfEntities));     // Allocation n�cessaire pour le nouvel �l�ment.
    if(new_element != NULL) {               // Si l'allocation s'est bien pass�e.
        new_element->entity = entity;       // On affecte la valeur pass�e en argument � l'attribut du nouvel �lement correspondant.
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
 * @name displayListOfLines
 *
 * @brief Affiche tous les �l�ments d'une liste cha�n�e de type listOfLines.
 *          Servira seulement pour du d�boggage.
 *
 * @param listOfLines* list : liste cha�n�e concern�e.
 *
 * @return void
 */
void displayListOfLines(listOfLines* list) {
    listOfLines* temp;

    printf("\tList of lines :\n");
    if(list != NULL) {
        temp = list;
        while(temp->next != NULL) {
            printf("\t\tkey :%s\n\t\tvalue :%s\n", temp->line.key, temp->line.value);
            temp = temp->next;
        }
        printf("\t\tkey :%s\n\t\tvalue :%s\n", temp->line.key, temp->line.value);
    } else {
        error("\t\tListe vide.");
    }
    printf("\tEnd of list.\n\n");
}




/**
 * @name displayListOfEntities
 *
 * @brief Affiche tous les �l�ments d'une liste cha�n�e de type listOfEntities.
 *          Servira seulement pour du d�boggage.
 *
 * @param listOfEntities* list : liste cha�n�e concern�e.
 *
 * @return void
 */
void displayListOfEntities(listOfEntities* list) {
    listOfEntities* temp;

    printf("\nList of entitites :\n");
    if(list != NULL) {
        temp = list;
        while(temp->next != NULL) {
            displayListOfLines(temp->entity);
            temp = temp->next;
        }
        displayListOfLines(temp->entity);
    } else {
        error("\tListe vide.\n");
    }
    printf("End of list.\n\n");
}




/**
 * @name freeListOfLines
 *
 * @brief lib�re tout l'espace m�moire pris par la liste cha�n�e.
 *
 * @param listOfLines list : liste cha�n�e concern�e.
 *
 * @return void.
 */
void freeListOfLines(listOfLines* list) {
    listOfLines* temp;
    listOfLines* temp2;

    if(list != NULL) {
        temp  = list;
        temp2 = list;
        while(temp->next != NULL) {
            temp2 = temp;
            if(temp2 != NULL)
                free(temp2);
            temp = temp->next;
        }
        if(temp != NULL)
            free(temp);
    }
}




/**
 * @name displayListOfEntities
 *
 * @brief Lib�re tout l'espace m�moire pris par la liste cha�n�e
 *
 * @param listOfEntities* list : list cha�n�e
 *
 * @return void.
 */
void freeListOfEntities(listOfEntities* list) {
    listOfEntities* temp;       // Curseur ayant un cran d'avance (cf. paragraphe d'explication ci-dessous
    listOfEntities* temp2;      // Curseur "lib�rateur de m�moire"

    /*
        Pour lib�rer l'espace m�moire d'une liste cha�n�e, deux curseurs sont n�cessaire.
        Un des curseur parcours la liste �l�ment par �l�ment en lib�rant leur espace m�moire les hein apr�s les autres.
        Seulement en lib�rant cet espace m�moire, on perd tout trace de l'�l�ment suivant de la liste.
        C'est pouruqoi on utilise un second curseur qui sera un cran en avant dans les �l�ment, poru pouvoir continuer de lib�rer la cha�ne.
    */
    if(list != NULL) {
        temp  = list;
        temp2 = list;
        while(temp->next != NULL) {
            temp2 = temp;
            if(temp2 != NULL) {                 // Simple s�curit�, le cas contraire ne devrait jamais arriver
                freeListOfLines(temp2->entity); // Lib�ration m�moire de l'ensensemble de l'�l�ment (lui m�me �tant une liste cha�n�e d'un autre type)
                free(temp2);
            }
            temp = temp->next;
        }
        freeListOfLines(temp->entity);
        if(temp != NULL)
            free(temp);
    }
}




/**
 * @name freadL
 *
 * @brief Lit une ligne dans un fihcier donn�e et la renvoie dans la cha�ne pass�e en argument.
 *               `fgets` a pour d�faut d'avoir un saut de ligne ('\n') en fin de cha�ne.
 *               `freadL` (la fonction ci-dessous) a pour unique but de palier � ce d�faut.
 *
 * @param char* destination : cha�ne dans laquelle stock�e la ligne lue.
 * @param unsigned int sizeMax : nombre de caract�res � lire.
 * @param FILE* sourceFile : Pointeur du fichier concern�.
 *
 * @return (on success) 1
 * @return (on failure) 0
 *
 * @remarks Pas de gestion de la position du pointeur.
 */
int freadL(char* destination, unsigned int sizeMax, FILE* sourceFile) {
    int strLength;
    char result[MAX];

    if(sourceFile != NULL) {
        if(fgets(result, sizeMax, sourceFile) != NULL) {    // Lecture d'un ligne dans le fichier
            FILE_LINE_COUNTER++;
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
 * @name verifLine
 *
 * @brief V�rifie que la ligne en question est bien � traiter.
 *
 * @param char* str : cha�ne de caract�res concernc�e.
 *
 * @return (on success) 1
 * @return (on failure) 0
 */
int verifLine(char* str) {

    // Empty string
    if(str == NULL || strlen(str) == 0)
        return 0;

    // D�but de fichier
    if(strcmp(str, "---") == 0      // Le symbole de d�but de fichier est "---"
    || strcmp(str, "---\n") == 0    // Il peut �tre suivit d'une saut de ligne
    || strcmp(str, "---\r\n") == 0) // Autre �criture du saut de ligne possible.
        return 0;

    // Fin de fichier
    if(strcmp(str, "...") == 0      // Le symbole de fin de fichier est "..."
    || strcmp(str, "...\n") == 0    // Peut �tre suivit d'un saut de ligne.
    || strcmp(str, "...\r\n") == 0) // Autre �criture du saut de ligne possible (d�pend du fichier).
        return 0;

    // Commentaire ou ligne vide
    if(str[0] == '#' || str[0] == '\n' || str[0] == '\r')
        return 0;

    return 1;   // Si aucun des cas ci-dessus, alors la ligne peut �tre trait�e.
}




/**
 * @name hasKey
 *
 * @brief V�rifie que la ligne pass�e en argument contient bien une clef donn�e.
 *               Pour ce faire, parcours le fichier � la recherche d'occurences.
 *               D�s qu'une est trouv�e, on v�rifie qu'il n'y a rien avant et rien apr�s hormis des espaces ou des caract�res autoris�s ('-' et ':')
 *
 * @param char* line : cha�ne contenant la ligne lue.
 * @param char* key : cha�ne recherch�e.
 *
 * @return (on success) 1
 * @return (on failure) 0
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
 * @name getKey
 *
 * @brief prend une ligne de donn�es YAML en param�tre et retourne la clef qui s'y trouve.
 *
 * @param char* line : ligne YAML concern�e.
 *
 * @return (on success) char* result : clef obtenue.
 * @return (on failure) NULL
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
    if(DEBUG_PRINT) printf("Key recovered : %s\n", result);
    return result;
}




/**
 * @name getValue
 *
 * @brief Prends une ligne de YAML en param�tre et renvoie la valeur qui s'y trouve.
 *
 * @param char* destination : cha�ne de caract�res dans laquelle sotcker la valeur.
 * @param char* line : ligne de YAML � traiter.
 *
 * @return (on success) char* : valeur obtenue
 * @return (on failure) char* : ""
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
            if(DEBUG_PRINT) printf("Value recovered : %s\n", line+tempInt);
            return line+tempInt;
    }
    if(DEBUG_PRINT) printf("Value recovered : \"\"\n");
    return "";
}




/**
 * @name getLineStruct
 *
 * @brief Prend une ligne de donn�e YAML en param�tre et renvoie un objet `line` contenant sa clef et sa valeur.
 *
 * @param char* str : cha�n� de caract�re de la ligne YAML concern�e.
 *
 * @return (on success) lineStruct line : objet `line` contenant la clef et la valeur trouv�es.
 *
 * @remarks Cas d'�chec non g�r�.
 */
lineStruct getLineStruct(char* str) {
    lineStruct line;

    strcpy(line.key, getKey(str));      // R�cup�re la clef de la ligne
    strcpy(line.value, getValue(str));  // R�cup�re la valeur correspondante
    return line;
}




/**
 * @name getEntity
 *
 * @brief R�cup�re l'int�gralit� d'une entit�.
 *
 * @param int startLine : Ligne o� d�marre l'ensemble des informations de l'entit�.
 * @param FILE* sourceFile : pointeur de fichier du fichier concern�.
 *
 * @return (on success) listOfLines* resultList : list cha�n�e de lignes.
 * @return (on failure) NULL.
 */
listOfLines* getEntity(int startLine, FILE* sourceFile) {
    char tempStr[MAX];
    lineStruct line;
    listOfLines* resultList;

    resultList = NULL;
    if(sourceFile != NULL) {
        if(fGoToLine(startLine, sourceFile)) {
            while(freadL(tempStr, MAX, sourceFile) && verifLine(tempStr) && countTab(tempStr) != 0) {
                line = getLineStruct(tempStr);
                resultList = addLineToList(resultList, line);
            }
            fseek(sourceFile, -strlen(tempStr)-2, SEEK_CUR);
            FILE_LINE_COUNTER--;
        } else {
            if(DEBUG_PRINT) printf("Line change failed.\n");
        }
    } else {
        if(DEBUG_PRINT) printf("Source file not found.\n");
    }
    return resultList;
}




/**
 * @name getBlockWhere
 *
 * @brief Renvoie l'ensemble des entit� ayant la clef pass�e en param�tre valant la valeur donn�e.
 *
 * @param char* key : Clef � rechercher
 * @param char* value : Valeur que la clef doit avoir.
 * @param FILE* sourceFile : Pointeur de fichier du fichier concern�.
 *
 * @return (on success) listOfEntities* entities : liste cha�n�e d'entit�es ayant la clef et la valeur correspondantes.
 * @return (on failure) NULL.
 */
listOfEntities* getBlockWhere(char* key, char* value, FILE* sourceFile) {
	int fileSize;
	int tabulation;
	int startingLine;
	char line[MAX];
	char tempKey[MAX];
	char tempValue[MAX];
	listOfLines* tempEntity;
	listOfEntities* entities;

    entities = NULL;
	fileSize = fSize(sourceFile);
    startingLine = 0;
    FILE_LINE_COUNTER  = 0;

    while(ftell(sourceFile) < fileSize) {                   // Parcours du fichier
        if(freadL(line, MAX, sourceFile)) {                 // Lecture d'une ligne du fichier
            if(verifLine(line)) {                           // Si la ligne peut �tre trait�e.
                tabulation = countTab(line);
                if(tabulation == 0) {                       // Si d�but d'entit�
                    if(DEBUG_PRINT) printf("Start of entity found at line %d\n", FILE_LINE_COUNTER);
                    startingLine = FILE_LINE_COUNTER;       // On enregistre la ligne de d�but de l'entit�
                } else {
                    if(strcpy(tempKey, getKey(line)) != NULL) {
                        if(strcpy(tempValue, getValue(line)) != NULL) {
                            if(strcmp(tempKey, key) == 0 && strcmp(tempValue, value) == 0) {
                                if(DEBUG_PRINT) printf("Recovering entity : \n");
                                if((tempEntity = getEntity(startingLine+1, sourceFile)) != NULL) {
                                    if ( (entities = addEntityToList(entities, tempEntity)) == NULL) {             // R�cup�ration de l'entit�
                                        error("Error while adding entity from file.");
                                        break;
                                    } else {
                                        if(DEBUG_PRINT) printf("Entity recovered.\n");
                                    }
                                } else {
                                    error("Error while recovering entity.");
                                    break;
                                }
                            }
                        } else {
                            error("Error while recovering value.");
                            break;
                        }
                    } else {
                        error("Error while recovering key.");
                        break;
                    }
                }
            }
        }
    }
    if(DEBUG_PRINT) printf("\nEnd of process.\n");
    return entities;
}




/**
 * @name getAllFrom
 *
 * @brief R�cup�re l'ensemble des entit�s pr�sente dans une table.
 *
 * @param FILE* sourceFile : pointeur de fichier du fichier concern�.
 *
 * @return (on success) listOfEntities* entities :
 * @return (on failure) NULL
 *
 * @remarks Pas finie.
 */
listOfEntities* getAllFrom(FILE* sourceFile) {
    int fileSize;
    int tabulation;
    int startOfEntity;
    char tempStr[MAX];
    listOfLines* tempEntity;
    listOfEntities* entities;

    tabulation    = 0;
    startOfEntity = 0;
    tempEntity = NULL;

    if(sourceFile != NULL) {
        fileSize = fSize(sourceFile);
        FILE_LINE_COUNTER = 0;
        while(ftell(sourceFile) < fileSize) {
            if(freadL(tempStr, MAX, sourceFile)) {
                FILE_LINE_COUNTER++;
                if(verifLine(tempStr)) {
                    tabulation = countTab(tempStr);
                    if(tabulation == 0) {
                        if(DEBUG_PRINT)
                            printf("Start of entity found at line %d\n", FILE_LINE_COUNTER);
                        startOfEntity = FILE_LINE_COUNTER;             // On enregistre la ligne de d�but de l'entit�
                    } else {
                        if((tempEntity = getEntity(startOfEntity+1, sourceFile)) != NULL) {
                            if(addEntityToList(entities, tempEntity) != NULL) {
                                if(DEBUG_PRINT) {
                                    printf("Entity recovered.\n");
                                }
                            } else {
                                error("Error while adding entity to list.\n");
                            }
                        } else {
                            error("Error while recovering entity.\n");
                        }
                    }
                }
            }
            system("pause >nul");
        }
    }
    freeListOfEntities(entities);
    return NULL;
}



/* FONCTION DE GESTION DE LISTE CHAIN�E DES BLOC DE DONN�ES */
