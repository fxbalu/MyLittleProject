/**
 * \file log.h
 * \brief Logging related functions
 *
 * \author François-Xavier Balu \<fx.balu@gmail.com\>
 * \date 08/04/14
 */


#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED


/**
 * \name Logging options
 * Define how the logging is handled, if it should be done in a terminal,
 * in a text file, if colors are used, if full file path is saved, etc.
 * Comment to disable them.
 */
/**@{*/

/** Memory related message will be displayed on the standard output (terminal) */
//#define LOG_MEM_IN_STDOUT

/** Memory related message will be saved in a text file */
//#define LOG_MEM_IN_LOG_FILE

/** Error related message will be displayed on the error output (terminal) */
//#define LOG_ERR_IN_STDERR

/** Error related message will be displayed on the standard output (terminal) */
//#define LOG_ERR_IN_STDOUT

/** Error related message will be saved in a error specific text file */
//#define LOG_ERR_IN_ERR_FILE

/** Error related message will be saved in a text file */
//#define LOG_ERR_IN_LOG_FILE

/** full file path will be used.
 * If defined, file path will be like this: /home/foo/src/bar.c
 * If commented, file path will be like this: bar.c
 */
//#define LOG_FILE_PATH

/** Path of the standard logging file */
//#define LOG_STD_FILE_PATH  "stdlog.txt"

/** Path of the error logging file */
//#define LOG_ERR_FILE_PATH  "errlog.txt"

/** Use colors in the standard output and error output */
#define LOG_WITH_COLORS

/**@}*/ /* Logging options */


/**
 * \name logMem() constants
 * Define direction of the memory logging. Use them in place of the direction
 * parameter of logMem().
 */
/**@{*/

/** Use this direction to log an allocation (after a malloc, calloc and realloc) */
#define LOG_ALLOC   '+'
/** Use this direction to log a freeing of memory (before a free and realloc) */
#define LOG_FREE    '-'

/**@}*/


/**
 * \name Verbose level of checkLoggedMemory().
 */
/**@}*/

#define LOG_TYPE         0x01 /**< Display the types summary */
#define LOG_USED         0x02 /**< Display variables actually used (not freed) */
#define LOG_FREED        0x04 /**< Display freed variables */
#define LOG_FILE_INFO    0x08 /**< Display variables' origin (file and line) */
#define LOG_DESCRIPTION  0x10 /**< Display variables' description */
#define LOG_ADDRESS      0x20 /**< Display variables' addresses */
#define LOG_EVERYTHING   0xFF /**< Every options above */

/**@}*/


/**
 * \name Tables Size
 * Define various sizes of some tables used in log.h and log.c. Try to increase
 * them if functions throw errors and glitches.
 */
/**@{*/

/** Number of entry in the global variable table */
#define LOG_VARIABLE_NB  10000

/** Number of types that can be logged */
#define LOG_TYPE_NB  20

/** Length of a type string */
#define LOG_TYPE_LENGTH         15

/** Length of a description string */
#define LOG_DESCRIPTION_LENGTH  30

/**
 * \def LOG_FILE_LENGTH
 * Length of a file path string, with a long (full path) and short (file's name
 * only) version.
 */
#ifdef LOG_FILE_PATH
   #define LOG_FILE_LENGTH      70
#else
   #define LOG_FILE_LENGTH      15
#endif /* LOG_FILE_PATH */

/**@}*/


/**
 * \name Colors for standard output
 * Colors for terminal logging
      String: "\e[{attr};{fg};{bg}m"

      Attributes:
         0 Reset All Attributes (return to normal mode)
         1 Bright (usually turns on BOLD)
         2 Dim
         3 Underline
         5 Blink
         7 Reverse
         8 Hidden

      Foreground:
         30 Black
         31 Red
         32 Green
         33 Yellow
         34 Blue
         35 Magenta
         36 Cyan
         37 White

      Background:
         40 Black
         41 Red
         42 Green
         43 Yellow
         44 Blue
         45 Magenta
         46 Cyan
         47 White
    */

/**@{*/


#ifdef LOG_WITH_COLORS
   #define LOG_RED      "\e[1;31m"  /**< Bold red */
   #define LOG_GREEN    "\e[1;32m"  /**< Bold Green */
   #define LOG_YELLOW   "\e[1;33m"  /**< Bold Yellow */
   #define LOG_BLUE     "\e[1;34m"  /**< Bold Blue */
   #define LOG_MAGENTA  "\e[1;35m"  /**< Bold Magenta */
   #define LOG_CYAN     "\e[1;36m"  /**< Bold Cyan */
   #define LOG_WHITE    "\e[1;37m"  /**< Bold White */
   #define LOG_NORMAL   "\e[0m"     /**< Reset colors and attributes */
#else
   #define LOG_RED      ""
   #define LOG_GREEN    ""
   #define LOG_YELLOW   ""
   #define LOG_BLUE     ""
   #define LOG_MAGENTA  ""
   #define LOG_CYAN     ""
   #define LOG_WHITE    ""
   #define LOG_NORMAL   ""
#endif /* LOG_WITH_COLORS */

/**@}*/


/** Computes the maximum of \a a and \a b */
#define max(a,b) (a<b)?b:a


/**
 * \struct Log_Variable
 * Informations about a logged variable are stored there. */
typedef struct Log_Variable {
   void* ptr;  /**< address where this variable is stored */
   int type;   /**< index for a Log_Memory.type[] string */
   char description[LOG_DESCRIPTION_LENGTH]; /**< a brief description */
   char file[LOG_FILE_LENGTH];   /**< file where the variable was allocated */
   int line;   /**< line where the file was allocated */
   int alloc;  /**< 1 if this var is used, 0 if it was freed */
} Log_Variable;


/**
 * Informations about every logged variables are stored there.
 */
typedef struct Log_Memory {
   Log_Variable var[LOG_VARIABLE_NB];  /**< Every logged variables */
   char type[LOG_TYPE_NB][LOG_TYPE_LENGTH];  /**< Every logged variables' types */
   int typeByVar[LOG_TYPE_NB];   /**< number of variables logged by types */
   int varNb;  /**< Number of variables logged */
   int typeNb; /**< Number of types logged */

} Log_Memory;


void logError(const char* str, const char* file, const int line);
void logMem(const char direction, const void* ptr, const char* type,
            const char* desc, char* file, const int line);
void checkAllocatedMemory(const char verbosity);

void drawBar(char line, int count);
void drawProgressBar(char firstBorder, char lastBorder, char on, char off, int percentage, int width);

void printBar(char border, char line, int count);
void printBarText(char border, char line, int count, char* text, char* color);
void printProgressBar(int percentage, int width);

#endif /* LOG_H_INCLUDED */
