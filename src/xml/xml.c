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
 *
 * \todo update error log after fopen() check when logError() will be improved.
 */
XMLFile* createXMLFile(const char* path, XMLFile* xml)
{
   char firstLine[XML_BUFFER_LENGTH];

   /* check path */
   if(path == NULL)
   {
      logError("XML file path is NULL.", __FILE__, __LINE__);
      return NULL;
   }

   /* allocate memory for XMLFile xml */
   if((xml = malloc(sizeof(XMLFile))) == NULL)
   {
      logError("Can't allocate memory for XMLFile* xml.", __FILE__, __LINE__);
      return NULL;
   }

   /* set file path in XMLFile xml */
   if((xml->path = malloc((strlen(path) + 1) * sizeof(char))) == NULL)
   {
      logError("Can't allocate memory for char* path.", __FILE__, __LINE__);
      free(xml);
      return NULL;
   }
   xml->path = strcpy(xml->path, path);

   /* open file using path */
   if((xml->file = fopen(path, "r")) == NULL)
   {
      logError("Can't open XML file", __FILE__, __LINE__);
      printf("error in createXMLFile() : can't open file %s\n", path);
      free(xml->path);
      free(xml);
      return NULL;
   }

   /* read first line */
   if(fgets(firstLine, XML_BUFFER_LENGTH, xml->file) == NULL)
   {
      logError("Useful message.", __FILE__, __LINE__);
      printf("error in createXMLFile() : can't read first line of %s\n", path);
      free(xml->path);
      free(xml);
      return NULL;
   }

   /* check first line */
   if(strcmp(firstLine, FIRST_LINE_XML_FILE) != 0)
   {
      fprintf(stderr, "! error in [%s] at line [%d] :\n", __FILE__, __LINE__);
      fprintf(stderr, "! [%s] is not a valid XML file.\n", path);
      fclose(xml->file);
      free(xml->path);
      free(xml);
      return NULL;
   }

   /* provided file is a valid XML file */
   fclose(xml->file);

   return xml;
}


/**
 * \brief Destroy a XMLFile
 * Free everything allocated in a given XMLFile. File is closed, path is freed
 * and tree is destroyed using destroyNode().
 *
 * \param xml  Destroyed XMLFile
 */
void destroyXMLFile(XMLFile* xml)
{
   if(xml != NULL)
   {
      if(xml->file != NULL)
         fclose(xml->file);
      if(xml->path != NULL)
         free(xml->path);
      if(xml->root != NULL)
         destroyNode(xml->root);
   }
}


Node* parseXMLFile(const char* path)
{
   XMLFile* xml;
   int buffer;
   Node* current;

   xml = NULL;
   current = NULL;
   if((xml = createXMLFile(path, xml)) != NULL)
   {
      xml->file = fopen(path, "r");
      /* pass first XML node */
      do
      {
         buffer = fgetc(xml->file);
      }
      while((buffer != (char)'>') && (buffer != EOF));

      /* read every character */
      while(buffer != EOF)
      {
         buffer = fgetc(xml->file);
         switch((char)buffer)
         {
            case '<' :
               /* close current Node */
               if((char)fgetc(xml->file) == '/')
               {

               }
               /* start a new Node */
               else
               {

               }

         }
      }

      /* close XML file */
      fclose(xml->file);
   }


   return xml->root;
}
