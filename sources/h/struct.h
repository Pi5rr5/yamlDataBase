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

    typedef struct tableEntity {
        char line[MAX];
        struct tableEntity *next;
    } tableEntity;
#endif // STRUCT_H_INCLUDED
