#include "../parserYAML.h"

#ifndef MAX
    #define MAX 255     // Taille maximum utilée pour les chaine de caractères non dynamiques.
#endif // MAX



/**
 * Description : Cherche une chaîne de caractères dans un fichier.
 *               Pour ce faire, lit un chaine dans le fichier de la taille de la chaine recherchée.
 *               Si la chaine ne correspond pas, on avance d'un caractère et on recommence.
 * Renvoi :
 *      Succès : renvoie 1 et place le curseur à la fin de la chaine.
 *      Echec  : renvoie -1 et ne bouge pas le curseur si atteint la fin du fichier sans trouver.
 * Paramètres :
 *      FILE* sourceFile :  Pointeur de fichier du fichier concerné.
 *      char* string :      Chaîne de caractère à rechercher dans le fichier.
*/
int fSearchStr(FILE *sourceFile, char *string) {
	char test[MAX];
	int prevCursor;
	int initialCursor;
	int size;

	size = fileSize(sourceFile)
	initialCursor = ftell(sourceFile);

	while(ftell(sourceFile) < size) {   // Tant que l'on n'est pas à la fin du fichier.
		prevCursor = ftell(sourceFile);                 // Sauvegarde de la position du curseur avant la recherche
		fread(test, 1, strlen(string), sourceFile);     // Lecture dans le fichier de N caractère. N étant la taille de la chaîne recherchée.\
                                                            Enregistre le résultat dans char test.
		test[strlen(string)] = '\0';                    // fread ne gère pas la '\0'.

		/* Vérification de la chaîne lue */
		if(stricmp(test, string) == 0) {
			return 1;   // Si identique
		} else {
            fseek(sourceFile, prevCursor, SEEK_SET);    // Si non, on retourne où l'on était.
            fseek(sourceFile, 1, SEEK_CUR);             // On avance d'un cran dans le fichier et on recommence.
		}
	}
	fseek(sourceFile, initialCursor, SEEK_SET);
	return -1;

	/* NB : PEUT ÊTRE AMÉLIORÉE AVEC DE LA RÉCURSIVITÉ */
}


/**
 * Description : Cherche un unique caractère dans un fichier avec un délimiteur.
 * Renvoi :
 *      Succès : renvoie 1 et place le curseur après le caractère.
 *      Echec  :
 *          Fin de fichier:         renvoie -1 et ne bouge pas le curseur.
 *          Délimiteur atteint :    renvoie 0 et met le délimiteur après le délimiteur.
 * Paramètres :
 *      FILE* sourceFile : pointeur de fichier du fichier concerné.
 *      char wantedChar  : caractère à rechercher dans le fichier.
 *      char delimiter   : caractère auquel arrêter la recherche
*/
int fSearchChar(FILE *sourceFile, char wantedChar, char delimiter) {
    char test;
	int initialCursor;
	int size;

	size = fileSize(sourceFile)
	initialCursor = ftell(sourceFile);

	while(ftell(sourceFile) < size) {   // Tant que l'on n'est pas à la fin du fichier.
        test = fgetc(fileSource);

		/* Vérification de la chaîne lue */
		if(test == wantedChar) {
			return 1;   // Si identique
		} else if(test == delimiter) {
		    return 0;   // Si delimiteur atteint
		} else {
            fseek(sourceFile, prevCursor, SEEK_SET);    // Si non, on retourne où l'on était.
            fseek(sourceFile, 1, SEEK_CUR);             // On avance d'un cran dans le fichier et on recommence.
		}
	}
	fseek(sourceFile, initialCursor, SEEK_SET);         // Retour à la position initiale
	return -1;
}


void getValue(FILE* fileSource, char* wantedElement, char* destination) {
    if ( fSearchStr(fileSource, wantedElement) ) {      // Cherche l'élément voulu
        if(fSearchChar(fileSource, ':', '\n')) {
            if(fSearchChar(fileSource, '>', ':')) {

            } else if(fSearchChar(fileSource, '|', ':')) {

            } else if(fSearchChar(fileSource, '>', ':')) {

            } else if(fSearchChar(fileSource, '-', ':')) {

            } else {

            }
        }
    }

}
