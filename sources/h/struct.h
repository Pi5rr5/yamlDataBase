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
     * Description : Liste cha�n�e de lignes. Correspond � l'ensemble des donn�es pour une entit�.
     * Attributs :
     *      char line[MAX] : ligne de donn�e.
     *      struct ll_line* next : pointeur vers l'�l�ment de la liste suivant.
     */
    typedef struct ll_line {
        char line[MAX];
        struct ll_line *next;
    } ll_line;

    /**
     * Description : Liste cha�n�e de blocs de donn�es. C'est ce type de liste qui est renvoy� apr�s une selection.
     * Attributs :
     *      struct ll_line block* block : liste cha�n�e de lignes de donn�es (ou "Bloc de donn�es").
     *      struct ll_dataBlock* *next : �l�ment suivant de la liste cha�n�e.
     *
     *
     */
    typedef struct ll_dataBlock {
        struct ll_line* block;
        struct ll_dataBlock *next;
    } ll_dataBlock;
#endif // STRUCT_H_INCLUDED
