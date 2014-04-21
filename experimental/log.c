/**
 * \file log.c
 * \brief Logging related functions
 *
 * \author François-Xavier Balu \<fx.balu@gmail.com\>
 * \date 08/04/14
 * \todo extend logMem() with a description.
 * \todo remove useless part given by the _FILE__ macro.
 */


#include <stdio.h>      /* FILE, fopen(), fprintf(), printf() */
#include <stdlib.h>
#include <string.h>     /* strrchr(), strcmp(), strcpy(), strlen() */
#include <inttypes.h>   /* PRIxPTR */
#include <stdint.h>     /* uintptr_t */
#include "log.h"


static Log_Memory mem;


/**
 * \brief Log error in standard error output
 * Show an error message in standard error output with file name and line number.
 * It need to be called as shown below :
 * \code
 * logError("Useful message.",  __FILE__ ,  __LINE__ );
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
 *       Prototype will be : \code
 *       void logError(const char* str, const char* file, const char* line, ...);
 * \endcode
 * \todo replace every similar (f)printf(same_stuff) by (f)printf(line)
 *       with line a string where log will be written only once.
 */
void logError(const char* str, const char* file, const int line){
   #ifdef LOG_ERR_IN_ERR_FILE
      static FILE* errFile = NULL;
   #endif /* LOG_ERR_IN_ERR_FILE */

   #ifdef LOG_ERR_IN_LOG_FILE
      static FILE* logFile = NULL;
   #endif /* LOG_ERR_IN_LOG_FILE */

   #ifndef LOG_FILE_PATH
      char* lastSlash;

      if((lastSlash = strrchr(file, '/')) != NULL){
         file = lastSlash + 1;
      }
   #endif /* LOG_FILE_PATH */

   #ifdef LOG_ERR_IN_STDERR
      fprintf(stderr, LOG_RED "[ERR] error in " LOG_YELLOW "%s ", file);
      fprintf(stderr, LOG_RED "at line " LOG_BLUE "%d ", line);
      fprintf(stderr, LOG_RED ":\n%s\n" LOG_NORMAL, str);
   #endif /* LOG_ERR_IN_STDERR */

   #ifdef LOG_ERR_IN_STDOUT
      fprintf(stdout, LOG_RED "[ERR] error in " LOG_YELLOW "%s ", file);
      fprintf(stdout, LOG_RED "at line " LOG_BLUE "%d ", line);
      fprintf(stdout, LOG_RED ":\n%s\n" LOG_NORMAL, str);
   #endif /* LOG_ERR_IN_STDOUT */

   #ifdef LOG_ERR_IN_ERR_FILE
      /* file logging code */
      if(errFile == NULL){
         errFile = fopen(LOG_ERR_FILE_PATH, "w");
      }
      fprintf(errFile, "[ERR] error in %s ", file);
      fprintf(errFile, "at line %d : %s\n\r", line, str);
   #endif /* LOG_ERR_IN_ERR_FILE */

   #ifdef LOG_ERR_IN_LOG_FILE
      /* file logging code */
      if(logFile == NULL){
         logFile = fopen(LOG_ERR_FILE_PATH, "w");
      }
      fprintf(logFile, "[ERR] error in %s ", file);
      fprintf(logFile, "at line %d : %s\n\r", line, str);
   #endif /* LOG_ERR_IN_LOG_FILE */
}


/**
 * \brief Log dynamically allocated memory to look for memory leaks.
 *
 * \param[in] direction  LOG_ALLOC if memory is allocated, LOG_FREE if memory is freed.
 * \param[in] ptr        Logged variable's address.
 * \param[in] type       String of the variable's type, eg: "int", "string".
 * \param[in] desc       A brief description of this variable.
 * \param[in] file       File where this variable was allocated, use the macro __FILE__.
 * \param[in] line       Line where this variable was allocated, use the macro __LINE__.
 */
void logMem(const char direction, const void* ptr, const char* type,
            const char* desc, char* file, const int line){
   int iVar, iType;
   Log_Variable* var;

   #ifndef LOG_FILE_PATH
   char* lastSlash;

   if((lastSlash = strrchr(file, '/')) != NULL){
      file = lastSlash + 1;
   }
   #endif /* LOG_FILE_PATH */

   /* add newly allocated variable to global structure mem */
   if(direction == LOG_ALLOC){

      /* check if variable table is full */
      if(mem.varNb >= LOG_VARIABLE_NB){
         logError("Variable table is full. Change LOG_VARIABLE_NB constant in log.h.",
                   __FILE__ ,  __LINE__ );
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
                         __FILE__ ,  __LINE__ );
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
         strcpy(var->file, file);

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
         logError("mem table is empty.",  __FILE__ ,  __LINE__ );
      }

      /* search variable in variable table */
      else{

         iVar = 0;
         while((iVar < mem.varNb) &&
               ((mem.var[iVar].ptr != ptr) || (mem.var[iVar].alloc == 0)) ){
            iVar++;
         }
         if(iVar == mem.varNb){
            logError("Didn't find variable in variable table.",  __FILE__ ,  __LINE__ );
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
               logError("Didn't find type in variable type.",  __FILE__ ,  __LINE__ );
            }
            else if(mem.typeByVar[iType] <= 0){
               logError("Type count is already zero",  __FILE__ ,  __LINE__ );
            }
            else{
               mem.typeByVar[iType]--;
            }
         }
      }
   }

   /* Direction is not LOG_ALLOC or LOG_FREE */
   else{
      logError("Use LOG_ALLOC or LOG_FREE as direction.",  __FILE__ ,  __LINE__ );
   }

   /* display log messages in a terminal */
   #ifdef LOG_MEM_IN_STDOUT
      if(direction == LOG_ALLOC){
         printf(LOG_MAGENTA "[MEM] " LOG_GREEN "+ ");
      }
      else{
         printf(LOG_MAGENTA "[MEM] " LOG_RED "- ");
      }
      printf(LOG_CYAN "%s " LOG_WHITE "%s " LOG_NORMAL, type, desc);
      printf("in " LOG_YELLOW "%s " LOG_NORMAL, file);
      printf("at line " LOG_BLUE "%d " LOG_NORMAL, line);
      printf("[adress: %p]\n", ptr);
   #endif /* LOG_ON_STDOUT */

   /* save log messages in a text file */
   #ifdef LOG_MEM_IN_LOG_FILE
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
   int i, iType, iVar, width, temp, usedCount, usedPercentage;
   Log_Variable* var;

   /* ###########################################
    * ##  compute window width
    * ###########################################
    */

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
         temp += 4 + 16 + 1;
      }

      width = max(width, temp);
   }
   width += 2;

   /* ###########################################
    * ##  compute percentage of used memory
    * ###########################################
    */
   usedCount = 0;
   //printf("variable number:%d  \n");
   for(iVar=(mem.varNb-1); iVar>=0; iVar--){
      if(mem.var[iVar].alloc == 1) usedCount++;
   }
   usedPercentage = (usedCount * 100) / mem.varNb;

   /* ###########################################
    * ##  draw the memory map window
    * ###########################################
    */

   /* display window upper bar _______ */
   printBar(' ', '_', width);

   /* display window title */
   printBarText('|', ' ', width, "MEMORY MAP", LOG_MAGENTA);

   /* display used variable bar */
   printProgressBar(usedPercentage, width);

   /* ###########################################
    * ##  draw the types window
    * ###########################################
    */
   if(verbosity & LOG_TYPE){

      /* display separation bar |------| */
      printBar('|', '-', width);

      /* display section title */
      printBarText('|', ' ', width, "Types", LOG_MAGENTA);

      /* display separation bar |      | */
      putchar('|');
      for(i=0; i<width; i++) putchar(' ');
      puts("|");

      /* display type title and count */
      for(iType=0; iType<mem.typeNb; iType++){
         putchar('|');putchar(' ');
         if(mem.typeByVar[iType] == 0){
            printf(LOG_GREEN "%4d" LOG_NORMAL " %-*s",
                   mem.typeByVar[iType], LOG_TYPE_LENGTH, mem.type[iType]);
         }
         else{
            printf(LOG_RED "%4d" LOG_NORMAL " %-*s",
                   mem.typeByVar[iType], LOG_TYPE_LENGTH, mem.type[iType]);
         }
         drawBar(' ', width-(1+4+1+LOG_TYPE_LENGTH));
         puts("|");
      }
   }

   /* ###########################################
    * ##  draw the variables window
    * ###########################################
    */
   if(verbosity & (LOG_USED | LOG_FREED)){

      /* display separation bar |------| */
      putchar('|');
      for(i=0; i<width; i++) putchar('-');
      puts("|");

      /* display section title */
      printBarText('|', ' ', width, "Variables", LOG_MAGENTA);

      /* display separation bar |     | */
      putchar('|');
      for(i=0; i<width; i++) putchar(' ');
      puts("|");

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
               //printf(" [%9p]", var->ptr);
               printf(" [0x%016" PRIxPTR "]", (uintptr_t)(var->ptr));
            }

            /* end of line */
            puts(" |");
         }
      }
   }

   /* end of display */
   printBar('|', '_', width);
}


void drawBar(char line, int count){
   while(count > 0){
      putchar(line);
      count--;
   }
}

void drawProgressBar(char firstBorder, char lastBorder, char on, char off, int percentage, int width){
   int barWidth, onCount;

   /* compute essential values */
   barWidth = width - 7;
   onCount = barWidth*percentage/100;

   /* print percentage and draw progress bar */
   printf("%3d%c %c", percentage, '%', firstBorder);
   drawBar(on, onCount);
   drawBar(off, barWidth-onCount);
   putchar(lastBorder);
}

void printBar(char border, char line, int count){
   putchar(border);
   while(count > 0){
      putchar(line);
      count--;
   }
   putchar(border);
   putchar('\n');
}

void printBarText(char border, char line, int count, char* text, char* color){
   int length;

   length = strlen(text);
   putchar(border);
   drawBar(line, (count-length)/2);
   printf("%s%s" LOG_NORMAL, color, text);
   drawBar(line, count-length-(count-length)/2);
   putchar(border);
   putchar('\n');
}

void printProgressBar(int percentage, int width){
   putchar('|'); putchar(' ');
   drawProgressBar('[', ']', '#', ' ', percentage, width-2);
   puts(" |");
}
