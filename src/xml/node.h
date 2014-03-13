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


#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>  /* strlen() */
#include "common.h"


/**
 * \struct Node
 * \brief A tree's node.
 */
typedef struct Node Node;
struct Node
{
   char * name;   /**< The node's name. */
   char * value;  /**< The node's value. */

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

   /* list * attributes; */  /**< List of attributes for this node. */
};


/**
 * \name Node functions
 * Functions related to name and value members of Node
 */
/**@{*/
Node * createNode(Node * n);
void resetNode(Node * n);

void setNodeName(const char * name, Node * n);
void setNodeValue(const char * value, Node * n);

void printNode(const Node * n, const int mode);
/**@}*/ /* Node functions */


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
/**@}*/ /* List's node functions */


#endif /* TREE_H_INCLUDED */
