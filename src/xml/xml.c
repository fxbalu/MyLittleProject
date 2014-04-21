/**
 * \file xml.c
 * \brief XML file related functions.
 *
 * Definitions of functions to read and parse a XML file.
 *
 * \author François-Xavier Balu \<fx.balu@gmail.com\>
 * \date 13 mars 2014
 */


#include <stdio.h>   /* printf(), fopen(), fclose(), fgets() */
#include <stdlib.h>  /* malloc(), free(), atoi(), strtod() */
#include <string.h>  /* strlen(), strcpy(), strcmp() */

#include "../log.h"  /* logError() */
#include "node.h"    /* XML_Node */
#include "xml.h"


/**
 * \brief Create an initialized XML_File.
 * Allocate memory for a XML_File and initialize it.
 *
 * \return  Created XML_File.
 */
XML_File* createXMLFile(void)
{
   XML_File* xml;

   if((xml = malloc(sizeof(XML_File))) == NULL) {
      logError("Can't allocate memory for XML_File", __FILE__, __LINE__);
   }
   else {
      logMem(LOG_ALLOC, xml, "XML_File", "xml file", __FILE__, __LINE__);
      xml->path = NULL;
      xml->file = NULL;
      xml->root = NULL;
   }

   return xml;
}


/**
 * \brief Destroy a XML_File.
 *
 * \param xml  Destroyed XML_File.
 */
void destroyXMLFile(XML_File* xml)
{
   if(xml == NULL) {
      logError("Trying to destroy a NULL XML_File", __FILE__, __LINE__);
   }
   else {
      /* free path */
      if(xml->path != NULL) {
         logMem(LOG_FREE, xml->path, "string", "xml path", __FILE__, __LINE__);
         free(xml->path);
      }
      /* close file */
      if(xml->file != NULL) {
         logMem(LOG_FREE, xml->file, "file", "xml file", __FILE__, __LINE__);
         fclose(xml->file);
      }
      /* destroy tree */
      if(xml->root != NULL) {
         destroyXMLNode(xml->root);
      }
      /* free XML_File */
      logMem(LOG_FREE, xml, "XML_File", "xml file", __FILE__, __LINE__);
      free(xml);
   }
}


/**
 * \brief Set a file path for a XML_File.
 * Allocate memory for a XML_File's path, and copy path's content in it.
 * If \p xml already has a name, memory is reallocated instead.
 *
 * \param[in] path  Given file path.
 * \param     xml   Modified XML_File.
 */
void setXMLFilePath(const char* path, XML_File* xml)
{
   /* NULL XML_File */
   if(xml == NULL) {
      logError("Giving a file path to a NULL XML_File", __FILE__, __LINE__);
   }
   /* NULL file path */
   else if(path == NULL) {
      logError("Giving a NULL file path to a XML_File", __FILE__, __LINE__);
   }
   /* XML_File already has a file path */
   else if(xml->path != NULL) {
      if((xml->path = realloc(xml->path, (strlen(path) + 1) * sizeof(char))) == NULL) {
         logError("Can't reallocate memory for file path", __FILE__, __LINE__);
      }
      else {
         strcpy(xml->path, path);
      }
   }
   /* XML_File doesn't have a file path */
   else {
      if((xml->path = malloc((strlen(path) + 1) * sizeof(char))) == NULL) {
         logError("can't allocate memory for file path", __FILE__, __LINE__);
      }
      else {
         logMem(LOG_ALLOC, xml->path, "string", "xml path", __FILE__, __LINE__);
         strcpy(xml->path, path);
      }
   }
}


void openXMLFile(XML_File* xml)
{
   if(xml == NULL) {
      logError("Can't open XML file of a NULL XML_File", __FILE__, __LINE__);
   }
   else if(xml->path == NULL) {
      logError("No path found in XML_File", __FILE__, __LINE__);
   }
   else if(xml->file != NULL) {
      logError("File already opened in XML_File", __FILE__, __LINE__);
   }
   else if((xml->file = fopen(xml->path, "r")) == NULL) {
      logError("Can't open file with XML_File's path", __FILE__, __LINE__);
   }
   else {
      logMem(LOG_ALLOC, xml->file, "file", "xml file", __FILE__, __LINE__);
   }
}


void closeXMLFile(XML_File* xml)
{
   if(xml == NULL) {
      logError("Can't close XML file of a NULL XML_File", __FILE__, __LINE__);
   }
   else if(xml->file == NULL) {
      logError("Can't close a NULL file in XML_File", __FILE__, __LINE__);
   }
   else {
      logMem(LOG_FREE, xml->file,"file", "xml file", __FILE__, __LINE__);
      fclose(xml->file);
      xml->file = NULL;
   }
}


int checkFirstLineXMLFile(XML_File* xml)
{
   char firstLine[XML_BUFFER_LENGTH];

   if(xml == NULL) {
      logError("Can't check first line of a NULL XML_File", __FILE__, __LINE__);
   }
   else if(xml->file == NULL) {
      logError("Can't read a NULL file in XML_File", __FILE__, __LINE__);
   }
   else if(fgets(firstLine, XML_BUFFER_LENGTH, xml->file) == NULL) {
      logError("Can't read first line of XML_File", __FILE__, __LINE__);
   }
   else {
      return (strcmp(firstLine, XML_FIRST_LINE) == 0);
   }

   return 0;
}


XML_Node* parseXMLFile(FILE* file)
{
   XML_Node *current, *child, *root;
   XML_Tag* tag;
   int endOfParsing;

   current = child = root = NULL;
   tag = NULL;
   endOfParsing = 0;

   /* read first tag */
   if((tag = readXMLTag(file)) == NULL) {
      logError("Nothing to parse", __FILE__, __LINE__);
      destroyXMLTag(tag);
      return NULL;
   }
   else if(tag->type == CLOSING) {
      logError("First tag is a closing tag", __FILE__, __LINE__);
      destroyXMLTag(tag);
      return NULL;
   }
   else if(tag->type == UNIQUE) {
      root = createXMLNode();
      initXMLNodeFromXMLTag(root, tag);
      destroyXMLTag(tag);
      return root;
   }
   else /* tag->type == OPENING */ {
      current = root = createXMLNode();
      initXMLNodeFromXMLTag(current, tag);
      destroyXMLTag(tag);
   }

   /* read following node's value or tags, if any */
   while(endOfParsing == 0) {
      //reachNextXMLTag(file);  // prevent parsing to read a node's value.
      readXMLNodeValue(current, file);
      tag = readXMLTag(file);

      if(tag == NULL) {
         logError("No tag remaining, and tree isn't finished",
                  __FILE__, __LINE__);
         destroyXMLNode(root);
         return NULL;
      }
      /* Tag opens a child node for current node */
      else if(tag->type == OPENING) {
         child = createXMLNode();
         initXMLNodeFromXMLTag(child, tag);
         addXMLNodeToParent(current, child);
         current = child;
      }
      else if(tag->type == UNIQUE) {
         child = createXMLNode();
         initXMLNodeFromXMLTag(child, tag);
         addXMLNodeToParent(current, child);
      }
      /* Tag close current node */
      else if(tag->type == CLOSING) {
         if(current->parent != NULL) {
            current = current->parent;
         }
         else {
            endOfParsing = 1;
         }
      }

      destroyXMLTag(tag);
   }

   if(root != current) {
      logError("Last closed node isn't root node", __FILE__, __LINE__);
      destroyXMLNode(root);
      return NULL;
   }

   return root;
}


XML_File* loadXMLFile(const char* path){
   XML_File* xml;

   if((xml = createXMLFile()) != NULL){
      setXMLFilePath(path, xml);
      openXMLFile(xml);
      checkFirstLineXMLFile(xml);
      xml->root = parseXMLFile(xml->file);
   }

   return xml;
}


/**
 * \brief Read integer values in a XML file and stored them in a table.
 *
 * \param[in] table  Table where integers will be stored
 * \param[in] path   Matching expression. Every matching values will be
 *                   converted to int and stored.
 * \param[in] xml    XML file where values are searched
 * \return           Number of stored integers
 */
int getXMLIntTable(int* table, char* path, XML_File* xml){
   int count;
   char* temp;
   char strBuffer[XML_BUFFER_LENGTH];
   char nameBuffer[XML_BUFFER_LENGTH];
   char attrBuffer[XML_BUFFER_LENGTH];
   XML_Node* n;
   XML_Attribute* attr;
   int readValue;

   count = 0;

   /* check parameters */
   if((table == NULL) || (path == NULL) || (xml == NULL)){
      logError("NULL parameter(s) in getXMLIntTable().", __FILE__, __LINE__);
      return 0;
   }

   /* check if there is a ':' or a '$' in path */
   /** \bug do not work as expected. Use multiple of strchr() instead. */
   else if(strpbrk(path, "$:/") == NULL){
      logError("Bad path (no parent (/), attribute (:) or value ($)).", __FILE__, __LINE__);
      return 0;
   }

   // test/data?layer=0/gid:n
   // -----------------  <--parent

   /* get parent node */
   temp = strrchr(path, (int)'/');
   strncpy(strBuffer, path, temp-path);
   strBuffer[temp-path] = '\0';
   if((n = getXMLNode(strBuffer, xml->root)) == NULL){
      logError("Can't find a parent node with this path.", __FILE__, __LINE__);
   }

   /* check children */
   else{

      /* read node's name in path */
      path = temp+1;
      temp = strpbrk(path, ":$");
      strncpy(nameBuffer, path, temp-path);
      nameBuffer[temp-path] = '\0';

      /* read attribute's name if necessary */
      if(*temp == ':'){
         readValue = 0;
         strcpy(attrBuffer, temp+1);
      }
      else{
         readValue = 1;
      }

      n = n->first;
      while(n != NULL){
         /* check node's name */
         if(strcmp(n->name, nameBuffer) == 0){

            /* read, convert and store value */
            if(readValue){
               *table = atoi(n->value);
               table++;
               count++;
            }

            /* check attributes */
            else{
               attr = n->attr;
               while(attr != NULL){
                  if(strcmp(attr->name, attrBuffer) == 0){
                     *table = atoi(attr->value);
                     table++;
                     count++;
                  }
                  attr = attr->next;
               }
            }
         }
         n = n->next;
      }
   }

   return count;
}


/**
 * \brief Read a value in a XML file.
 *
 * \param[in] path  Values path in the XML file.
 *                  To find a node's value, use "root/foo/bar$"
 *                  To find an attribute, use "root/foo/bar:attribute"
 * \param[in] root  Searched XML tree.
 */
char* getXMLValue(char* path, XML_Node* root){
   char strBuffer[XML_BUFFER_LENGTH];
   char* charPtr;
   char* value;
   XML_Node* n;
   XML_Attribute* attr;

   value = NULL;

   /* check parameters */
   if((path == NULL) || (root == NULL)){
      logError("NULL parameter(s) in getXMLValue().", __FILE__, __LINE__);
   }

   /* check if there is a ':' or a '$' in path */
   else if((charPtr = strpbrk(path, "$:")) == NULL){
      logError("Not asking a value ($) or an attribute (:) in path.", __FILE__, __LINE__);
   }

   /* get node */
   else{
      /* copy path without the last part ("$" or ":attribute_name") */
      strncpy(strBuffer, path, charPtr-path);
      strBuffer[charPtr-path] = '\0';

      if((n = getXMLNode(strBuffer, root)) == NULL){
         logError("Didn't find a node with this path.", __FILE__, __LINE__);
      }

      /* return node's value */
      else if(*charPtr == '$'){
         value = n->value;
      }

      /* find attribute */
      else{
         charPtr++;
         attr = n->attr;
         while((attr != NULL) && (strcmp(charPtr, attr->name) != 0)){
            attr = attr->next;
         }
         if(attr == NULL){
            logError("Didn't find an attribute with this name", __FILE__, __LINE__);
         }
         else{
            value = attr->value;
         }
      }
   }

   return value;
}

/**
 * \brief Finds a particular node in a XML tree.
 *
 * \param[in] path  Node path in the tree.
 *                  eg. "foo/bar", "foo/bar?attr=value/lel"
 * \param[in] root  Tree's root.
 * \return          A pointer to found node, NULL if such a node wasn't found.
 */
XML_Node* getXMLNode(char* path, XML_Node* root){
   char nameBuffer[XML_BUFFER_LENGTH];
   char attrBuffer[XML_BUFFER_LENGTH];
   char valueBuffer[XML_BUFFER_LENGTH];
   int iPath, iNaBuf, iAtBuf, iVaBuf;
   char charBuffer;
   XML_Node* n;
   XML_Attribute* attr;
   int nodeFound;

   /* checks parameters */
   if((path == NULL) || (root == NULL)){
      return NULL;
   }

   n = root;
   iPath = iNaBuf = iAtBuf = iVaBuf = 0;

   /* reads node's name in path */
   charBuffer = path[iPath];
   while((charBuffer != '/') &&
         (charBuffer != '?') &&
         (charBuffer != '\0') &&
         (iNaBuf < XML_BUFFER_LENGTH)){
      nameBuffer[iNaBuf] = charBuffer;
      iNaBuf++;
      iPath++;
      charBuffer = path[iPath];
   }

   nameBuffer[iNaBuf] = '\0';
   iPath++;

   /* reads attribute's name and value if necessary */
   if(charBuffer == '?'){

      /* reads attribute's name in path */
      charBuffer = path[iPath];
      while((charBuffer != '=') &&
            (charBuffer != '\0') &&
            (iNaBuf < XML_BUFFER_LENGTH)){
         attrBuffer[iAtBuf] = charBuffer;
         iAtBuf++;
         iPath++;
         charBuffer = path[iPath];
      }
      attrBuffer[iAtBuf] = '\0';
      iPath++;

      /* checks if attribute's name is followed by a value */
      if(charBuffer != '='){
         logError("Attribute's name is not followed by a value.", __FILE__, __LINE__);
         return NULL;
      }

      /* reads attribute's value */
      else{
         charBuffer = path[iPath];
         while((charBuffer != '/') &&
               (charBuffer != '\0') &&
               (iVaBuf < XML_BUFFER_LENGTH)){
            valueBuffer[iVaBuf] = charBuffer;
            iVaBuf++;
            iPath++;
            charBuffer = path[iPath];
         }
         valueBuffer[iVaBuf] = '\0';
         iPath++;
      }
   }

   /* finds a matching node */
   nodeFound = 0;
   printf("search node with name %s\n", nameBuffer);
   do{
      printf(" tested node: ");printXMLNode(n, 1);
      /* checks node's name */
      if(strcmp(nameBuffer, n->name) != 0){
         n = n->next;
      }
      /* found a node with this name, and no need to check attribute */
      else if(!iAtBuf){
         nodeFound = 1;
      }
      /* also checks attribute's name and value */
      else{
         printf(" search attribute %s with value %s\n", attrBuffer, valueBuffer);
         attr = n->attr;
         while((attr != NULL) && (nodeFound == 0)){
            printf("  %s=\"%s\"\n", attr->name, attr->value);
            if((strcmp(attr->name, attrBuffer) == 0) &&
               (strcmp(attr->value, valueBuffer) == 0)){
               nodeFound = 1;
            }
            else{
               attr = attr->next;
            }
         }
         /* Didn't found a matching attribute, select next node */
         if(attr == NULL){
            n = n->next;
         }
      }
   }
   while((!nodeFound) && (n != NULL));

   /* Didn't found a matching node, return NULL */
   if(!nodeFound){
      n = NULL;
   }
   /* found node character '/', checks children */
   else if(charBuffer == '/'){
      n = getXMLNode(path + iPath, n->first);
   }
   /* Didn't find end of string character '/0', return NULL  */
   else if(charBuffer != '\0'){
      n = NULL;
   }

   return n;
}

char* getXMLString(char* path, XML_File* xml, char* defaultValue){
   char* value;

   if((value = getXMLValue(path, xml->root)) == NULL){
      value = defaultValue;
   }

   return value;
}

int getXMLInt(char* path, XML_File* xml, int defaultValue){
   char* temp;
   int value;

   if((temp = getXMLValue(path, xml->root)) == NULL){
      value = defaultValue;
   }
   else{
      value  = atoi(temp);
   }

   return value;
}

int getXMLBool(char* path, XML_File* xml, int defaultValue){
   char* temp;
   int value;

   if((temp = getXMLValue(path, xml->root)) == NULL){
      value = defaultValue;
   }
   else{
      if(strcmp(temp, "true") == 0){
         value = 1;
      }
      else if(strcmp(temp, "false") == 0){
         value = 0;
      }
      else{
         value = defaultValue;
      }
   }

   return value;
}

double getXMLDouble(char* path, XML_File* xml, double defaultValue){
   char* temp;
   double value;

   if((temp = getXMLValue(path, xml->root)) == NULL){
      value = defaultValue;
   }
   else{
      value  = strtod(temp, NULL);
   }

   return value;
}
