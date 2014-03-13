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


#include "node.h"


typedef struct XMLFile XMLFile;
struct XMLFile
{
   char * path;   /**< Path of the XML file */
   FILE * file;   /**< Pointer to the file */
   Node * root;   /**< Root of the generated tree after parsing */
};


XMLFile * createXMLFile(const char * path, XMLFile * xml);


#endif // XML_H_INCLUDED
