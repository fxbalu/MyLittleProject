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

/*
   ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   :::    Old functions                                                   :::
   ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/

/**
 * \brief create an XML_File
 * Allocate memory, open the file described in path and check if it contains
 * XML formated data. The check is done by reading the first line of the file.
 *
 * \param path  Path of the file to read
 * \param xml   Created XML_File
 * \return      \p XML_File if file contains XML formated data, \c NULL if not.
 *
 * \todo update error log after fopen() check when logError() will be improved.
 */
XML_File* createXMLFile(const char* path, XML_File* xml)
{
   char firstLine[XML_BUFFER_LENGTH];

   /* check path */
   if(path == NULL)
   {
      logError("XML file path is NULL.", __FILE__, __LINE__);
      return NULL;
   }

   /* allocate memory for XMLFile xml */
   if((xml = malloc(sizeof(XML_File))) == NULL)
   {
      logError("Can't allocate memory for XML_File* xml.", __FILE__, __LINE__);
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
   if(strcmp(firstLine, XML_FIRST_LINE) != 0)
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
void destroyXMLFile(XML_File* xml)
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
 *
 * \todo Redo this function entirely
 */
Node* getTreeFromXMLFile(const char* path)
{
   XML_File* xml;
   int buffer;
   /*XML_Tag* tag;*/


   xml = NULL;
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
      printf("End of file [%s] reached. Parsing stopped.\n", path);

      /* close XML file */
      fclose(xml->file);
   }


   return xml->root;
}









/**
 * \brief Read a tag attribute in a XML file.
 *
 * \param file Read XML file.
 * \return     Read tag's attribute.
 */
Attribute* readAttribute(FILE* file)
{
   Attribute* attr;
   char strBuffer[XML_BUFFER_LENGTH];
   int charBuffer, i;

   attr = allocateAttribute(attr);

   /* read attribute's name */
   i = 0;
   charBuffer = fgetc(file);
   while(charBuffer != (int)'=') {

      strBuffer[i] = (char)charBuffer;
      i++;
      charBuffer = fgetc(file);
   }
   strBuffer[i] = '\0';

   /* check implied following character '"' */
   if(fgetc(file) != (int)'"') {
      logError("Badly parsed XML file.", __FILE__, __LINE__);
      return NULL;
   }

   /* set attribute's name with read string */
   setAttributeName(strBuffer, attr);

   /* read attribute's value */
   i = 0;
   charBuffer = fgetc(file);
   while(charBuffer != (int)'"') {
      strBuffer[i] = (char)charBuffer;
      i++;
      charBuffer = fgetc(file);
   }
   strBuffer[i] = '\0';

   /* set attribute's value with read string */
   setAttributeValue(strBuffer, attr);

   return attr;
}
