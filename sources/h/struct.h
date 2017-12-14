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
    } command_options, fctPtr;

    extern command_options cmdRequest[];

	typedef struct arrayOfStrings {
		char** array;
		unsigned int stringsNb;
	} arrayOfStrings;


    /* 		----- "BY ENTITY" YAML SELECTION -----
		The following structures are used for YAML
		selection by entity, i.e `SELECT *` queries    */

    /**
     * @struct lineStruct
     * @typedef lineStruct
     *
     * @brief Structure of a YAML data line.
     *
     * @var char key[MAX] : data key (i.e name of the column)
     * @var char value[MAX] : data value
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
     * @var struct line element : data line.
     * @var struct listOfLines* next : next element of the linked list.
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


#endif // STRUCT_H_INCLUDED
