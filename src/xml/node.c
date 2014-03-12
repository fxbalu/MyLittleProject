/**
 * \file node.c
 * \brief Node related functions
 *
 * Definitions of functions to access a Node's members.
 *
 * \author François-Xavier Balu \<fx.balu@gmail.com\>
 * \date 11 mars 2014
 */


#include "node.h"


/**
 * \brief Create a Node.
 * Allocate memory for a Node and set every pointer to NULL.
 *
 * \param n  Created Node
 * \return   Created Node
 */
Node * createNode(Node * n)
{
   if((n = malloc(sizeof(Node))) == NULL)
   {
      printf("\n\\(O_O)/ <( oh ma gad, c'est le bowdel dans la memoiwe ! )");
      printf("\nerror in createNode(Node * n)");
   }
   else
   {
      resetNode(n);
   }

   return n;
}


/**
 * \brief Reset a node.
 * Set a Node's members to NULL for the pointers and 0 for the children count.
 *
 * \param n  Reseted Node
 * \todo add attributes support when attribute struct is done.
 */
void resetNode(Node * n)
{
   if(n != NULL)
   {
      n->name = NULL;
      /* n->attributes = NULL; */
      /* Node's parent */
      n->parent = NULL;
      /* Node's siblings */
      n->previous = n->next = NULL;
      /* Node's children */
      n->first = n->current = n->last = NULL;
      n->cc = 0;
   }
}


/**
 * \brief Set a name for a Node.
 *
 * \param[in] name given name
 * \param     n    modified Node
 */
void setNodeName(const char * name, Node * n)
{
   if(name != NULL && n != NULL)
   {
      if((n->name = malloc((strlen(name) + 1) * sizeof(char))) == NULL)
      {
         printf("error in setNodeName()");
      }
      else
      {
         strcpy(n->name, name);
      }
   }
}


/**
 * \brief Set a value for a Node.
 *
 * \param[in] value given value
 * \param     n     modified Node
 */
void setNodeValue(const char * value, Node * n)
{
   if(value != NULL && n != NULL)
   {
      if((n->value = malloc((strlen(value) + 1) * sizeof(char))) == NULL)
      {
         printf("error in setNodeValue()");
      }
      else
      {
         strcpy(n->value, value);
      }
   }
}
