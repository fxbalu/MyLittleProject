/**
 * \file log.h
 * \brief Logging related functions
 *
 * \author François-Xavier Balu \<fx.balu@gmail.com\>
 * \date 08/04/14
 */


#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED


/* Memory logging options. Comment to disable.  */
#define LOG_ON_STDOUT
#define LOG_ON_STDERR
//#define LOG_IN_STD_FILE
//#define LOG_IN_ERR_FILE

/* Direction for logMem(). Basically IN or OUT */
#define LOG_ALLOC   '<'
#define LOG_FREE    '>'

/* Number of entry in the logMem() table of MemAlloc structures */
#define LOG_ENTRY_NB  100

/* String length */
#define LOG_TYPE_LENGTH  20
#define LOG_DESCRIPTION_LENGTH  40


/* Structure for dynamic memory allocation logging */
typedef struct MemAlloc {
   char type[LOG_TYPE_LENGTH];
   /* char* description;
   char* file;
   int line; */
} MemAlloc;


void logError(const char* str, const char* file, const int line);
void logMem(const char direction, const char* type, const char* file, const int line);
void checkMemAlloc(void);

#endif /* LOG_H_INCLUDED */
