/**
 * \file node.h
 * \brief Node related definitions
 *
 * Definition of a Node structure.
 * Used by node.c, list.c and tree.c.
 *
 * \author François-Xavier Balu \<fx.balu@gmail.com\>
 * \date 11 mars 2014
 */


#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>  /* strlen(), strcpy() */
#include "common.h"


/**
 * \struct Attribute
 * \brief A Node's Attribute.
 */
typedef struct Attribute Attribute;
struct Attribute
{
   char * name;         /**< The Attribute's name. */
   char * value;        /**< The Attribute's value. */
   Attribute * next;    /**< Next Attribute. */
};


/**
 * \struct Node
 * \brief A tree's node.
 */
typedef struct Node Node;
struct Node
{
   char * name;         /**< The node's name. */
   char * value;        /**< The node's value. */
   Attribute * attr;    /**< First Attribute for this node. */

   /** \name Parent node */
   /**@{*/
   Node * parent;       /**< Parent node. */
   /**@}*/

   /** \name Sibling nodes */
   /**@{*/
   Node * previous;     /**< Previous sibling node. */
   Node * next;         /**< Next sibling node. */
   /**@}*/

   /** \name Child nodes */
   /**@{*/
   Node * first;        /**< First child node. */
   Node * current;      /**< Current child node. */
   Node * last;         /**< Last child node. */
   int cc;              /**< Children count. */
   /**@}*/
};


/**
 * \name Node functions
 * Functions related to name and value of a Node
 */
/**@{*/
Node * createNode(const char * name, const char * value, Node * n);

Node * allocateNode(Node * n);
void resetNode(Node * n);

void setNodeName(const char * name, Node * n);
void setNodeValue(const char * value, Node * n);

void printNode(const Node * n, const int mode);
/**@}*/ /* Node functions */


/**
 * \name Attribute functions
 * Functions related to an Attribute.
 */
/**@{*/
Attribute * createAttribute(Attribute * a);

void allocateAttribute(Attribute * a);
void resetAttribute(Attribute * a);

void setAttributeName(const char * name, Attribute * a);
void setAttributeValue(const char * value, Attribute * a);

void printAttribute(const Attribute * a);

void insertFirstAttribute(Attribute * a, Node * n);
void insertLastAttribute(Attribute * a, Node * n);

Attribute * deleteFirstAttribute(Node * n);
Attribute * deleteLastAttribute(Node * n);
/**@}*/ /* Attribute functions */


/**
 * \name List functions
 * Functions related to Node as a list.
 */
/**@{*/
boolean hasNodeChildren(Node * n);
boolean hasNodeParent(Node * n);

void insertFirst(Node * child, Node * parent);
void insertLast(Node * child, Node * parent);

Node * deleteFirstNodeList(Node * parent);
Node * deleteLastNodeList(Node * parent);

void forEachNodeChild(Node * parent, void (*fn)(Node *));
/**@}*/ /* List functions */


#endif /* NODE_H_INCLUDED */
