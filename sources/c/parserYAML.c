#include "../parserYAML.h"

#ifndef MAX
    #define MAX 255     // Taille maximum util�e pour les chaine de caract�res non dynamiques.
#endif // MAX



/**
 * Description : Cherche une cha�ne de caract�res dans un fichier.
 *               Pour ce faire, lit un chaine dans le fichier de la taille de la chaine recherch�e.
 *               Si la chaine ne correspond pas, on avance d'un caract�re et on recommence.
 * Renvoi :
 *      Succ�s : renvoie 1 et place le curseur � la fin de la chaine.
 *      Echec  : renvoie -1 et ne bouge pas le curseur si atteint la fin du fichier sans trouver.
 * Param�tres :
 *      FILE* sourceFile :  Pointeur de fichier du fichier concern�.
 *      char* string :      Cha�ne de caract�re � rechercher dans le fichier.
*/
int fSearchStr(FILE *sourceFile, char *string) {
	char test[MAX];
	int prevCursor;
	int initialCursor;
	int size;

	size = fileSize(sourceFile)
	initialCursor = ftell(sourceFile);

	while(ftell(sourceFile) < size) {   // Tant que l'on n'est pas � la fin du fichier.
		prevCursor = ftell(sourceFile);                 // Sauvegarde de la position du curseur avant la recherche
		fread(test, 1, strlen(string), sourceFile);     // Lecture dans le fichier de N caract�re. N �tant la taille de la cha�ne recherch�e.\
                                                            Enregistre le r�sultat dans char test.
		test[strlen(string)] = '\0';                    // fread ne g�re pas la '\0'.

		/* V�rification de la cha�ne lue */
		if(stricmp(test, string) == 0) {
			return 1;   // Si identique
		} else {
            fseek(sourceFile, prevCursor, SEEK_SET);    // Si non, on retourne o� l'on �tait.
            fseek(sourceFile, 1, SEEK_CUR);             // On avance d'un cran dans le fichier et on recommence.
		}
	}
	fseek(sourceFile, initialCursor, SEEK_SET);
	return -1;

	/* NB : PEUT �TRE AM�LIOR�E AVEC DE LA R�CURSIVIT� */
}


/**
 * Description : Cherche un unique caract�re dans un fichier avec un d�limiteur.
 * Renvoi :
 *      Succ�s : renvoie 1 et place le curseur apr�s le caract�re.
 *      Echec  :
 *          Fin de fichier:         renvoie -1 et ne bouge pas le curseur.
 *          D�limiteur atteint :    renvoie 0 et met le d�limiteur apr�s le d�limiteur.
 * Param�tres :
 *      FILE* sourceFile : pointeur de fichier du fichier concern�.
 *      char wantedChar  : caract�re � rechercher dans le fichier.
 *      char delimiter   : caract�re auquel arr�ter la recherche
*/
int fSearchChar(FILE *sourceFile, char wantedChar, char delimiter) {
    char test;
	int initialCursor;
	int size;

	size = fileSize(sourceFile)
	initialCursor = ftell(sourceFile);

	while(ftell(sourceFile) < size) {   // Tant que l'on n'est pas � la fin du fichier.
        test = fgetc(fileSource);

		/* V�rification de la cha�ne lue */
		if(test == wantedChar) {
			return 1;   // Si identique
		} else if(test == delimiter) {
		    return 0;   // Si delimiteur atteint
		} else {
            fseek(sourceFile, prevCursor, SEEK_SET);    // Si non, on retourne o� l'on �tait.
            fseek(sourceFile, 1, SEEK_CUR);             // On avance d'un cran dans le fichier et on recommence.
		}
	}
	fseek(sourceFile, initialCursor, SEEK_SET);         // Retour � la position initiale
	return -1;
}


void getValue(FILE* fileSource, char* wantedElement, char* destination) {
    if ( fSearchStr(fileSource, wantedElement) ) {      // Cherche l'�l�ment voulu
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
