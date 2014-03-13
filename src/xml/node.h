/**
 * \file node.h
 * \brief Node related definitions
 *
 * Definition of a Node structure.
 *
 * \author François-Xavier Balu \<fx.balu@gmail.com\>
 * \date 11 mars 2014
 */


#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>  /* strcpy() */
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

   /* list * attributes;   /**< List of attributes for this node. */
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
/**@}*/ /* Node functions */


/**
 * \name List's node functions
 * Functions related to Node as member of a list (the Node is IN a list).
 */
/**@{*/
int getNodePosition(Node * n);
/**@}*/ /* List's node functions */


/**
 * \name List functions
 * Functions related to Node as a list (the Node IS the list).
 */
/**@{*/

/**@}*/ /* List's node functions */


#endif /* TREE_H_INCLUDED */
