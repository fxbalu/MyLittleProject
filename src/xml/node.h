/**
 * \file node.h
 * \brief Node related definitions
 *
 * Definition of a XML_Node structure and functions to use it.
 *
 * \author François-Xavier Balu \<fx.balu@gmail.com\>
 * \date 11 mars 2014
 *
 * \todo check usefulness of functions in XML parsing.
 * \todo change type from Node to XML_Node, like SDL does.
 * \todo use XML_Attribute list like a FIFO (First In First Out) pile.
 *       Attributes doesn't need powerful functions to use them.
 */


#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>  /* strlen(), strcpy() */


/**
 * \struct XML_Node
 * \brief A XML tree's node.
 */
typedef struct XML_Node XML_Node;
struct XML_Node
{
   char* name;             /**< Node's name. */
   char* value;            /**< Node's value. */
   XML_Attribute* attr;    /**< First node's attribute. */

   /** \name Parent node */
   /**@{*/
   XML_Node* parent;       /**< Parent node. */
   /**@}*/

   /** \name Sibling nodes */
   /**@{*/
   XML_Node* previous;     /**< Previous sibling node. */
   XML_Node* next;         /**< Next sibling node. */
   /**@}*/

   /** \name Child nodes */
   /**@{*/
   XML_Node* first;        /**< First child node. */
   XML_Node* current;      /**< Current child node. */
   XML_Node* last;         /**< Last child node. */
   int cc;                 /**< Children count. */
   /**@}*/
};


XML_Node* createXMLNode(void);
void destroyXMLNode(XML_Node* n);

XML_Node* allocXMLNode(XML_Node* n);
void freeXMLNode(XML_Node* n);

void initXMLNode(XML_Node* n);

void setXMLNodeName(const char* name, XML_Node* n);
void setXMLNodeValue(const char* value, XML_Node* n);

void addAttributeToXMLNode(Attribute* attr, XML_Node* n);
XML_Attribute* deleteAttributeFromXMLNode(XML_Node* n);

void addXMLNodeToParent(XML_Node* parent, XML_Node* child);
void deleteXMLNodeFromParent(XML_Node* child);


#endif /* NODE_H_INCLUDED */
