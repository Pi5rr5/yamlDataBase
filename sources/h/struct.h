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

    /* ----- END OF "BY ENTITY" YAML SELECTION ----- */



	/* 		----- "BY KEY" YAML SELECTION -----
		The following structures are used for YAML
		selection by key, i.e all selection queries
		except `SELECT *`. 							*/

	/**
     * @struct stringList
     *
     * @typedef stringList
     * @typedef listOfValues
     * @typedef listOfString
     *
     * @brief Linked list of string. Used for a lot of creation and few searches.
     * 			Instead of a dynamic array of string which is used for a lot of searching and few creation.
     *
     * @var char[MAX] str : string element.
     * @var struct stringList* next : next element of the linked list
     */
	typedef struct stringList {
		char value[MAX];
		struct stringList* next;
	} stringList, listOfValues, listOfString;

	/**
	 * @struct listOfKeys
	 * @typedef listOfKey
	 *
	 * @brief linked list of keys, each element contains a list of all the value found for the key.
	 *
	 * @var char key[MAX] : name of the key.
	 * @var struct listOfValues* values : linked list of the values corresponding to that key.
	 * @var struct listOfKeys* next : pointer to the next element of that key.
	 *
	 * @remarks Used as variable for `queryResult` only.
	 */
	typedef struct listOfKeys {
		char key[MAX];
		struct listOfValues* values;
		struct listOfKeys* next;
	} listOfKeys;

	/**
	 * @struct selectResult
	 * @typedef selectResult
	 *
	 * @brief linked list returned by any SQL selection that need a result "by keys"
	 *
	 * @var listOfKeys* keys : list of the keys selected
	 * @var struct queryResult* next : pointer to the next element of the list.
	 */
	typedef struct queryResult {
		listOfKeys* keys;
		struct quesryResult* next;
	} queryResult;

	/* ----- END OF "BY KEY" YAML SELECTION ----- */

#endif // STRUCT_H_INCLUDED
