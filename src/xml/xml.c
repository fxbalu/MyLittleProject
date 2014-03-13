/**
 * \file xml.c
 * \brief XML file related functions.
 *
 * Definitions of functions to read and parse a XML file.
 *
 * \author François-Xavier Balu \<fx.balu@gmail.com\>
 * \date 13 mars 2014
 */


#include "xml.h"


/**
 * \brief create an XMLFile
 * Allocate memory, open the file described in path and check if it contains
 * XML formated data. The check is done by reading the first line of the file.
 *
 * \param path  Path of the file to read
 * \param xml   Created XMLFile
 * \return      \p XMLFile if file contains XML formated data, \c NULL if not.
 */
XMLFile * createXMLFile(const char * path, XMLFile * xml)
{
   /* check path */
   if(path == NULL)
   {
      printf("error in createXMLFile() : path = NULL\n");
   }
   else
   {
      /* allocate memory for XMLFile xml */
      if((xml = malloc(sizeof(XMLFile))) == NULL)
      {
         printf("error in createXMLFile() : can't allocate memory\n");
      }
      else
      {
         /* open file */
         xml->path = path;
         if((xml->file = fopen(path, "r")) == NULL)
         {
            printf("error in createXMLFile() : can't open file %s\n", path);
         }
         else
         {
            /* check first line */
            if( /* not an XML file */ )
            {
               printf("error in createXMLFile() : %s is not a XML file", path);
               /* close file, free everything */
               xml = NULL;
            }
            else
            {
               /* close file */
            }
         }
      }
   }

   return xml;
}
