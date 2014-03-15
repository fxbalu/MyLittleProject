/**
 * \file xml.h
 * \brief XML files related definitions
 *
 * Definition of a XML file structure.
 *
 * \author François-Xavier Balu \<fx.balu@gmail.com\>
 * \date 13 mars 2014
 */


#ifndef XML_H_INCLUDED
#define XML_H_INCLUDED


#include <stdio.h>   /* printf(), fopen(), fclose(), fgets() */
#include <stdlib.h>  /* malloc(), free() */
#include <string.h>  /* strlen(), strcpy() */

#include "../common.h"
#include "node.h"


/**
 * \brief Execute some testing code in function
 * Lines preceded by \code if(DEBUG) {...} \endcode will be executed.
 */
#define DEBUG  true

/**
 * \brief Buffer length for XML file reading.
 * Number of characters read by fgets() while reading a XML file.
 * Need to be at least superior or equal to 39 char in order to read the first
 * line that contains xml version and character encoding.
 */
#define XML_BUFFER_LENGTH  50

/**
 * \brief First line of a valid XML file.
 * First node of an XML file. It contains XML version and character encoding of
 * the file. There is 38 effective characters and a END OF STRING '\\0'
 * character at the end.
 * Quotes between values are escaped for C compatibility sake.
 */
#define FIRST_LINE_XML_FILE  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"

/**
 * \brief String length of XMLTag's members.
 */
#define XML_TAG_STRING_LENGTH 100


typedef struct XMLFile     XMLFile;
typedef struct XMLTag      XMLTag;
typedef enum   XMLTagType  XMLTagType;

/**
 * \brief XML file structure
 * Contains informations about a XML file.
 */
struct XMLFile {
   char * path;   /**< Path of the XML file */
   FILE * file;   /**< Pointer to the file */
   Node * root;   /**< Root of the generated tree after parsing */
};

/**
 * \brief XML Tag structure
 * Contains informations about a XML tag.
 * Example of a XML tag :
 * \code{.xml} <name attr1name="attr1value" attr2name="attr2value"/> \endcode
 */
struct XMLTag {
   char* name;       /**< Tag's name. */
   Attribute* attr;  /**< Tag's first Attribute. */
};


Node* parseXMLFile(const char* path);
XMLFile* createXMLFile(const char* path, XMLFile* xml);
XMLTag* readNextTag(const XMLFile* xml, XMLTag* tag);


#endif /* XML_H_INCLUDED */
