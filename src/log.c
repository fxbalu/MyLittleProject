/**
 * \file log.c
 * \brief Logging related functions
 *
 * \author François-Xavier Balu \<fx.balu@gmail.com\>
 * \date 08/04/14
 * \todo extend logMem() with a description.
 * \todo remove useless part given by the _FILE__ macro.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"


MemAlloc t[LOG_ENTRY_NB];
int allocCount = 0;


/**
 * \brief Log error in standard error output
 * Show an error message in standard error output with file name and line number.
 * It need to be called as shown below :
 * \code
 * logError("Useful message.", __FILE__, __LINE__);
 * \endcode
 * The output message should be :
 * \verbatim
 * ! error in [/src/my_file.c] at line [42] :
 * ! Useful message.
 * \endverbatim
 *
 * \param[in] str   Additional informations displayed in log's second line.
 * \param[in] file  File path displayed in log's first line.
 * \param[in] line  Line number displayed in log's first line.
 *
 * \todo Improve logError with variable argument number as seen with printf().
 * Prototype will be : \code
 * void logError(const char* str, const char* file, const char* line, ...);
 * \endcode
 */
void logError(const char* str, const char* file, const int line){
   #ifdef LOG_ON_STDERR
   fprintf(stderr, "! error in [%s] at line [%d] :\n! %s\n", file, line, str);
   #endif
   #ifdef LOG_IN_ERR_FILE
   /* file logging code */
   #endif
}


void logMem(const char direction, const char* type, const char* file, const int line){
   if(direction == LOG_ALLOC){
      if(allocCount >= LOG_ENTRY_NB){
         logError("logMem table is full. Check LOG_ENTRY_NB constant in log.h.",
                  __FILE__, __LINE__);
      }
      else{
         strcpy(t[allocCount].type, type);
         allocCount++;
      }
   }
   else if(direction == LOG_FREE){
      if(allocCount <= 0){
         logError("logMem table is empty.", __FILE__, __LINE__);
      }
      else{
         allocCount--;
      }
   }
   else{
      logError("Bad use of logMem().", __FILE__, __LINE__);
   }

   #ifdef LOG_ON_STDOUT
   printf("MEM %c %s in %s at line %d\n", direction, type, file, line);
   #endif /* LOG_ON_STDOUT */
   #ifdef LLOG_IN_STD_FILE
   /* file logging code */
   #endif /* LOG_IN_STD_FILE */
}

/**
 * \brief Check all logged allocated memory.
 */
void checkMemAlloc(void){
   int i;

   printf("\n _________________________\n");
   printf("|       Memory Map        |\n");
   printf("|-------------------------|\n");
   for(i=0; i<allocCount; i++){
      printf("|%3d %-20s |\n", i, t[i].type);
   }
   printf("|_________________________|\n");
}
