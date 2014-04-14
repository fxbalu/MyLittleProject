/**
 * \file log.c
 * \brief Logging related functions
 *
 * \author François-Xavier Balu \<fx.balu@gmail.com\>
 * \date 08/04/14
 * \todo extend logMem() with a description.
 * \todo remove useless part given by the _FILE__ macro.
 */


#include <stdio.h>   /* FILE, fopen(), fprintf(), printf() */
#include <stdlib.h>
#include <string.h>  /* strrchr(), strcmp(), strcpy() */
#include "log.h"

static Log_Memory mem;

/**
 * \brief Log error in standard error output
 * Show an error message in standard error output with file name and line number.
 * It need to be called as shown below :
 * \code
 * logError("Useful message.", __FILE__, __LINE__);
 * \endcode
 * The output message should be like this :
 * \verbatim
 * ! error in [/home/user/git/mlp/src/my_file.c] at line [42] :
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
   #ifndef LOG_FILE_PATH
      char* lastSlash;
   #endif /* LOG_FILE_PATH */
   #ifdef LOG_IN_ERR_FILE
      static FILE* errorFile = NULL;
   #endif /* LOG_IN_ERR_FILE */

   #ifdef LOG_ON_STDERR
      #ifdef LOG_FILE_PATH
         fprintf(stderr, LOG_RED "[ERR] error in " LOG_YELLOW "%s ", file);
      #else
         if((lastSlash = strrchr(file, '/')) == NULL){
            fprintf(stderr, LOG_RED "[ERR] error in " LOG_YELLOW "%s ", file);
         }
         else{
            fprintf(stderr, LOG_RED "[ERR] error in " LOG_YELLOW "%s ", lastSlash+1);
         }
      #endif /* LOG_FILE_PATH */
      fprintf(stderr, LOG_RED "at line " LOG_BLUE "%d ", line);
      fprintf(stderr, LOG_RED ":\n%s\n" LOG_NORMAL, str);
   #endif /* LOG_ON_STDERR */

   #ifdef LOG_IN_ERR_FILE
      /* file logging code */
      if(errorFile == NULL){
         errorFile = fopen(LOG_ERR_FILE_PATH, "w");
      }
      #ifdef LOG_FILE_PATH
         fprintf(errorFile, "[ERR] error in %s ", file);
      #else
         if((lastSlash = strrchr(file, '/')) == NULL){
            fprintf(errorFile, "[ERR] error in %s ", file);
         }
         else{
            fprintf(errorFile, "[ERR] error in %s ", lastSlash+1);
         }
      #endif /* LOG_FILE_PATH */
      fprintf(errorFile, "at line %d : %s\n\r", line, str);
   #endif /* LOG_IN_ERR_FILE */
}


/**
 * \brief Log dynamically allocated memory to look for memory leaks.
 */
void logMem(const char direction, const void* ptr, const char* type,
            const char* desc, const char* file, const int line){
   int iVar, iType;
   Log_Variable* var;

   #ifndef LOG_FILE_PATH
   char* lastSlash;
   lastSlash = NULL;
   #endif /* LOG_FILE_PATH */

   var = NULL;


   /* add newly allocated variable to global structure mem */
   if(direction == LOG_ALLOC){

      /* check if variable table is full */
      if(mem.varNb >= LOG_VARIABLE_NB){
         logError("Variable table is full. Change LOG_VARIABLE_NB constant in log.h.",
                  __FILE__, __LINE__);
      }

      /* copy variable in table */
      else{
         var = &(mem.var[mem.varNb]);

         /* check if this type has been used before */
         iType = 0;
         while((iType < mem.typeNb) && (strcmp(type, mem.type[iType]) != 0)){
            iType++;
         }

         /* detected new type, add it in type table */
         if(iType == mem.typeNb){
            if(mem.typeNb >= LOG_TYPE_NB){
               logError("Type table is full. Change LOG_TYPE_NB constant in log.h",
                        __FILE__, __LINE__);
            }
            else{
               strcpy(mem.type[iType], type);
               mem.typeByVar[iType] = 0;
               mem.typeNb++;
            }
         }

         /* copy type */
         var->type = iType;

         /* copy file's name */
         #ifdef LOG_FILE_PATH
            strcpy(var->file, file);
         #else
            if((lastSlash = strrchr(file, '/')) == NULL){
               strcpy(var->file, file);
            }
            else{
               strcpy(var->file, lastSlash + 1);
            }
         #endif /* LOG_FILE_PATH */

         /* copy variable's address */
         var->ptr = (void*)ptr;

         /* copy description */
         strcpy(var->description, desc);

         /* copy line's value */
         var->line = line;

         /* set state */
         var->alloc = 1;

         mem.typeByVar[iType]++;
         mem.varNb++;
      }
   }

   /* delete freed variable from the variable table */
   else if(direction == LOG_FREE){

      /* check if variable table is empty */
      if(mem.varNb <= 0){
         logError("mem table is empty.", __FILE__, __LINE__);
      }

      /* search variable in variable table */
      else{

         /* find type in type table */
         iVar = 0;
         while((iVar < mem.varNb) && (mem.var[iVar].ptr != ptr)){
            iVar++;
         }
         if(iVar == mem.varNb){
            logError("Didn't find variable in variable table.", __FILE__, __LINE__);
         }
         else{
            var = &(mem.var[iVar]);

            /* set state */
            var->alloc = 0;

            /* decrement type */
            iType = 0;
            while((iType < mem.typeNb) && (strcmp(mem.type[iType], type) != 0)){
               iType++;
            }
            if(iType == mem.typeNb){
               logError("Didn't find type in variable type.", __FILE__, __LINE__);
            }
            else if(mem.typeByVar[iType] <= 0){
               logError("Type count is already zero", __FILE__, __LINE__);
            }
            else{
               mem.typeByVar[iType]--;
            }
         }
      }
   }

   /* Direction is not LOG_ALLOC or LOG_FREE */
   else{
      logError("Use LOG_ALLOC or LOG_FREE as direction.", __FILE__, __LINE__);
   }

   /* display log messages in a terminal */
   #ifdef LOG_ON_STDOUT
      if(direction == LOG_ALLOC){
         printf(LOG_MAGENTA "[MEM] " LOG_GREEN "+ ");
      }
      else{
         printf(LOG_MAGENTA "[MEM] " LOG_RED "- ");
      }
      printf(LOG_CYAN "%s " LOG_WHITE "%s " LOG_NORMAL, type, desc);
      printf("in " LOG_YELLOW "%s " LOG_NORMAL, mem.var[mem.typeNb-1].file);
      printf("at line " LOG_BLUE "%d " LOG_NORMAL, line);
      printf("[adress: %p]\n", ptr);
   #endif /* LOG_ON_STDOUT */

   /* save log messages in a text file */
   #ifdef LOG_IN_STD_FILE
      /* file logging code */
   #endif /* LOG_IN_STD_FILE */
}


/**
 * \brief Check all logged allocated memory.
 * \param[in] verbosity  How talkative logMem() is.
 *                       LOG_TYPE display the types
 *                       LOG_USED display non freed variables
 *                       LOG_FREED display freed variables
 *                       LOG_FILE_INFO display file's path and line
 *                       LOG_DESCRIPTION display variable's description
 *                       LOG_ADDRESS display variable's address
 *                       LOG_EVERYTHING display all the above
 */
void checkAllocatedMemory(const char verbosity){
   int i, iType, iVar, width, temp;
   Log_Variable* var;

   /* calculate window width */

   /* width for title */
   width = 10;

   /* width for type part */
   if(verbosity & LOG_TYPE){
      temp = 5 + LOG_TYPE_LENGTH;
      width = max(width, 5);
      width = max(width, temp);
   }

   /* width for variable part */
   if(verbosity & (LOG_FREED | LOG_USED)){

      /* state and type */
      temp = 1 + 4 + 1 + LOG_TYPE_LENGTH;

      /* description */
      if(verbosity & LOG_DESCRIPTION){
         temp += 1 + LOG_DESCRIPTION_LENGTH;
      }

      /* file and line */
      if(verbosity & LOG_FILE_INFO){
         temp += 1 + LOG_FILE_LENGTH + 1 + 4;
      }

      /* address */
      if(verbosity & LOG_ADDRESS){
         temp += 1 + 16;
      }

      width = max(width, temp);
   }
   width += 2;

   /* display window upper bar _______ */
   printf("\n ");
   for(i=0; i<width; i++) putchar('_');
   printf("\n|");

   /* display window title */
   for(i=0; i<((width-10)/2); i++) putchar(' ');
   printf(LOG_MAGENTA "MEMORY MAP" LOG_NORMAL);
   for(i=0; i<(width-10-(width-10)/2); i++) putchar(' ');
   printf("|\n");

   /* display used types */
   if(verbosity & LOG_TYPE){

      /* display separation bar |------| */
      putchar('|');
      for(i=0; i<width; i++) putchar('-');
      printf("|\n|");

      /* display section title */
      for(i=0; i<((width-5)/2); i++) putchar(' ');
      printf(LOG_GREEN "Types" LOG_NORMAL);
      for(i=0; i<(width-5-(width-5)/2); i++) putchar(' ');
      printf("|\n");

      /* display separation bar |      | */
      putchar('|');
      for(i=0; i<width; i++) putchar(' ');
      printf("|\n");

      /* display type title and count */
      for(iType=0; iType<mem.typeNb; iType++){
         printf("| ");
         if(mem.typeByVar[iType] == 0){
            printf(LOG_GREEN "%4d" LOG_NORMAL " %-*s",
                   mem.typeByVar[iType], LOG_TYPE_LENGTH, mem.type[iType]);
         }
         else{
            printf(LOG_RED "%4d" LOG_NORMAL " %-*s",
                   mem.typeByVar[iType], LOG_TYPE_LENGTH, mem.type[iType]);
         }
         for(i=0; i<width-(1+4+1+LOG_TYPE_LENGTH); i++){
            putchar(' ');
         }
         printf("|\n");
      }
   }

   /* display every logged variables */
   if(verbosity & (LOG_USED | LOG_FREED)){

      /* display separation bar |------| */
      putchar('|');
      for(i=0; i<width; i++) putchar('-');
      printf("|\n|");

      /* display section title */
      for(i=0; i<((width-9)/2); i++) putchar(' ');
      printf(LOG_CYAN "Variables" LOG_NORMAL);
      for(i=0; i<(width-9-(width-9)/2); i++) putchar(' ');
      printf("|\n");

      /* display separation bar |     | */
      putchar('|');
      for(i=0; i<width; i++) putchar(' ');
      printf("|\n");

      /* display variables */
      for(iVar=0; iVar<mem.varNb; iVar++){
         var = &(mem.var[iVar]);

         if( ((verbosity & LOG_USED) && (var->alloc == 1)) ||
             ((verbosity & LOG_FREED) && (var->alloc == 0)) ){

            /* start line */
            putchar('|');

            /* display variable state (free or used) and type */
            if((verbosity & LOG_USED) && (var->alloc == 1)){
               printf(" " LOG_RED "used" LOG_NORMAL "  %-*s",
                      LOG_TYPE_LENGTH, mem.type[var->type]);
            }
            else if((verbosity & LOG_FREED) && (var->alloc == 0)){
               printf(" " LOG_GREEN "free" LOG_NORMAL "  %-*s",
                      LOG_TYPE_LENGTH, mem.type[var->type]);
            }

            /* display variable's description */
            if(verbosity & LOG_DESCRIPTION){
               printf(LOG_WHITE " %-*s" LOG_NORMAL, LOG_DESCRIPTION_LENGTH, var->description);
            }

            /* display variable's file infos */
            if(verbosity & LOG_FILE_INFO){
               printf(LOG_YELLOW " %*s" LOG_BLUE ":%-4d" LOG_NORMAL,
                      LOG_FILE_LENGTH, var->file, var->line);
            }

            /* display variable's address */
            if(verbosity & LOG_ADDRESS){
               printf(" [%p]", var->ptr);
            }

            /* end of line */
            printf(" |\n");
         }
      }
   }

   /* end of display */
   putchar('|');
   for(i=0; i<width; i++) putchar('_');
   printf("|\n");
}
