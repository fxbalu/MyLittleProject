/**
 * \file log.h
 * \brief Logging related functions
 *
 * \author François-Xavier Balu \<fx.balu@gmail.com\>
 * \date 08/04/14
 */


#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED


/* Logging options. Comment to disable.  */
#define LOG_ON_STDOUT
#define LOG_ON_STDERR
#define LOG_IN_STD_FILE
#define LOG_IN_ERR_FILE
//#define LOG_FILE_PATH

/* Log files path */
#define LOG_STD_FILE_PATH  "stdlog.txt"
#define LOG_ERR_FILE_PATH  "errlog.txt"

/* Direction for logMem(). Basically IN or OUT */
#define LOG_ALLOC   '+'
#define LOG_FREE    '-'
#define LOG_REALLOC '='

/* Number of entry in the global Log_Variable table t */
#define LOG_VARIABLE_NB  4000

/* Number of type who can be logged at the same time */
#define LOG_TYPE_NB  20

/* String length */
#define LOG_TYPE_LENGTH         20
#define LOG_DESCRIPTION_LENGTH  40
#define LOG_FILE_LENGTH         100

/* Verbose level of logMem() */
#define LOG_TYPE         0x01
#define LOG_USED         0x02
#define LOG_FREED        0x04
#define LOG_FILE_INFO    0x08
#define LOG_DESCRIPTION  0x10
#define LOG_EVERYTHING   0xFF

/** Colors for terminal logging
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
//#define LOG_WITH_COLORS
#ifdef LOG_WITH_COLORS
   #define LOG_RED      "\e[1;31m"
   #define LOG_GREEN    "\e[1;32m"
   #define LOG_YELLOW   "\e[1;33m"
   #define LOG_BLUE     "\e[1;34m"
   #define LOG_MAGENTA  "\e[1;35m"
   #define LOG_CYAN     "\e[1;36m"
   #define LOG_WHITE    "\e[1;37m"
   #define LOG_NORMAL   "\e[0m"
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

/* Structures for dynamic memory allocation logging */
typedef struct Log_Variable {
   int type;
   char description[LOG_DESCRIPTION_LENGTH];
   char file[LOG_FILE_LENGTH];
   int line;
   int alloc; /**< 1 if this var is used, 0 if it was freed */
} Log_Variable;


typedef struct Log_Memory {
   Log_Variable var[LOG_VARIABLE_NB];
   char type[LOG_TYPE_NB][LOG_TYPE_LENGTH];
   int typeByVar[LOG_TYPE_NB];
   int varNb;
   int typeNb;
} Log_Memory;


void logError(const char* str, const char* file, const int line);
void logMem(const char direction, const char* type, const char* file, const int line);
void checkAllocatedMemory(const char verbosity);

#endif /* LOG_H_INCLUDED */
