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
     * Description : Liste chaînée de lignes. Correspond à l'ensemble des données pour une entité.
     * Attributs :
     *      char line[MAX] : ligne de donnée.
     *      struct ll_line* next : pointeur vers l'élément de la liste suivant.
     */
    typedef struct ll_line {
        char line[MAX];
        struct ll_line *next;
    } ll_line;

    /**
     * Description : Liste chaînée de blocs de données. C'est ce type de liste qui est renvoyé après une selection.
     * Attributs :
     *      struct ll_line block* block : liste chaînée de lignes de données (ou "Bloc de données").
     *      struct ll_dataBlock* *next : élément suivant de la liste chaînée.
     *
     *
     */
    typedef struct ll_dataBlock {
        struct ll_line* block;
        struct ll_dataBlock *next;
    } ll_dataBlock;
#endif // STRUCT_H_INCLUDED
