/**
 * \file common.c
 * \brief Common functions.
 * \author François-Xavier Balu \<fx.balu@gmail.com\>
 * \date 12 mars 2014
 */

#include "common.h"

/**
 * \brief Log error in standard error output
 * Show an error message in standard output with file name and line number.
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
void logError(const char* str, const char* file, const int line)
{
    fprintf(stderr, "! error in [%s] at line [%d] :\n! %s\n", file, line, str);
}

//premiere version on va test la vitesse des blits avec et sans
SDL_Surface* loadImage(char* file) {
   SDL_Surface* temp = IMG_Load(file);
   SDL_Surface* image = SDL_DisplayFormatAlpha(temp);

   if(image == NULL){
      logError("erreur fonction loadImage", __FILE__, __LINE__);
   }
   free(temp);
   return image;
}
