#ifndef MAX
    #define MAX 255
#endif // MAX

#ifndef STRUCT_H_INCLUDED
    #define STRUCT_H_INCLUDED

    typedef struct struct_db {
        char *database;
    } db_infos;

    typedef struct struct_command {
        char *name;

        void (*f)(char *);
    } command_options;

    extern command_options cmdRequest[];

    /**
     * @brief Structure d'une ligne de donn�e.
     * @param char key[MAX] : cha�ne de caract�res correspondant � la clef de la donn�e (ou nom de la colonne)
     * @param char value[MAX] : cha�ne de caract�res correspondant � la valeur de la donn�e.
     */
     typedef struct lineStruct {
        char key[MAX];
        char value[MAX];
     } lineStruct;

    /**
     * @brief Liste cha�n�e de lignes. Correspond � l'ensemble des donn�es pour une entit�.
     *
     * @param struct line element : ligne de donn�e.
     * @param struct listOfLines* next : pointeur vers l'�l�ment de la liste suivant.
     */
    typedef struct listOfLines {
        struct lineStruct line;
        struct listOfLines *next;
    } listOfLines;

    /**
     * @brief Liste cha�n�e de blocs de donn�es. C'est ce type de liste qui est renvoy� apr�s une selection.
     *
     * @param struct ll_line block* block : liste cha�n�e de lignes de donn�es (ou "Bloc de donn�es").
     * @param struct ll_dataBlock* *next : �l�ment suivant de la liste cha�n�e.
     */
    typedef struct listOfEntities {
        struct listOfLines* entity;
        struct listOfEntities* next;
    } listOfEntities;
#endif // STRUCT_H_INCLUDED
