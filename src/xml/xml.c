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


/**
 * \brief Generate a tree from a XML file.
 * This function has the higher level possible in the XML Parser. It's should be
 * The only function called from outside.
 *
 * \param[in] path  read XML file.
 * \return          Generated tree's root.
 */
Node* parseXMLFile(const char* path)
{
   XMLFile* xml;
   int buffer;
   XMLTag


   xml = NULL;
   current = NULL;
   if((xml = createXMLFile(path, xml)) != NULL)
   {
      xml->file = fopen(path, "r");
      /* skip first XML node, since it was checked in createXMLFile() */
      do
      {
         if((buffer = fgetc(xml->file)) == EOF)
            logError("EOF found before end of first tag.", __FILE__, __LINE__);
      }
      while((buffer != (char)'>') && (buffer != EOF));

      /* read file until EOF is reached */
      while(buffer != EOF)
      {

      }
      printf(" End of file [s] reached. Parsing stopped.\n", path);

      /* close XML file */
      fclose(xml->file);
   }


   return xml->root;
}


/**
 * \brief Create a XMLTag.
 *
 * \param tag Created XMLTag.
 * \return    Created XMLTag.
 */
XMLTag* createXMLTag(XMLTag* tag)
{
   if((tag = malloc(sizeof(XMLTag))) == NULL)
   {
      logError("Can't allocate memory for XMLTag", __FILE__, __LINE__);
   }
   else
   {
      tag->name = NULL;
      tag->attr = NULL;
   }

   return tag;
}


/**
 * \brief Read and parse a tag in a XML file.
 * Read characters in a XML file until '>' is reached, and store informations in
 * a XMLTag structure.
 *
 * \param[in] xml  Handled XMLFile, read file is in XMLFile->file.
 * \return         Read and parsed XMLTag, \c NULL if an error happened.
 */
XMLTag* readTag(const XMLFile* xml, XMLTag* tag)
{
   int buffer;

   if(xml != NULL)
   {
      tag = createXMLTag(tag);

      /* parse tag */
      do
      {

      }
      while((buffer != (int)'>') && (buffer != EOF));
   }

   return tag;
}
