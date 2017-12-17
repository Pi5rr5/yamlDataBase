#ifndef GLOBALS_H_INCLUDED
    #define GLOBALS_H_INCLUDED

    // storage current database
    extern char *CURRENT_DATABASE;
    char *CURRENT_DATABASE;
	/**
	 * @name FILE_LINE_COUNTER
	 *
	 * @brief global counting le current line number on which is the file cursor. Updated by few functions.
	 *
	 * @remarks `extern` is exclusive to globals variables.
	 *			It allows to specify to the compiler that the variable may have been already declared in another file.
	 *			And if it has been, then it will be not redeclared
	 *
	 * @see getEntity() getBlockWhere() getAllFrom() freadLine()
	 */
	int FILE_LINE_COUNTER;
#endif // GLOBALS_H_INCLUDED
