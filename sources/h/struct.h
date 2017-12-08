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
     * @struct lineStruct
     * @typedef lineStruct
     *
     * @brief Structure of a YAML data line.
     *
     * @param char key[MAX] : data key (i.e name of the column)
     * @param char value[MAX] : data value
     */
     typedef struct lineStruct {
        char key[MAX];
        char value[MAX];
     } lineStruct;

    /**
     * @struct listOfLines
     * @typedef listOfLines
     *
     * @brief Linked list of `linesStruct`. Corresponds to the entirety of an entity.
     *
     * @param struct line element : data line.
     * @param struct listOfLines* next : next element of the linked list.
     */
    typedef struct listOfLines {
        struct lineStruct line;
        struct listOfLines *next;
    } listOfLines;

    /**
     * @struct listOfEntities
     * @typedef listOfEntities
     *
     * @brief Linked list of data blocks. This is the type that is return after any selection.
     *
     * @param struct ll_line block* block : linked list of data lines (also called "data block" or "entity")
     * @param struct ll_dataBlock* *next : next element of the linked list.
     */
    typedef struct listOfEntities {
        struct listOfLines* entity;
        struct listOfEntities* next;
    } listOfEntities;

    /**
     * @struct stringList
     * @typedef stringList
     *
     * @brief Linked list of string. Use for a lot of creation and few searches.
     * 			Instead of a dynamic array of string which is use for a lot of searching and few creation.
     *
     * @param char[MAX] str : string element.
     * @param struct stringList* next : next element of the linked list
     */
     typedef struct stringList {
		char str[MAX];
		struct stringList* next;
     } stringList;

#endif // STRUCT_H_INCLUDED
