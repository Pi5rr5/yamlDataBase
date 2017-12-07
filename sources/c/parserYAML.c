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
extern int FILE_LINE_COUNTER;     // Extern est utlisé pour les globales uniquement.\
                                    Il permet au compilateur de signaler que cette variable a peut être déjà été déclarée qulquepart.\
                                    Il parcourt alors les fichiers (donc un peu coûteux en ressources)\
                                    et s'il trouve une autre déclaration qui a déjà été exécutée,\
                                    alors il ne recrée pas la globale.



/* ----- FUNCTIONS ----- */

/**
 * @name addLineToList
 *
 * @brief Add an element to linked list typed as `listOfLines`
 *
 * @param listOfLines* list : pointer of the start of the linked list.
 * @param value : value to add in the new element.
 *
 * @return (on success) : pointer to the updated linked list.
 * @return (on failure) : if an allocation error occures, return a null pointer.
 */
listOfLines* addLineToList(listOfLines* list, lineStruct line) {
    listOfLines* new_element;
    listOfLines* temp;

    new_element = malloc(sizeof(listOfLines));     // Required allocation for the new elément.
    if(new_element != NULL) {               // If the allocation went well.
        if(DEBUG_PRINT) printf("Adding to list : '%s' as key and '%s' as value.\n", line.key, line.value);
        new_element->line = line;           // We assign the value passed in argument to the attribute
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
 * @name addEntityToList
 *
 * @brief Ajoute un élément à une liste chaînée de type `listOfEntities`
 *
 * @param listOfEntities* list : pointeur du début de la liste chaînée.
 * @param value : valeur à ajouter dans le nouvel élément
 *
 * @return (on success) : pointeur vers la liste chaînée mise à jour.
 * @return (on failure) : en cas d'erreur d'allocation, renvoie la liste non mise à jour.
 */
listOfEntities* addEntityToList(listOfEntities* list, listOfLines* entity) {
    listOfEntities* new_element;
    listOfEntities* temp;

    new_element = malloc(sizeof(listOfEntities));     // Allocation nécessaire pour le nouvel élément.
    if(new_element != NULL) {               // Si l'allocation s'est bien passée.
        new_element->entity = entity;       // On affecte la valeur passée en argument à l'attribut du nouvel élement correspondant.
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
 * @name displayListOfLines
 *
 * @brief Affiche tous les éléments d'une liste chaînée de type listOfLines.
 *          Servira seulement pour du déboggage.
 *
 * @param listOfLines* list : liste chaînée concernée.
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
 * @brief Affiche tous les éléments d'une liste chaînée de type listOfEntities.
 *          Servira seulement pour du déboggage.
 *
 * @param listOfEntities* list : liste chaînée concernée.
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
 * @brief libère tout l'espace mémoire pris par la liste chaînée.
 *
 * @param listOfLines list : liste chaînée concernée.
 *
 * @return void.
 */
void freeListOfLines(listOfLines** list) {
    listOfLines* temp;

    if(*list != NULL) {
        while( (temp = *list) != NULL ) {
        	*list = (*list)->next;
			free(temp);
        }
    }
}




/**
 * @name displayListOfEntities
 *
 * @brief Libère tout l'espace mémoire pris par la liste chaînée
 *
 * @param listOfEntities* list : list chaînée
 *
 * @return void.
 */
void freeListOfEntities(listOfEntities** list) {
    listOfEntities* temp;       		// Curseur temporaire qui pointe vers la valeur à libérer

    if(*list != NULL) {
        while ( (temp = *list) != NULL ) {
            *list = (*list)->next;
			freeListOfLines(&temp->entity);		// Libération mémoire de l'ensensemble de l'élément (lui même étant une liste chaînée d'un autre type)
			free(temp);
        }
    }
}




/**
 * @name freadL
 *
 * @brief Lit une ligne dans un fihcier donnée et la renvoie dans la chaîne passée en argument.
 *               `fgets` a pour défaut d'avoir un saut de ligne ('\n') en fin de chaîne.
 *               `freadL` (la fonction ci-dessous) a pour unique but de palier à ce défaut.
 *
 * @param char* destination : chaîne dans laquelle stockée la ligne lue.
 * @param unsigned int sizeMax : nombre de caractères à lire.
 * @param FILE* sourceFile : Pointeur du fichier concerné.
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
 * @name verifLine
 *
 * @brief Vérifie que la ligne en question est bien à traiter.
 *
 * @param char* str : chaîne de caractères concerncée.
 *
 * @return (on success) 1
 * @return (on failure) 0
 */
int verifLine(char* str) {
	char temp;

    // Empty string
    if(str == NULL || strlen(str) == 0)
        return 0;

    // Début de fichier
    if(strcmp(str, "---") == 0      // Le symbole de début de fichier est "---"
    || strcmp(str, "---\n") == 0    // Il peut être suivit d'une saut de ligne
    || strcmp(str, "---\r\n") == 0) // Autre écriture du saut de ligne possible.
        return 0;

    // Fin de fichier
    if(strcmp(str, "...") == 0      // Le symbole de fin de fichier est "..."
    || strcmp(str, "...\n") == 0    // Peut être suivit d'un saut de ligne.
    || strcmp(str, "...\r\n") == 0) // Autre écriture du saut de ligne possible (dépend du fichier).
        return 0;

    // Commentaire ou ligne vide
    while(fgetc(temp) == ' ');
    if(temp == '#' || temp == '\n' || temp == '\r')
        return 0;

    return 1;   // Si aucun des cas ci-dessus, alors la ligne peut être traitée.
}





/**
 * @name getKey
 *
 * @brief prend une ligne de données YAML en paramètre et retourne la clef qui s'y trouve.
 *
 * @param char* line : ligne YAML concernée.
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

    while(line[tempInt++] == ' ');                          // Trouve l'index du premier caractère n'étant pas un espace
    keyStart = tempInt;
    while(line[tempInt++] != ' ' && line[tempInt] != ':');  // Trouve l'index du premier caractère n'étant ni espace ni un ':'

    strncpy(result, line+keyStart-1, tempInt-keyStart);     // copie juste la clef dans result
    result[tempInt-keyStart] = '\0';                        // strncpy ne prend pas en charge le '\0', on le rajoute à la fin de la chaîne
    if(DEBUG_PRINT) printf("Key recovered : %s\n", result);
    return result;
}




/**
 * @name getValue
 *
 * @brief Prends une ligne de YAML en paramètre et renvoie la valeur qui s'y trouve.
 *
 * @param char* destination : chaîne de caractères dans laquelle sotcker la valeur.
 * @param char* line : ligne de YAML à traiter.
 *
 * @return (on success) char* : valeur obtenue
 * @return (on failure) char* : ""
 */
char* getValue(char* line) {
    int tempInt = 0;

    while(line[tempInt++] != ':');      // Déplacement jusqu'au ':' de la clef
    while(line[tempInt++] == ' ');      // Déplacement jusqu'au premier caractère de la valeur (inclu)

    switch(line[tempInt]) {           // Recule d'un cran avant
        case 39:    // Texte sur une ligne simple quote (39 en ASCII)
            break;
        case 34:    // Texte sur une ligne double quote (34 en ASCII)
            break;
        default:    // Valeur classique
            if(DEBUG_PRINT) printf("Value recovered : %s\n", line+tempInt);
            return line+tempInt-1;
    }
    if(DEBUG_PRINT) printf("Value recovered : \"\"\n");
    return "";
}




/**
 * @name getLineStruct
 *
 * @brief Prend une ligne de donnée YAML en paramètre et renvoie un objet `line` contenant sa clef et sa valeur.
 *
 * @param char* str : chaîné de caractère de la ligne YAML concernée.
 *
 * @return (on success) lineStruct line : objet `line` contenant la clef et la valeur trouvées.
 *
 * @remarks Cas d'échec non géré.
 */
lineStruct getLineStruct(char* str) {
    lineStruct line;

    strcpy(line.key, getKey(str));      // Récupère la clef de la ligne
    strcpy(line.value, getValue(str));  // Récupère la valeur correspondante
    return line;
}




/**
 * @name getEntity
 *
 * @brief Récupère l'intégralité d'une entité.
 *
 * @param int startLine : Ligne où démarre l'ensemble des informations de l'entité.
 * @param FILE* sourceFile : pointeur de fichier du fichier concerné.
 *
 * @return (on success) listOfLines* resultList : list chaînée de lignes.
 * @return (on failure) NULL.
 */
listOfLines* getEntity(int startLine, FILE* sourceFile) {
    char tempStr[MAX];
    lineStruct line;
    listOfLines* resultList;

	if(DEBUG_PRINT) printf("Recovering entity.\n");
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
    if(DEBUG_PRINT) printf("End of recover.\n");
    return resultList;
}




/**
 * @name getBlockWhere
 *
 * @brief Renvoie l'ensemble des entité ayant la clef passée en paramètre valant la valeur donnée.
 *
 * @param char* key : Clef à rechercher
 * @param char* value : Valeur que la clef doit avoir.
 * @param FILE* sourceFile : Pointeur de fichier du fichier concerné.
 *
 * @return (on success) listOfEntities* entities : liste chaînée d'entitées ayant la clef et la valeur correspondantes.
 * @return (on failure) NULL.
 *
 * @remarks si une erreur survient lors de la manipulation, renvoie tout de même les éléments trouvés.
 *			Danger non estimé et passé outre, à réviser.
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
    FILE_LINE_COUNTER = 0;

    while(ftell(sourceFile) < fileSize) {                   // Parcours du fichier
        if(freadL(line, MAX, sourceFile)) {                 // Lecture d'une ligne du fichier
            if(verifLine(line)) {                           // Si la ligne peut être traitée.
                tabulation = countTab(line);
                if(tabulation == 0) {                       // Si début d'entité
                    startingLine = FILE_LINE_COUNTER;       // On enregistre la ligne de début de l'entité
                } else {
                    if(strcpy(tempKey, getKey(line)) != NULL) {											// Récupération de la clef.
                        if(strcmp(tempKey, key) == 0) {													// Vérification, s'il s'agit de la clef voulue.
                            if(strcpy(tempValue, getValue(line)) != NULL) {								// Récupération de la valeur.
                                if(strcmp(tempValue, value) == 0) {										// Vérification s'il s'agit de la valeur recherchée.
                                    if((tempEntity = getEntity(startingLine+1, sourceFile)) != NULL) {	// Clef et valeur trouvées. Récupération de l'entité les contenant.
                                        if ( (entities = addEntityToList(entities, tempEntity)) == NULL) {  // Ajout de l'entité à la liste des entités ayant "matché".
                                            error("Error while adding entity from file.");				// Si erreur lors de la manipulation de la liste chaînée
                                            break;														// Sortie de fonction
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
                        }
                    } else {
                        error("Error while recovering key.");
                        break;
                    }
                }
            }
        }
    }
    return entities;
}




/**
 * @name getAllFrom
 *
 * @brief Récupère l'ensemble des entités présente dans une table.
 *
 * @param FILE* sourceFile : pointeur de fichier du fichier concerné.
 *
 * @return (on success) listOfEntities* entities :
 * @return (on failure) NULL
 *
 * @remarks Pas finie.
 */
listOfEntities* getAllFrom(FILE* sourceFile) {
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
    FILE_LINE_COUNTER = 0;

	if(sourceFile != NULL) {
		fseek(sourceFile, 0, SEEK_SET);
		while(ftell(sourceFile) < fileSize) {					// Parcours du fichier
			if(freadL(line, MAX, sourceFile)) {					// Lecture d'une ligne du fichier
				if(verifLine(line)) {							// Si la ligne peut être traitée.
					if( (tabulation = countTab(line)) == 0) {	// Si début d'entité
						if((tempEntity = getEntity(FILE_LINE_COUNTER+1, sourceFile)) != NULL) {		// Récupération de la prochaine entité.
							if ( (entities = addEntityToList(entities, tempEntity)) == NULL) {		// Ajout de l'entité à la liste des entités ayant "matché".
								error("Error while adding entity from file.");				// Si erreur lors de la manipulation de la liste chaînée
								break;														// Sortie de fonction
							}// Sinon, c'est que le block a correctement été récupéré.
						} else {
							error("Error while recovering entity.");
							break;
						}
					}
				}
			}
		}
	}
    return entities;
}

