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
     * @brief Structure d'une ligne de donnée.
     * @param char key[MAX] : chaîne de caractères correspondant à la clef de la donnée (ou nom de la colonne)
     * @param char value[MAX] : chaîne de caractères correspondant à la valeur de la donnée.
     */
     typedef struct lineStruct {
        char key[MAX];
        char value[MAX];
     } lineStruct;

    /**
     * @brief Liste chaînée de lignes. Correspond à l'ensemble des données pour une entité.
     *
     * @param struct line element : ligne de donnée.
     * @param struct listOfLines* next : pointeur vers l'élément de la liste suivant.
     */
    typedef struct listOfLines {
        struct lineStruct line;
        struct listOfLines *next;
    } listOfLines;

    /**
     * @brief Liste chaînée de blocs de données. C'est ce type de liste qui est renvoyé après une selection.
     *
     * @param struct ll_line block* block : liste chaînée de lignes de données (ou "Bloc de données").
     * @param struct ll_dataBlock* *next : élément suivant de la liste chaînée.
     */
    typedef struct listOfEntities {
        struct listOfLines* entity;
        struct listOfEntities* next;
    } listOfEntities;
#endif // STRUCT_H_INCLUDED
