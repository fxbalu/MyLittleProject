/**
 * \file tag.h
 * \brief XML tag related definitions
 *
 * Definition of a XML_Tag structure and functions to use it.
 *
 * \author François-Xavier Balu \<fx.balu@gmail.com\>
 * \date 16 mars 2014
 *
 * \todo check if \\struct tag in needed to document struct and enum.
 */


#ifndef TAG_H_INCLUDED
#define TAG_H_INCLUDED


#include <stdio.h>
#include "attribute.h"
#include "xml.h"        /* XML_BUFFER_LENGTH */
#include "../common.h"  /* logError() */



/**
 * \brief The type of a tag in a XML file.
 * A tag can open a Node, close it or the two in the same time.
 *
 */
typedef enum XML_TagType {
   OPENING,    /**< This tag start a new Node. */
   CLOSING,    /**< This tag close a Node opened by an OPENING tag. */
   UNIQUE,     /**< This tag open and close a Node of his own. */
   UNKNOWN     /**< The tag type is unknown */
} XML_TagType;


/**
 * \brief XML tag structure
 * Contains informations about a XML tag.
 * Example of a XML tag :
 * \code{.xml} <name attr1name="attr1value" attr2name="attr2value"/> \endcode
 */
typedef struct XML_Tag {
   char* name;             /**< Tag's name. */
   XML_Attribute* attr;    /**< Last added attribute. */
   XML_TagType type;       /**< Tag type (opening, closing, unique) */
} XML_Tag;


XML_Tag* createXMLTag(void);
void destroyXMLTag(XML_Tag* tag);

XML_Tag* allocXMLTag(XML_Tag* tag);
void freeXMLTag(XML_Tag* tag);

void initXMLTag(XML_Tag* tag);
void resetXMLTag(XML_Tag* tag);

void setXMLTagName(const char* name, XML_Tag* tag);
void addAttributeToXMLTag(Attribute* attr, XML_Tag* tag);
XML_Tag* deleteAttributeFromXMLTag(XML_Tag* tag);

XML_Tag* readXMLTag(FILE* file);

#endif // TAG_H_INCLUDED
